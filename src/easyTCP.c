#include "easyTCP.h"


/// server functions /////////////////////////////////////////////////
int initServer(struct socketInfo *server, int port, int backlog)
{
    int tmp; // temporal values for error handling
    server->port = port;
    server->backlog = backlog;

    // create socket file descriptor
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!server->socket)
    {
        perror("[-] initServer() in socket()");
        return -1;
    }

    // config server address
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_family = AF_INET;
    server->address.sin_port = htons(server->port);

    // bind address to the socket
    tmp = bind(server->socket, (struct sockaddr *) &(server->address),
               sizeof(server->address));
    if (tmp < 0)
    {
        perror("[-] initServer() in bind()");
        return -1;
    }

    // start listening for new connections
    tmp = listen(server->socket, server->backlog);
    if (tmp < 0)
    {
        perror("[-] initServer() in listen()");
        return -1;
    }

    return 0;
}

void closeServer(struct socketInfo *server)
{
    // close socket
    close(server->socket);

    // set info to 0
    memset(server, 0, sizeof(*server));
}

void acceptClient(struct socketInfo *server, struct socketInfo *client)
{
    // block the program until a wild client appears
    client->socket = accept(server->socket,
                    (struct sockaddr *) &(client->address),
                    &(client->length));
}

void setNonBlock(struct socketInfo *server)
{
    int flags = fcntl(server->socket, F_GETFL);
    fcntl(server->socket, F_SETFL, flags | O_NONBLOCK);
}


/// client functions /////////////////////////////////////////////////
int connectToServer(struct socketInfo *server, const char *ip, int port)
{
    int tmp;

    // init socket
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket < 0)
    {
        perror("[-] connectToServer() in socket()");
        return -1;
    }

    // prepare server address for connection
    server->address.sin_family = AF_INET;
    server->address.sin_port = htons(port);

    // resolve host name
    tmp = inet_pton(AF_INET, ip, &(server->address.sin_addr));
    if (tmp < 0)
    {
        perror("[-] connectToServer() in inet_pton()");
        return -1;
    }

    // connect to the server
    tmp = connect(server->socket, (struct sockaddr *)&server->address,
                  sizeof(server->address));
    if (tmp < 0)
    {
        perror("[-] connectToServer() in connect()");
        return -1;
    }

    return server->socket;
}

void disconnectFromServer(struct socketInfo *server)
{
    // close socket
    close(server->socket);

    // set information to 0
    memset(server, 0, sizeof(*server));
}


/// common functions /////////////////////////////////////////////////
int sendMessage(struct socketInfo *to, char *buffer, int bufferSize)
{
    // send the message
    int length = send(to->socket, buffer, bufferSize, 0);

    return length;
}

int recvMessage(struct socketInfo *from, char *buffer, int bufferSize)
{
    // receive the message
    int length = recv(from->socket, buffer, bufferSize, 0);

    return length;
}
