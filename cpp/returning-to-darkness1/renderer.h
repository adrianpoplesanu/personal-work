#ifndef __RENDERER_H
#define __RENDERER_H

#include <SDL.h>
#include <glad/glad.h>

class Renderer {
public:
    SDL_Window* window;

    Renderer();
    void init();
    void destroy();
    void draw();
};

#endif