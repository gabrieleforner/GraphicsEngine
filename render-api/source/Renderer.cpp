#include "../include/core/Renderer.h"

#include <GLFW/glfw3.h>
#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.h>


static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
    }
    return VK_FALSE;
}

VkDebugUtilsMessengerCreateInfoEXT createDebugMessengerInfo() {
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    return createInfo;
}

void Renderer::createInstance(bool engineerMode)
{
    VkResult result;
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "FastGFX";
    appInfo.pEngineName = "FastGFX";

    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.pApplicationInfo = &appInfo;

#ifdef __APPLE__
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

    // MARK: Enumerate REQUIRED EXTENSIONS
    uint32_t glfwExtCount;
    std::vector<const char *> engine_vk_extensions;
    const char **glfwRequiredExt = glfwGetRequiredInstanceExtensions(&glfwExtCount);

    for(uint32_t i = 0; i > glfwExtCount; i++) {
        engine_vk_extensions.emplace_back(glfwRequiredExt[i]);
    }
    // MARK: Enumerate SUPPORTED EXTENSIONS
    uint32_t supportedExtCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtCount, nullptr);
    std::vector<VkExtensionProperties> vk_extension_properties(supportedExtCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtCount, vk_extension_properties.data());

#ifdef __APPLE__
    engine_vk_extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
    if (engineerMode) {
        engine_vk_extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    if (engineerMode) {
       if(hasValidationLayer(layers, "VK_LAYER_KHRONOS_validation")) {
           std::cout << "Vulkan validation layer is present! Enabling engineer mode...." << std::endl;
       }
       else {
            std::cerr << "Vulkan validation layer is not present! Engineer Mode will not be available!" << std::endl;
           exit(-1);
        }
    }

    std::vector<const char*> enabledLayers;
    enabledLayers.reserve(layers.size());
    std::cout << "Enabled layers: " << std::endl;
    for (auto& layer : layers) {
        if (std::strcmp(layer.layerName, "VK_LAYER_LUNARG_api_dump") != 0) {
            std::cout << '\t' << layer.layerName << std::endl;
            enabledLayers.emplace_back(layer.layerName);
        }
    }

    createInfo.enabledLayerCount = enabledLayers.size();
    createInfo.ppEnabledLayerNames = enabledLayers.data();
    createInfo.enabledExtensionCount = engine_vk_extensions.size();
    createInfo.ppEnabledExtensionNames = engine_vk_extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debg_create_info_ext = createDebugMessengerInfo();
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = &debg_create_info_ext;
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(this->engine_instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(this->engine_instance, &debg_create_info_ext, nullptr, &this->engModeCallbackHandle);
    }

    result = vkCreateInstance(&createInfo, nullptr, &engine_instance);
    if (result != VK_SUCCESS) { throw std::runtime_error(string_VkResult(result)); }

    else { printSuccess("VkInstance Created!"); }

}
void Renderer::destroy() const {
    if (this->engModeCallbackHandle != VK_NULL_HANDLE)
    {
        auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(
            this->engine_instance, "vkDestroyDebugUtilsMessengerEXT"));
        if (func != nullptr)
            {
            func(this->engine_instance, this->engModeCallbackHandle, nullptr);
        }
    }
    vkDestroyInstance(this->engine_instance, nullptr);
}
