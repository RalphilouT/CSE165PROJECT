you must have these libraries insalled: glut, glew, glfw, soil, and SDL2.

windows: use MSYS2 and pacman commands to install libraries.
    pacman -Syu
    pacman -S --needed base-devel mingw-w64-x86_64-toolchain
    pacman -S mingw-w64-x86_64-freeglut
    pacman -S mingw-w64-x86_64-glew
    pacman -S mingw-w64-x86_64-glfw
    pacman -S mingw-w64-x86_64-soil
    pacman -S mingw-w64-x86_64-SDL mingw-w64-x86_64-SDL_mixer mingw-w64-x86_64-SDL_image
    pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf

linux: use sudo apt-get install commands to install libraries. 
    apt-get install mesa-utils
    apt-get install freeglut3-dev
    apt-get install libglfw3-dev
    sudo apt-get install libsoil-dev
    apt-get install libsdl1.2-dev libsdl-mixer1.2-dev libsdl-image1.2-dev
    apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev

use command "make" to compile the code.

use command "make run" to run the game.
or just double click the .exe to launch the game from file explorer. 
