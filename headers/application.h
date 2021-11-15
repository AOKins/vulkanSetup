#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <vector>

#include "renderer.h"

// Main application class that handles running the application during its lifetime
class application {
protected: 
    bool running_;
    int fps_; // Framerate to run at
    // Renderer object to handle rendering (irrelevant of rest of application behavior hopefully)
    renderer * myRenderer_;

    // Dimensions of the window
    int window_width_, window_height_;

    // Initialize libraries and things
    void initialize();

    void close();

    void event(SDL_Event * event, double deltaT);

public:
    // Public Info
    // Pointer to the main window
    SDL_Window * window_;
    // Name of the application
    std::string appName;

    // Default constructor, calls initialize and sets running to false
    application();
    ~application();

    void start();

    void loop();
    

};

#endif
