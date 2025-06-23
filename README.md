
# arkanoid
SDL2 clone of the classic 1986 arcade game *Arkanoid* by Taito written in C++ as a final project for the Programming and Algorithmics 2 course at FIT CTU.

## Demo
<img src="https://github.com/nadrajak/arkanoid/blob/main/demo.gif" alt="Demo gif" width="100%"/>

## Game Description
You control a paddle at the bottom of the screen, bouncing a ball to break bricks. Letting the ball fall below the paddle costs a life. Some bricks drop power-ups that enhance the paddle's abilities. Only one power-up can be active at a time; picking up a new one replaces the old. Losing a life clears all active power-ups.
### Menu Controls
- `[W]`/`[S]` to navigate
- `[RETURN]` to select
- `[ESCAPE]` to go back
### Game Controls
- `[A]`/`[D]` to move the paddle
- `[SPACE]` to launch a ball

## Building
### Prerequisites
- C++ compiler with C++14 support
- SDL2, SDL2_ttf development libraries
- GNU Make

On Ubuntu/Debian you can install the prerequisites using:
```bash
sudo apt-get install build-essential libsdl2-dev libsdl2-ttf-dev 
```
### Build & Run
```bash
cd arkanoid
make run
```
