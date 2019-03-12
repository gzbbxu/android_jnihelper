//
// Created by gzbbxu on 2019/3/12.
//

#ifndef JNIDEMO_TEST_H
#define JNIDEMO_TEST_H

#include <jni.h>
#ifdef __cplusplus
extern "C"
{
#endif //cpp

    void testFun(int i);
    void create_mult_process(int procesNum,int loopNum);

#ifdef __cplusplus
}
#endif //cpp


#endif //JNIDEMO_TEST_H
