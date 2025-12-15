NES AOROM Menu

<img width="770" height="724" alt="image" src="https://github.com/user-attachments/assets/585e247e-82c5-47ca-b2c3-585f6c1bedbc" />


Menu example for an NES project based on AOROM (mapper 7)

This repository contains the source code of a demonstration menu for the NES (Nintendo Entertainment System), built using classic NES development tools and targeting the AOROM mapper (iNES Mapper 7). It serves as a useful starting point for anyone interested in NES homebrew game or demo development, especially projects that require a custom menu system and basic audio support.

📦 Contents

The project includes:

C source code: menu.c — menu logic and interface handling

ASM / startup code: crt0.s — startup routines and entry point

Audio and music: sound and music modules

Configuration: nes_aorom.cfg — linker configuration for mapper 7

NES support library: neslib.h / neslib.s — helper functions and utilities

Build scripts: build.bat for assembling and linking

🕹️ About AOROM (Mapper 7)

NES cartridges use different mappers — hardware mechanisms that control ROM and VRAM bank switching.
AOROM is part of the AxROM family and implements iNES Mapper 7, with the following characteristics:

PRG ROM bank switching

CHR RAM instead of CHR ROM

No additional PRG RAM

Single-screen nametable mirroring

This makes AOROM especially suitable for experiments, demos, and relatively simple games that benefit from a large PRG space without complex CHR layouts.

🛠️ Building the Project

To build the project, you will need standard NES development tools (for example cc65 / ca65 / ld65, and an emulator such as FCEUX for testing):

Install an NES development toolchain (e.g. cc65).

Run build.bat or assemble and link the project manually.

The resulting .nes ROM can be tested in an emulator or on real hardware.

📌 How to Use

Study menu.c and neslib.h to understand how the menu system works.

Examine the sound and music code to see how audio events are handled.

Modify and reuse the code as a foundation for your own NES homebrew projects.
