// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

#include <iostream>

#include <SDL.h>
#include <glad/glad.h>
#include "game.cpp"
#include "renderer.cpp"
#include "input_handler.cpp"

int main(int argc, char* argv[]) {

    Renderer renderer;
    InputHandler inputHandler;
    renderer.init();

    bool gameIsRunning = true;
    while(gameIsRunning) {
        inputHandler.handle_poll_events(gameIsRunning);
        renderer.draw();
    }

    renderer.destroy();
    return 0;
}

