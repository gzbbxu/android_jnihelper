#include <jni.h>
#include <string>
#include "Alog-priv.h"
#define LOG_TAG "zhouke_nativelib"
#include "test.h"
#include "JNIHelp.h"

//Java_com_zkk_demo_MainActivity_stringFromJNI
extern "C" JNIEXPORT jstring

JNICALL
test(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    std::string  test= "test ";
//    testFun();
    create_mult_process(2,1);
    env->NewStringUTF(test.c_str());

    return env->NewStringUTF(hello.c_str());
}
static JNINativeMethod gMethods[]={
        {"stringFromJNI","()Ljava/lang/String;",(void*)test},
};

 int register_android(JNIEnv * env){
    return jniRegisterNativeMethods((C_JNIEnv*)env,
                                                 "com/zkk/demo/MainActivity", gMethods, NELEM(gMethods));
}

static jclass findClass(C_JNIEnv* env, const char* className) {
    JNIEnv* e = reinterpret_cast<JNIEnv*>(env);
    return (*env)->FindClass(e, className);
}


jint JNI_OnLoad(JavaVM * vm,void* reserved){
    ALOGV("JNI_OnLoad 执行");
    JNIEnv * env = NULL;
    jint result = -1;
    if(vm->GetEnv((void**) &env,JNI_VERSION_1_4)!=JNI_OK){
        ALOGV("get env failed");
        goto bail;
    }
    if(register_android(env)<0){
        ALOGV("动态注册失败");
        goto bail;
    }
    ALOGV("动态注册成功");
    result = JNI_VERSION_1_4;
    bail:
    return result;

}