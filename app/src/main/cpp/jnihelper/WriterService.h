//
// Created by gzbbxu on 2019/3/29.
//

#ifndef JNIDEMO_WRITERSERVICE_H
#define JNIDEMO_WRITERSERVICE_H

#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
class WriterService {
public:
    static jobject  obj;
    static jmethodID  callback;
    void writeString();
    void readString();
    void connectServer(JavaVM *javaVM);
    WriterService(jobject obj,jmethodID pcallback);
    ~WriterService();

    static void * writeConsume(void * pVoid);
    static  void * readConsume(void * pVoid);

};


#endif //JNIDEMO_WRITERSERVICE_H
