//
// Created by mayongheng on 2020/3/15.
//

#ifndef OPENGLES_JNIRENDERER_H
#define OPENGLES_JNIRENDERER_H

#include <jni.h>
#include <string.h>
#include <stdlib.h>
#include "../shaderloader/LoadShaders.h"
extern char *mGLSLPath;
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus


class Renderder {
public:
    virtual void onSurfaceCreated() {}

    virtual void onSurfaceChanged(jint width, jint height) {}

    virtual void onDrawFrame() {}
};

class Program01Renderer : public Renderder {
public:
    void onSurfaceCreated();

    void onSurfaceChanged(jint width, jint height);

    void onDrawFrame();
};

#ifdef __cplusplus
}
#endif
#endif //OPENGLES_JNIRENDERER_H
