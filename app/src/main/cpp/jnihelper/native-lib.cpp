#include <jni.h>
#include <string>
#include "Alog-priv.h"

#define LOG_TAG "zhouke_nativelib"

#include "WriterService.h"
#include "test.h"
#include "JNIHelp.h"

//Java_com_zkk_demo_MainActivity_stringFromJNI
jobject mobj;
jmethodID callback;
WriterService *writerService = nullptr;
JavaVM *jvm;
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
    callback = env->GetMethodID(objclss, "callBack", "(Ljava/lang/String;)V");

    return env->NewStringUTF(hello.c_str());
}
extern "C" JNIEXPORT void

JNICALL
createData(JNIEnv *env, jobject thiz) {
    if (writerService == nullptr) {
        writerService = new WriterService();
        writerService->connectServer(jvm);
    }
    timespec time;
    clock_gettime(CLOCK_REALTIME,&time);
    long nsec = time.tv_nsec;
    char temp[64] ={0};
    sprintf(temp,"%ld",nsec);
    writerService->writeString(temp,strlen(temp));
//    env->CallVoidMethod(mobj, callback, sttest);
}


static JNINativeMethod gMethods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) test},
        {"createData",    "()V",   (void*)createData}
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