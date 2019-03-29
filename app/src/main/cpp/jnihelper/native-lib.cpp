#include <jni.h>
#include <string>
#include "Alog-priv.h"

#define LOG_TAG "zhouke_nativelib"

#include "WriterService.h"
#include "test.h"
#include "JNIHelp.h"

//Java_com_zkk_demo_MainActivity_stringFromJNI
jobject mobj;
jmethodID  callback;
WriterService * writerService;
JavaVM * jvm;
jclass strclass;
extern "C" JNIEXPORT jstring

JNICALL
test(
        JNIEnv *env,
        jobject thiz) {
    std::string hello = "Hello from C++";
    std::string test = "test ";
//    testFun();
    mobj = env->NewGlobalRef(thiz);
    jclass objclss = env->FindClass("com.zkk.demo.MainActivity");
    callback = env->GetMethodID(objclss,"callBack","(Ljava/lang/String;)V");
    ALOGI("FindClass >> 11");
    strclass = env->FindClass("java/lang/String");
    ALOGI("FindClass >> 22");
    writerService = new WriterService(mobj,callback);
    writerService->connectServer(jvm);
//    create_mult_process(2, 1);
    jstring  sttest = env->NewStringUTF(test.c_str());
    env->CallVoidMethod(mobj,callback,sttest);
    ALOGI("FindClass >> 33");

    return env->NewStringUTF(hello.c_str());
}
static JNINativeMethod gMethods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) test},
};

int register_android(JNIEnv *env) {
    return jniRegisterNativeMethods((C_JNIEnv *) env,
                                    "com/zkk/demo/MainActivity", gMethods, NELEM(gMethods));
}

static jclass findClass(C_JNIEnv *env, const char *className) {
    JNIEnv *e = reinterpret_cast<JNIEnv *>(env);
    return (*env)->FindClass(e, className);
}


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    ALOGI("JNI_OnLoad 执行");
    jvm = vm;
    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        ALOGI("get env failed");
        goto bail;
    }
    if (register_android(env) < 0) {
        ALOGI("动态注册失败");
        goto bail;
    }
    ALOGI("动态注册成功");
    result = JNI_VERSION_1_4;
    bail:
    return result;

}