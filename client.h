#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define EXIT_SYMBOL '#'
#define DEFAULT_PORT 1701
#define BUFFER_SIZE 1024

bool is_client_connection_close(const char* msg);

#endif  // CLIENT_H_