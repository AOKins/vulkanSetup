#ifndef _RENDERER_CPP_
#define _RENDERER_CPP_
#include "../headers/renderer.h"

#include <stdio.h>


// Default constructor, calls initialize and sets running to false
renderer::renderer(application * app) {
    this->appInstance_ = app;
}

renderer::~renderer() {

}

#endif
