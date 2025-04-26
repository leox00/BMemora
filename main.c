// todo_input.c

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 100
#define FONT_SIZE     24
#define MAX_TEXT_LEN  256
#define CURSOR_WIDTH  2
#define CURSOR_HEIGHT FONT_SIZE
#define CURSOR_BLINK_INTERVAL 500  // Milliseconds for cursor blink

void save_text(const char* text) {
    const char* home = getenv("HOME");
    if (!home) {
        home = ".";
    }
    char path[512];
    snprintf(path, sizeof(path), "%s/.bmemora", home);

    FILE* file = fopen(path, "a");
    if (file) {
        fprintf(file, "%s\n", text);
        fclose(file);
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow(
        "Quick Todo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf", FONT_SIZE);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }

    SDL_StartTextInput();

    char text[MAX_TEXT_LEN] = {0};
    int running = 1;
    SDL_Event e;

    Uint32 cursor_blink_timer = 0;
    bool cursor_visible = true;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            else if (e.type == SDL_TEXTINPUT) {
                if (strlen(text) + strlen(e.text.text) < MAX_TEXT_LEN - 1) {
                    strcat(text, e.text.text);
                }
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    size_t len = strlen(text);
                    if (len > 0) {
                        text[len - 1] = '\0';
                    }
                }
                else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                    save_text(text);
                    running = 0;
                }
                else if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

        // Handle cursor blink
        Uint32 current_time = SDL_GetTicks();
        if (current_time - cursor_blink_timer > CURSOR_BLINK_INTERVAL) {
            cursor_blink_timer = current_time;
            cursor_visible = !cursor_visible;  // Toggle cursor visibility
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Blended(font, text, textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = {20, (WINDOW_HEIGHT - texH) / 2, texW, texH};

        SDL_RenderCopy(renderer, texture, NULL, &dstrect);

        // Draw the blinking cursor
        if (cursor_visible) {
            int cursor_x = 20 + texW;  // Position the cursor right after the text
            int cursor_y = (WINDOW_HEIGHT - FONT_SIZE) / 2;  // Center vertically
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White cursor
            SDL_Rect cursorRect = {cursor_x, cursor_y, CURSOR_WIDTH, CURSOR_HEIGHT};
            SDL_RenderFillRect(renderer, &cursorRect);
        }

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
