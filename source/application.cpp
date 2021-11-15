#ifndef _APP_CPP_
#define _APP_CPP_

#include <stdio.h>

#include "../headers/application.h"
#include "../headers/vulkanRenderer.h"

application::application() {
    this->appName = "My Application";
    this->running_ = true;
    this->fps_ = 60;
    this->window_width_ = 720;
    this->window_height_ = 720;

    this->initialize();
}


application::~application() {
    delete this->myRenderer_;
}


void application::initialize() {
    // Create window for app
    this->window_ = SDL_CreateWindow(this->appName.c_str(), 10, 100, this->window_width_, this->window_height_, SDL_WINDOW_VULKAN);
    if (this->window_ == NULL) {
        printf("ERROR::APPLICATION\nDid not successfully create window\n");
        exit(EXIT_FAILURE);
    }
    
    this->myRenderer_ = new vulkanRenderer(this);

    this->myRenderer_->initialize();
}

void application::close() {
    this->running_ = false;

    // Closing window and closing library
    SDL_DestroyWindow(this->window_);
    SDL_Quit();
}

void application::start() {

    this->loop();
}

void application::loop() {
    
    SDL_Event event;
    double currTime,lastTime;
    // Last time is currently now
    lastTime = double(SDL_GetTicks()) / 1000.0f;
    while (this->running_) {
        // Get current time in milliseconds
        currTime = double(SDL_GetTicks()) / 1000.0f;
        while(SDL_PollEvent(&event)) {
            this->event(&event, currTime - lastTime);
        }
        double duration = double(1000)/double(this->fps_);
        SDL_Delay(duration);

        // Before entering new loop, this time is now last time
        lastTime = currTime;
    }
}


void application::event(SDL_Event * event, double deltaT) {
    switch (event->type) {
        case (SDL_QUIT):
            close();
            break;
    }

}
#endif
