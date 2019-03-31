//
// Created by gzbbxu on 2019/3/29.
//

#include "WriterService.h"
#include <jni.h>
#include <pthread.h>
#include <zconf.h>
#include "Alog-priv.h"
#include <string>
#include <endian.h>
#include "serverSocket.h"

#define LOG_TAG "zhouke_nativelib"
extern jobject mobj;
extern jmethodID callback;
int WriterService::msgType = 1111;
SyncQueue<char *> *WriterService::syncQueue;

WriterService::WriterService() {
    /* obj = pobj;
     callback = pcall;*/

    syncQueue = new SyncQueue<char *>(100);
}

void *WriterService::readConsume(void *pVoid) {
    JavaVM *jvm = static_cast<JavaVM *>(pVoid);
    JNIEnv *env = NULL;
    jint result = -1;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
    }

    jvm->AttachCurrentThread(&env, NULL);
    while (1) {
        //读取前4个字节
        int32_t netLen = 0; //网络字节序的长度

        int ret = readFromServer(&netLen, sizeof(int32_t));
        if (ret == -1) {
            ALOGI("读取 失败 异常");
            sleep(5);
        } else if (ret < sizeof(int32_t)) {
            ALOGI("读取函数 客户端关闭");
            sleep(5);
        }

    }

    jvm->DetachCurrentThread();
    return NULL;
}

void *WriterService::writeConsume(void *pVoid) {
    ALOGI("writeConsume");
    JavaVM *jvm = static_cast<JavaVM *>(pVoid);
    JNIEnv *env = NULL;
    jint result = -1;
    int preLen = sizeof(int32_t) * 2;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
    }

    jvm->AttachCurrentThread(&env, NULL);
    reconnect();
    while (1) {


        /*    jstring jstring1 ;
            env->CallVoidMethod(obj,callback,jstring1);
            env->DeleteLocalRef(jstring1)*/
        ALOGI("开始取数据 ");
//        jstring  jstring1  = charTojstring(env,temp,stringclass);
//char * p = "hello";
        char *pWriteData;
        syncQueue->Take(pWriteData);
        ALOGI("取数据成功");
        if (pWriteData) {
            int *pdatalen = reinterpret_cast<int *>(pWriteData);
            //长度
            int localLen = *pdatalen;
            int netlen = htonl(localLen);
            *pdatalen = netlen;
            //类型

            int32_t *ptype = reinterpret_cast<int32_t *>(pWriteData + sizeof(int32_t));
            int _msg_type_l = *ptype;//当前消息类型 本地字节序

            *ptype = htonl(_msg_type_l);

//            *ptype = msgType;//保留字段 type

            if (writeToServer(pWriteData, preLen + localLen) < 0) {
                ALOGI("写数据失败5s 后重连");
                closeSocket();
                reconnect();
                //todo 清理缓存的数据。
//                syncQueue->clear();
                delete pWriteData;
                sleep(5);
                continue;
            }
            ALOGI("写数据成功");
            delete pWriteData;
        }

        /*   env->CallVoidMethod(mobj, callback, jstring1);
           env->DeleteLocalRef(jstring1);*/
//        ALOGI("write consume %s ",temp);
    }

    jvm->DetachCurrentThread();
    return NULL;
}

void WriterService::reconnect() {
    int bindResult;
    if ((bindResult = bindListenSocket()) < 0) {
        if (bindResult == BIND_ERROR) {
            ALOGI("绑定失败>>");
        } else if (bindResult == CONNECT_ERROR) {
            ALOGI("连接失败>>");
        }

    } else {
        ALOGI("连接成功");
    }
}


void WriterService::readString() {

}

void WriterService::writeString(char *pdata, int len) {
    int preLen = sizeof(int32_t) * 2;
    //len 不包括\0  len 是本地字节序
    char *rPdata = new char[preLen + len]; //
    int32_t *plen = (int32_t *) rPdata;
    *plen = len; //长度
    int32_t *ptype = reinterpret_cast<int32_t *>(rPdata + sizeof(int32_t));
    *ptype = msgType;//保留字段 type
    memcpy(rPdata + preLen, pdata, len);

    syncQueue->Put(rPdata);
}

void WriterService::connectServer(JavaVM *javaVM) {
    pthread_t readpid;
    pthread_t writepid;
    pthread_create(&writepid, NULL, writeConsume, javaVM);
//    pthread_create(&readpid,NULL,readConsume,NULL);
}

WriterService::~WriterService() {

}