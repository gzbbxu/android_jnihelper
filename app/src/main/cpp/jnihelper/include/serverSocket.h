//
// Created by gzbbxu on 2019/3/31.
//

#ifndef JNIDEMO_SERVERSOCKET_H
#define JNIDEMO_SERVERSOCKET_H
#define  BIND_ERROR -1
#define  CONNECT_ERROR -2

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int server_sockfd;
int bindListenSocket();

int writeToServer(const void *buf, size_t count);

int readFromServer(const void * buf ,size_t count);
int closeSocket();

#ifdef __cplusplus
}
#endif
#endif //JNIDEMO_SERVERSOCKET_H
