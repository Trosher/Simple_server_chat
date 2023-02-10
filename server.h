#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define DEFAULT_PORT 1701
#define ERROR_S "SERVER ERROR: "
#define BUFFER_SIZE 1024
#define EXIT_SYMBOL '#'

bool is_client_connection_close(const char* msg);

#endif  // SERVER_H_