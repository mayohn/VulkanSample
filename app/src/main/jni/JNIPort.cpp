//
// Created by mayongheng on 2020/3/14.
//
#include <bits/strcasecmp.h>
#include "com_mayohn_vulkan_jni_JniRenderer.h"
#include "renderers/JniRenderer.h"

//char *mGLSLPath;
Renderder *renderer = nullptr;
extern "C" JNIEXPORT void JNICALL Java_com_mayohn_vulkan_jni_JniRenderer_setGLSLPath
        (JNIEnv *env, jobject obj, jstring jpath, jstring tag) {
    mGLSLPath = const_cast<char *>(env->GetStringUTFChars(jpath, 0));
    const char *cTag = env->GetStringUTFChars(tag, 0);
     if (strcasecmp(cTag, "Program01Renderer") == 0) {
        renderer = new Program01Renderer();
    }
}


extern "C" JNIEXPORT void JNICALL Java_com_mayohn_vulkan_jni_JniRenderer_onSurfaceCreated
        (JNIEnv *env, jobject obj) {
    if (NULL != renderer) {
        renderer->onSurfaceCreated();
    }
}


extern "C" JNIEXPORT void JNICALL Java_com_mayohn_vulkan_jni_JniRenderer_onSurfaceChanged
        (JNIEnv *env, jobject obj, jint width, jint height) {
    if (NULL != renderer) {
        renderer->onSurfaceChanged(width, height);
    }
}


extern "C" JNIEXPORT void JNICALL Java_com_mayohn_vulkan_jni_JniRenderer_onDrawFrame
        (JNIEnv *env, jobject obj) {
    if (NULL != renderer) {
        renderer->onDrawFrame();
    }
}