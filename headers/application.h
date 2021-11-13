#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "renderer.h"

// Main application class that handles running the application during its lifetime
class application {
protected: 
    int fps_; // Framerate to run at

    SDL_Window * window_;
    SDL_GLContext context_;
    // Renderer object to handle rendering (irrelevant of rest of application behavior hopefully)
    renderer * myRenderer_;

    // Dimensions of the window
    int window_width_, window_height_;

public:
    // Default constructor, calls initialize and sets running to false
    application();
    ~application();

};

#endif
