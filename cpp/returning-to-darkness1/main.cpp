// On linux compile with:
// g++ -std=c++17 main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

#include <iostream>

#include <SDL.h>
#include <glad/glad.h>
#include "game.cpp"
#include "renderer.cpp"

int main(int argc, char* argv[]) {

    Renderer renderer;
    renderer.init();

    bool gameIsRunning = true;
    while(gameIsRunning) {
        SDL_Event event;
        // Start our event loop
        while(SDL_PollEvent(&event)) {
            // Handle each specific event
            if(event.type == SDL_QUIT) {
                std::cout << "quitting game\n";
                gameIsRunning = false;
            }
            if(event.type == SDL_MOUSEMOTION) {
                std::cout << "mouse has been moved\n";
            }
            if(event.type == SDL_KEYDOWN) {
                std::cout << "a key has been pressed\n";
                if(event.key.keysym.sym == SDLK_0){
                    std::cout << "0 was pressed\n";
                }else{
                    std::cout << "0 was not pressed\n";
                }
            }
            // Retrieve the state of all of the keys
            // Then we can query the scan code of one or more
            // keys at a time
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]) {
                std::cout << "right arrow key is pressed\n";
            }
        }
        renderer.draw();
    }

    renderer.destroy();
    return 0;
}

