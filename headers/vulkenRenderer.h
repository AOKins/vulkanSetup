#ifndef _APP_VULKAN_H_
#define _APP_VULKAN_H_


#include <SDL2/SDL_vulkan.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include "application.h"
#include "renderer.h"
// Main application class that handles running the application
class vulkenRenderer : renderer {
private: 
    VkInstance * vk_instance_;
public:
    // Constructor, requires an instance of the application to refer to if needed
    vulkenRenderer(application * app);
    ~vulkenRenderer();

};

#endif
