//
// Created by mayongheng on 2020/3/16.
//

#include "JniRenderer.h"
#include "../utils/utils.h"

void Program01Renderer::onSurfaceCreated(ANativeWindow *pWindow) {
    if (!init_global_layer_properties())return;
    createInstance();
}

void Program01Renderer::onSurfaceChanged(jint width, jint height) {

}

void Program01Renderer::onDrawFrame() {

}

void Program01Renderer::surfaceDestroyed() {


}
