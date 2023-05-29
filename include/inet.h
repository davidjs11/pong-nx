#ifndef INET_H
#define INET_H

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct 
{
    int socket;
    struct sockaddr_in address;
    socklen_t size;

} socketInfo;

// init a server
int initServer(socketInfo *server);

// resolves a host for communication
socketInfo resolveHost(const char *ip, int port);


// message exchange stuff
int getMessage(socketInfo *receceiver, socketInfo *sender,
               char *buffer, int size);
int sendMessage(socketInfo *receiver, socketInfo *sender,
                char *buffer, int size);

#endif
