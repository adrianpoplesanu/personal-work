#include "input_handler.h"

#include <iostream>

void InputHandler::handle_poll_events(bool &gameIsRunning) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            std::cout << "quitting game\n";
            gameIsRunning = false;
        }
        if(event.type == SDL_MOUSEMOTION) {
            std::cout << "mouse has been moved\n";
        }
        if(event.type == SDL_KEYDOWN) {
            std::cout << "a key has been pressed\n";
            if(event.key.keysym.sym == SDLK_0) {
                std::cout << "0 was pressed\n";
            }else{
                std::cout << "0 was not pressed\n";
            }
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_RIGHT]) {
            std::cout << "right arrow key is pressed\n";
        }
    }    
}