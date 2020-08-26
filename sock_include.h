#ifndef _SOCK_INCLUDE_H_
#define _SOCK_INCLUDE_H_

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <pthread.h>
#define SERV_PORT 8000

#define SERV_IP "192.168.161.128"

int Bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
int Socket(int domain, int type, int protocol);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif