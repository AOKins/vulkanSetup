#ifndef _VULKEN_RENDERER_CPP_
#define _VULKEN_RENDERER_CPP_

#include "../headers/vulkanRenderer.h"

#include <stdio.h>
#include <vector>
#include <cstring>

// Default constructor, calls initialize and sets running to false
vulkanRenderer::vulkanRenderer(application * app) : renderer::renderer(app) {
}

vulkanRenderer::~vulkanRenderer() {
    if (this->enableValidationLayers) {
        destroyDebugUtilsMessengerEXT(NULL);
    }

    vkDestroyInstance(*this->vk_instance_, NULL);
}

void vulkanRenderer::initialize() {
    // Quick validation check
    if (this->enableValidationLayers && !checkValidationLayerSupport()) {
        printf("ERROR: Validation layers requested unavailable!\n");
        throw std::exception();        
        
    }

    // Setting up our app info for Vulkan
    VkApplicationInfo info;
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = this->appInstance_->appName.c_str();
    info.applicationVersion = VK_MAKE_VERSION(1,0,0);
    info.pEngineName = "No Engine";
    info.engineVersion = VK_MAKE_VERSION(1,0,0);
    info.apiVersion = VK_API_VERSION_1_0;
    info.pNext = NULL;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &info;
    createInfo.pApplicationInfo;

    std::vector<const char*> extensions = this->getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (this->enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    VkResult r = vkCreateInstance(&createInfo, NULL, this->vk_instance_);
    if (r != VK_SUCCESS) {
        printf("ERROR::VK_RENDERER_INITIALIZATION::CREATE_INSTANCE (Failed to create Vulkan instance!) VULKAN RESULT CODE: %d\n", r);
        throw std::exception();
    }
}

bool vulkanRenderer::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);

    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    for (int j = 0; j < this->validationLayers.size(); j++) {
        bool layerFound = false;
        for (int i = 0; i < layerCount; i++) {
            if (strcmp(layers[i].layerName,this->validationLayers[j]) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}

std::vector<const char*> vulkanRenderer::getRequiredExtensions() {
    uint32_t extCount = 0;
    SDL_Vulkan_GetInstanceExtensions(this->appInstance_->window_, &extCount, NULL);
    std::vector<const char*> extensions(extCount);

    SDL_Vulkan_GetInstanceExtensions(this->appInstance_->window_, &extCount, extensions.data());

    if (this->enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

VKAPI_ATTR VkBool32 vulkanRenderer::debugCallbackFunc(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, 
                                                                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        printf("validation layer|%s\n", pCallbackData->pMessage);
    }
    return VK_FALSE;
}

VkResult vulkanRenderer::setupDebugCommunications(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator) {
    
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(*this->vk_instance_, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(*this->vk_instance_, pCreateInfo, pAllocator, &this->debugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
void vulkanRenderer::destroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(*this->vk_instance_, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(*this->vk_instance_, this->debugMessenger, pAllocator);
    }
}

void vulkanRenderer::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = this->debugCallbackFunc;
}

#endif
