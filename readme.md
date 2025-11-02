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

#### Other Important Info
- Uses GCC compiler on all platforms
- **Untested on macOS**
- **Untested on ARM (AArch64)**

### Compilation Instructions
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


## How to Play
- There's barely a game currently
- All you can do is move a sprite around
    - Keyboard: WASD and ↑↓←→
    - Controller: DPad
        - Supported controllers: Most modern controlelrs including
            - Xbox 360, One, Series X
            - DualShock 4, DualSense
            - Switch (2) Pro Controller
