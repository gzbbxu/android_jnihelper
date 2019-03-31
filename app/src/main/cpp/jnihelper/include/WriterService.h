//
// Created by gzbbxu on 2019/3/29.
//

#ifndef JNIDEMO_WRITERSERVICE_H
#define JNIDEMO_WRITERSERVICE_H

#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SyncQueue.hpp"

class WriterService {
public:
    static  int msgType ;
    static SyncQueue<char*> *syncQueue;

    void writeString(char * pdata,int len);

    void readString();

    void connectServer(JavaVM *javaVM);


    WriterService();

    ~WriterService();

    static void *writeConsume(void *pVoid);

    static void *readConsume(void *pVoid);


    static void reconnect();
};


#endif //JNIDEMO_WRITERSERVICE_H
