//
// Created by mayongheng on 2020/3/15.
//

#ifndef OPENGLES_JNIRENDERER_H
#define OPENGLES_JNIRENDERER_H

#include <jni.h>
#include <string.h>
#include <stdlib.h>
#include <android/native_window.h>
#include "../shaderloader/LoadShaders.h"

extern char *mGLSLPath;
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus


class Renderder {
public:
    virtual void onSurfaceCreated(ANativeWindow *pWindow) {}

    virtual void onSurfaceChanged(jint width, jint height) {}

    virtual void onDrawFrame() {}

    virtual void surfaceDestroyed() {}
};

class Program01Renderer : public Renderder {
public:
    void onSurfaceCreated(ANativeWindow *pWindow);

    void onSurfaceChanged(jint width, jint height);

    void onDrawFrame();

    void surfaceDestroyed();
};

#ifdef __cplusplus
}
#endif
#endif //OPENGLES_JNIRENDERER_H
