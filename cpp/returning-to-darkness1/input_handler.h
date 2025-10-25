#ifndef __INPUT_HANDLER_H
#define __INPUT_HANDLER_H

#include <SDL.h>
#include <glad/glad.h>

class InputHandler {
public:
    void handle_poll_events(bool&);
};

#endif