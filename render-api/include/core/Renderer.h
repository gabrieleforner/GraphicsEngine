#pragma once
#include <iostream>
#include <util/ConsoleLog.h>
#include <vulkan/vulkan.h>
#include <vector>

class Renderer
{
public:
    VkInstance engine_instance = nullptr;
    VkDebugUtilsMessengerEXT engModeCallbackHandle = nullptr;

    void createInstance(bool engineerMode);
    void destroy();
};

