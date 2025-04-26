# Bmemora - Quick Idea Saver

**Bmemora** is a minimalistic, fast, and simple idea-saving application designed for quick note-taking directly on your Linux system. Inspired by tools like rofi, it allows you to quickly jot down ideas with a small input window. The text is saved in a plain text file (`~/.bmemora.txt`), which can be viewed or managed later.

- Written in C using SDL2 for rendering

## Installation

### Dependencies:
- SDL2
- SDL2_ttf
- Font (e.g., DejaVu Sans)

### Installing Dependencies

#### For Ubuntu/Debian-based distributions:

```bash
sudo apt-get install libsdl2-dev libsdl2-ttf-dev fonts-dejavu
```

#### For Fedora:

```bash
sudo dnf install SDL2-devel SDL2_ttf-devel dejavu-sans-fonts
```

#### For Arch Linux:

```bash
sudo pacman -S sdl2 sdl2_ttf ttf-dejavu
```

### Building the Project:

1. Clone the repository:

```bash
git clone https://github.com/leox00/BMemora.git
cd BMemora
```

2. Compile the project:

```bash
gcc -o bmemora main.c -lSDL2 -lSDL2_ttf
```

3. Run the application:

```bash
./bmemora
```

## Usage
When the application runs, a small input window will appear in the center of your screen. You can type your idea or note, and hit `Enter` to save it to your `.bmemora.txt` file. The window will close after saving your idea.

### Viewing the Saved Ideas
The ideas are saved in a plain text file located in your home directory as `.bmemora.txt`. You can view this file with any text editor or with the following command:

```bash
cat ~/.bmemora.txt
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact
Feel free to open an issue or create a pull request if you have any suggestions or improvements!
