#ifndef _RENDERER_PARENT_H_
#define _RENDERER_PARENT_H_

class application;
#include "application.h"

// A wrapper class with the goal to encapsulate all the tasks needed related to graphics rendering onto the screen
class renderer {
protected: 
    application * appInstance_;
public:
    // Default constructor, calls initialize and sets running to false
    renderer(application * app);

    virtual void initialize() = 0;

};

// Default constructor, calls initialize and sets running to false
renderer::renderer(application * app) {
    this->appInstance_ = app;
}

#endif
