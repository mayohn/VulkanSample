//
// Created by mayongheng on 2020/3/16.
//

#include "JniRenderer.h"
#include "../utils/utils.h"

void Program01Renderer::onSurfaceCreated(ANativeWindow *pWindow) {
    if (!init_global_layer_properties())return;
    createInstance();
    createSurface(pWindow);
    pickPhysicalDevice();
    initDeviceQueue();
}

void Program01Renderer::onSurfaceChanged(jint width, jint height) {
    init_window_size(width, height);
    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline(mGLSLPath);
    createFramebuffers();
    createCommandPool();
    createCommandBuffers();
    createSemaphores();

}

void Program01Renderer::onDrawFrame() {
    drawFrame();
}

void Program01Renderer::surfaceDestroyed() {
    cleanup();
}
