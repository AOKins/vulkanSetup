#ifndef _APP_VULKAN_H_
#define _APP_VULKAN_H_


#include <SDL2/SDL_vulkan.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include "application.h"
#include "renderer.h"
// Main application class that handles running the application
class vulkanRenderer : public renderer {
private: 
    // Vulkan instance
    VkInstance * vk_instance_;
    // The logical device to be used by renderer
    VkDevice * device_;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
    VkDebugUtilsMessengerEXT debugMessenger;

    bool checkValidationLayerSupport();

    std::vector<const char*> getRequiredExtensions();

    static VKAPI_ATTR VkBool32 debugCallbackFunc(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

    VkResult setupDebugCommunications(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator);
    void destroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator);

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
public:
    // Constructor, requires an instance of the application to refer to if needed
    vulkanRenderer(application * app);
    ~vulkanRenderer();

    void initialize();
    

};

#endif
