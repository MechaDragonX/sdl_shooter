# SDL Shooter

## General Information
- A simple shoot 'em up hame coding in C using SDL2
- Will just have a single bullet hell style boss fight
- The goal is to port to this to a variety of other platforms, starting with Sony PlayStation Vita (ARM Cortex-A9 MPCore CPU)

## Platform Availabilty
### Current
- PC
    - Linux
    - Windows
    - macOS
### Future
- PlayStation Vita

## PC Compilation Information
### Prerequisites
#### Packages
- SDL2
    - Linux:
        - Debian: `libsdl2-dev`
        - Arch: `sdl2`
        - Fedora: `SDL2-devel`
    - Windows:
        - MSYS2: `<package prefix>-x86_64-SDL2`
    - macOS:
        - Homebrew: `sdl2`
- SDL2_image
    - Linux:
        - Debian: `libsdl2-image-dev`
        - Arch: `sdl2_image`
        - Fedora: `SDL2_image`
    - Windows:
        - MSYS2: `<package prefix>-x86_64-SDL2_image`
    - macOS:
        - Homebrew: `sdl2_image`
#### Information
- Uses GCC compiler on all platforms
    - If `gcc`is an alias to `clang` on your macOS system, it'll use that

### Compilation Instructions
0. If you're on Nix / Nix OS:
   ```
   nix develop
   ```
1. ```
   make setup
   ```
2. ```
   make
   ```
3. On Unix:
   ```
   ./bin/shooter
   ```
   On Windows:
   ```
   ./bin/shooter.exe
   ```
   Naturally doubleclicking the executable now should work too (assuming permissions are in order).
### Other Commands
- ```
  make clean
  ```
  Remove all compiled object files and executable

## How to Play
- There's barely a game currently
- All you can do is move a sprite around
    - Keyboard: WASD and ↑↓←→
    - Controller: DPad
        - Supported controllers: All modern controllers including
            - Xbox 360, One, Series X
                - Other XInput controlllers
            - DualShock 3 (SDL supports it, but I couldn't get it to work), DualShock 4, DualSense
            - Switch (2) Pro Controller, Switch (2) Joy-Cons (only as a pair)
                - Controllers that act like one, such as 8BitDo controllers in Switch mode


## FAQ
- When will this be finished?
    - I don't know
- Is there a release I can download?
    - It isn't even a game yet, so no
