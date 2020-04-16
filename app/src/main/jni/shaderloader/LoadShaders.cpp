#include <stdio.h>
#include "LoadShaders.h"
#include "../renderers/JniRenderer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
static const char *ReaderShader(const char *fileName) {
    char *glslPath = (char *) malloc(strlen(mGLSLPath) + strlen(fileName));
    strcpy(glslPath, mGLSLPath);
    strcat(glslPath, fileName);
    LOGI("文件地址=%s", glslPath);
    FILE *inflie = fopen(glslPath, "rb");
    if (!inflie) {
        LOGI("文件打开失败%s", fileName);
        return NULL;
    }
    fseek(inflie, 0, SEEK_END);
    int len = ftell(inflie);
    fseek(inflie, 0, SEEK_SET);
    char *source = new char[len + 1];
    fread(source, 1, len, inflie);
    fclose(inflie);
    source[len] = 0;
    return source;

}

#ifdef __cplusplus
}
#endif // __cplusplus