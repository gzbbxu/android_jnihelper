//
// Created by gzbbxu on 2019/3/12.
//

#include <malloc.h>
#include "test.h"
#include "JNIHelp.h"
#include "Alog-priv.h"
#include "my_free.h"
#define LOG_TAG "zhouke_test"
void testFun(){
    ALOGV("test test 执行");
    char * tmp = malloc(sizeof(char)*10);
    FREE(tmp);
    ALOGV("test test 结束");
}