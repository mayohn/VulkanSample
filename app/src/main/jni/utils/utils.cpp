//
// Created by mayongheng on 2020/5/13.
//

#include "utils.h"
#include "../vulkan_wrapper/vulkan_wrapper.h" // Include Vulkan_wrapper and dynamically load symbols.
#include <malloc.h>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

VkInstance instance;
std::vector<const char *> validationLayers;
std::vector<const char *> deviceExtensions = {VK_KHR_SURFACE_EXTENSION_NAME,
                                              VK_KHR_ANDROID_SURFACE_EXTENSION_NAME};

bool init_global_layer_properties() {
    if (!InitVulkan()) {
        LOGE("initVulkan failed!");
        return false;
    }
    return true;
}
void initLayerProperties() {
    uint32_t instance_layer_count;
    VkResult res;
    VkLayerProperties *vk_props = nullptr;
    do {
        res = vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
        if (res) {
            LOGE("res!=null");
            return;
        }
        if (instance_layer_count == 0) {
            LOGI("instance_layer_count=0");
            return;
        }
        vk_props = (VkLayerProperties *) realloc(vk_props,
                                                 instance_layer_count * sizeof(VkLayerProperties));
        res = vkEnumerateInstanceLayerProperties(&instance_layer_count, vk_props);
    } while (res == VK_INCOMPLETE);
    for (uint32_t i = 0; i < instance_layer_count; i++) {

    }
}
void createInstance() {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pNext = nullptr;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    for (int i = 0; i < deviceExtensions.size(); i++) {
        LOGI("devicename=%s", deviceExtensions[i]);
    }
    initLayerProperties();
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.enabledExtensionCount = deviceExtensions.size();
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        LOGE("failed to create instance!");
    }
}


#ifdef __cplusplus
}
#endif // __cplusplus