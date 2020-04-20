//
// Created by mayongheng on 2020/3/16.
//

#include "JniRenderer.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

VkInstance instance;
std::vector<const char *> validationLayerNames = {"VK_LAYER_LUNARG_object_tracker"};
const float width = 800;
const float height = 600;
VkSemaphore imageAvailableSemaphore;
VkSemaphore renderFinishedSemaphore;
VkQueue graphicsQueue;
VkQueue presentQueue;
VkDevice logicalDevice;
VkRenderPassCreateInfo renderPassInfo = {};
VkSwapchainKHR swapChain;
VkSurfaceKHR surface;
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
std::vector<VkCommandBuffer> commandBuffer;

void checkValidationLayer();

void createInstance();

void createPhysicalDevice();

void createSurface(ANativeWindow *pWindow);

void creatingDeviceQueue();

void Program01Renderer::onSurfaceCreated(ANativeWindow *pWindow) {
    InitVulkan();
    // 2. check validation layer support
    checkValidationLayer();
    // 3. Create Instance
    createInstance();
    createPhysicalDevice();
    createSurface(pWindow);
    creatingDeviceQueue();
}

void Program01Renderer::onSurfaceChanged(jint width, jint height) {

}

void Program01Renderer::onDrawFrame() {

}

void Program01Renderer::surfaceDestroyed() {


}

void checkValidationLayer() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (auto validationLayerName : validationLayerNames) {
        bool support = false;
        for (auto supportedLayerName : availableLayers) {
            if (strcmp(supportedLayerName.layerName, validationLayerName) == 0) {
                support = true;
                break;
            }
        }
        if (support == false) {
            LOGI(" not all validation layer is supported . ");
        }
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
    appInfo.pNext = NULL;

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledExtensionCount = 0;
    instanceCreateInfo.ppEnabledExtensionNames = NULL;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledLayerNames = NULL;

    if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
        LOGI("failed to create instance!");
    } else {
        LOGI("Success to create instance!");
    }
}

void createPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
    if (deviceCount == 0) {
        LOGI("failed to find physical device .");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // 4.2 choose a suitable physical device
    for (const auto &device : devices) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
            deviceFeatures.geometryShader) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        LOGI("no suitable device.");
    }
}

void createSurface(ANativeWindow *pWindow) {
    VkAndroidSurfaceCreateInfoKHR createInfo{
            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            .pNext = NULL,
            .flags = 0,
            .window = pWindow};
    if (vkCreateAndroidSurfaceKHR(instance, &createInfo, NULL,
                                  &surface) != VK_SUCCESS) {
        LOGI(" failed to create window surface .");
    } else {
        LOGI(" Success to create window surface .");
    }
}

void creatingDeviceQueue() {
// 6.1 find a queueFamily which can be a graphics queue and a present queue
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
                                             queueFamilies.data());

    int i = 0;
    int queue_ind = -1;

    for (const auto &queueFamily : queueFamilies) {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT &&
            presentSupport) {
            queue_ind = i;
        }
        i++;
    }

    if (queue_ind == -1) {
        LOGI("No suitable queue .");
    } else {
        LOGI("have %d suitable queue .", queue_ind);
    }

    // 6.2 fill VkDeviceQueueCreateInfo
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queue_ind;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;
}