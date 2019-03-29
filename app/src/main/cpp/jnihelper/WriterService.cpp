//
// Created by gzbbxu on 2019/3/29.
//

#include "WriterService.h"
#include <jni.h>
#include <pthread.h>
#include <zconf.h>
#include "Alog-priv.h"
#include <string>

#define LOG_TAG "zhouke_nativelib"
jobject WriterService::obj = NULL;
jmethodID WriterService::callback = NULL;

WriterService::WriterService(jobject pobj, jmethodID pcall) {
    obj = pobj;
    callback = pcall;
}

void *WriterService::readConsume(void *pVoid) {
    JavaVM * jvm = static_cast<JavaVM *>(pVoid);
    JNIEnv *env = NULL;
    jint result = -1;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
    }

    jvm->AttachCurrentThread(&env,NULL);


    jvm->DetachCurrentThread();
    return NULL;
}
void *WriterService::writeConsume(void *pVoid) {
    ALOGI("writeConsume");
    JavaVM * jvm = static_cast<JavaVM *>(pVoid);
    JNIEnv *env = NULL;
    jint result = -1;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
    }

    jvm->AttachCurrentThread(&env,NULL);
    while(1){
        timespec time;
        clock_gettime(CLOCK_REALTIME,&time);
        long nsec = time.tv_nsec;
        char temp[64] ={0};
        sprintf(temp,"%ld",nsec);
    /*    jstring jstring1 ;
        env->CallVoidMethod(obj,callback,jstring1);
        env->DeleteLocalRef(jstring1)*/
        ALOGI("write consume11 %s ",temp);
//        jstring  jstring1  = charTojstring(env,temp,stringclass);
//char * p = "hello";
        jstring  jstring1 = env->NewStringUTF(temp);

        ALOGI("write consume22 %s ",temp);

        env->CallVoidMethod(obj,callback,jstring1);
        env->DeleteLocalRef( jstring1);
//        ALOGI("write consume %s ",temp);
        sleep(1);
    }

    jvm->DetachCurrentThread();
    return NULL;
}


void WriterService::readString() {

}

void WriterService::writeString() {

}

void WriterService::connectServer(JavaVM *javaVM) {
    pthread_t readpid;
    pthread_t writepid;
    pthread_create(&writepid,NULL,writeConsume,javaVM);
//    pthread_create(&readpid,NULL,readConsume,NULL);
}