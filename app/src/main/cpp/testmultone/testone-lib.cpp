//
// Created by gzbbxu on 2019/2/23.
//
#include <jni.h>
#include <string>
extern "C" JNIEXPORT jstring

JNICALL
test(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "test two C++";
    std::string  test= "test ";
    env->NewStringUTF(test.c_str());
    return env->NewStringUTF(hello.c_str());
}