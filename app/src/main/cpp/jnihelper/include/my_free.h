//
// Created by gzbbxu on 2019/3/12.
//

#ifndef JNIDEMO_MY_FREE_H
#define JNIDEMO_MY_FREE_H


#ifndef FREE
#define FREE(pvoid) \
    if (NULL != (pvoid)) { \
        void** pvTmp = (void**)&(pvoid); \
        free(*pvTmp); \
        *pvTmp = NULL; \
    }
#endif // FREE



#endif //JNIDEMO_MY_FREE_H
