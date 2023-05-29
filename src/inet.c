#include "inet.h"

socketInfo resolveHost(const char *ip, int port)
{
    socketInfo server;
    memset(&server, 0, sizeof(server));

    // create server UDP socket
    server.socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server.socket < 0)
    {
	    perror("[-] initServer in socket()");
	    memset(&server, 0, sizeof(server));
	    return server;
    }

    // set address info
    server.address.sin_family = AF_INET;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = inet_addr(ip);

    return server;
}

void setSocketTimeout(int socket)
{
    struct timeval readTimeout;
    readTimeout.tv_sec = 0;
    readTimeout.tv_usec = 10;
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO,
	       &readTimeout, sizeof(readTimeout));
}


int initServer(struct socketInfo *server)
{
    // bind server address to the socket
    int tmp = bind(server->socket, (struct sockaddr *) &(server->address),
	               sizeof(server->address));

    if (tmp < 0)
    {
        perror("[-] initServer in bind()");
        memset(server, 0, sizeof(*server));
        return -1;
    }

    return 0;
}

int getMessage(
    struct socketInfo *receiver, struct socketInfo *sender,
    char *buffer, int bufferSize)
{
    int tmp;
    memset(buffer, 0, bufferSize);
    sender->size = sizeof(sender->address);

    tmp = recvfrom(receiver->socket, buffer, bufferSize, 0,
	      (struct sockaddr *) &(sender->address),
	      &(sender->size));
    printf("tmptmptmp: %d\n", tmp);
    return tmp;
}

int sendMessage(
    struct socketInfo *receiver, struct socketInfo *sender,
    char *buffer, int bufferSize)
{
   int tmp;

   tmp = sendto(sender->socket, buffer, bufferSize, 0,
	       (struct sockaddr *) &(receiver->address),
	        sizeof(receiver->address));

   return tmp;
}
