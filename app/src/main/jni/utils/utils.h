//
// Created by mayongheng on 2020/5/13.
//

#ifndef VULKANSAMPLE_UTILS_H
#define VULKANSAMPLE_UTILS_H
#include <android/log.h>

#define LOG_TAG    "test===="
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
bool init_global_layer_properties();
void createInstance();
void initLayersProperties();
#ifdef __cplusplus
}
#endif // __cplusplus
#endif //VULKANSAMPLE_UTILS_H
