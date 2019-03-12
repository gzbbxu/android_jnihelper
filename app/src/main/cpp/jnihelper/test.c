//
// Created by gzbbxu on 2019/3/12.
//

#include <malloc.h>
#include <zconf.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <asm/errno.h>
#include "test.h"

#include "JNIHelp.h"
#include "Alog-priv.h"
#include "my_free.h"

#define LOG_TAG "zhouke_test"

void testFun(int i) {
    ALOGV("test test 进程 %d 执行 任务%d", getpid(), i);
    char *tmp = malloc(sizeof(char) * 10);
    sleep(1);
    FREE(tmp);
    ALOGV("test test 结束  %d 任务 %d ", getpid(), i);
}

void create_mult_process(int procesNum, int loopNum) {

    int i = 0;
    for (i = 0; i < procesNum; i++) {
        pid_t pid = fork();
        if (pid < 0) {
//            perror("forkerror");
            ALOGV("第% dforkerror ",i);
            return;
        } else if (pid > 0) {
            ALOGV("第% 父進程 ",i);
            //parent
        } else if (pid == 0) {
            //child
            ALOGV("第%d个父进程 轮询 ",i);
            int j = 0;
            for (j = 0; j < loopNum; j++) {
                testFun(j);
            }
            exit(0);
        }
    }
    while (1) {
        int status;
        int ret;
        if ((ret = wait(&status)) == -1) {
            if (ret == EINTR) {
                //父进程wait() 函数阻塞过程中，有可能被别的信号中断，需要做异常处理
                continue;
            }
            ALOGV("进程 号 %d 被回收", ret);
            break;
        }
    }

}
