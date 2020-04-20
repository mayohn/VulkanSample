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
std::vector<const char*> validationLayerNames = { "VK_LAYER_LUNARG_object_tracker" };
const float width = 800;
const float height = 600;
VkSemaphore imageAvailableSemaphore;
VkSemaphore renderFinishedSemaphore;
VkQueue graphicsQueue;
VkQueue presentQueue;
VkDevice logicalDevice;
VkRenderPassCreateInfo renderPassInfo = {};
VkSwapchainKHR swapChain;
std::vector<VkCommandBuffer> commandBuffer;


void Program01Renderer::onSurfaceCreated(ANativeWindow *pWindow) {
    // 2. check validation layer support
    checkValidationLayer();

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
            std::cout << validationLayerName << " is not supported . " << std::endl;
            throw std::runtime_error(" not all validation layer is supported . ");
        }
    }
}
