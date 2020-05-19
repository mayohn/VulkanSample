//
// Created by mayongheng on 2020/5/13.
//

#include "utils.h"
#include "../vulkan_wrapper/vulkan_wrapper.h" // Include Vulkan_wrapper and dynamically load symbols.
#include <malloc.h>
#include <vector>
#include <set>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

VkInstance instance;
std::vector<const char *> validationLayers;
std::vector<const char *> instanceExtension = {VK_KHR_SURFACE_EXTENSION_NAME,
                                               VK_KHR_ANDROID_SURFACE_EXTENSION_NAME};
const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
int graphicsFamily = -1;
int presentFamily = -1;
int width, height;
VkDevice device;
VkQueue graphicsQueue;
VkQueue presentQueue;
VkSurfaceKHR surface;

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
    initLayerProperties();
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.enabledExtensionCount = instanceExtension.size();
    createInfo.ppEnabledExtensionNames = instanceExtension.data();
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        LOGE("failed to create instance!");
    }
}

bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> avaliableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         avaliableExtensions.data());
    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
    for (const auto &extension : avaliableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }
    return requiredExtensions.empty();
}

bool isDeviceSuitable(VkPhysicalDevice device) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    uint32_t i = 0;
    for (const auto &queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphicsFamily = i;
        }
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (presentSupport) {
            presentFamily = i;
        }
        i++;
    }
    bool extensionsSupport = checkDeviceExtensionSupport(device);
    LOGE("graphicsFamily=%d  presentFamily=%d extensionsSupport=%d ", graphicsFamily,presentFamily,extensionsSupport);
    if (graphicsFamily != -1 && presentFamily != -1 && extensionsSupport) {
        return true;
    } else {
        return false;
    }
}

void pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        LOGE("failed to find GPU with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    for (const auto &device:devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
        }
    }
    if (physicalDevice == VK_NULL_HANDLE) {
        LOGE("failed to find a suitable GPU!");
    }

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = graphicsFamily;
    queueCreateInfo.queueCount = 1;
    float queuePriorities = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriorities;

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = deviceExtensions.size();
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        LOGE("failed to create device !");
    }
}

void createSurface(ANativeWindow *pWindow) {
    VkAndroidSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.flags = 0;
    createInfo.window = pWindow;

    if (vkCreateAndroidSurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS) {
        LOGE("failed to create surface!");
    } else{
        LOGI("success to create surface!");
    }

}
void initDeviceQueue() {
    vkGetDeviceQueue(device, graphicsFamily, 0, &graphicsQueue);
    if (graphicsFamily == presentFamily) {
        presentQueue = graphicsQueue;
    } else {
        vkGetDeviceQueue(device, presentFamily, 0, &presentQueue);
    }
}
void cleanup() {
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyDevice(device, NULL);
    vkDestroyInstance(instance, nullptr);
}

#ifdef __cplusplus
}
#endif // __cplusplus