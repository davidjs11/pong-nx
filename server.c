#include <sys/select.h>
#include "easyTCP.h"
#include "utils.h"

#define PORT 3476

int main(void)
{
    char *ip = "192.168.1.144";
    struct socketInfo server;
    struct socketInfo client[2];
    int connected = 0;

    // init server
    initServer(&server, PORT, 2);
    setNonBlock(&server);

    // fd set structures
    fd_set acceptedClients, readableClients;
    FD_ZERO(&acceptedClients);
    FD_SET(server.socket, &acceptedClients);

    // input arrays
    u8 input[2*INPUTSIZE] = {0};
    u8 tmpInput[2*INPUTSIZE] = {0};

    char buffer[1024];
    int tmp;
    while(1)
    {
        // clear input buffers
        memset(input, 0, 2*INPUTSIZE);

        // detect which fd is readable
        readableClients = acceptedClients;
        select(10, &readableClients, NULL, NULL, NULL);

        // accept new connection
        if (FD_ISSET(server.socket, &readableClients) && connected < 2)
        {
            acceptClient(&server, client+connected);
            printf("player %d connected\n", connected+1);
            FD_SET(client[connected].socket, &acceptedClients);
            connected++;
        }

        if (FD_ISSET(client[0].socket, &readableClients))
        {
            tmp = recvMessage(client, tmpInput, 2*INPUTSIZE);

            // mix both player inputs in global input buffer
            for(int i=0; i<2*INPUTSIZE; i++)
                input[i] = (input[i] | tmpInput[i]);

            // handle disconnection
            if (tmp <= 0)
            {
                FD_CLR(client[0].socket, &acceptedClients);
                client[0] = client[1];
                connected--;
                printf("player 1 disconnected\n");
            }

            printf("%d)\tplayer %d\n", tmp, 1);
        }

        if (connected > 1 && FD_ISSET(client[1].socket, &readableClients))
        {
            tmp = recvMessage(client+1, tmpInput, 2*INPUTSIZE);

            // mix both player inputs in global input buffer
            for(int i=0; i<2*INPUTSIZE; i++)
                input[i] = (input[i] | tmpInput[i]);

            // handle disconnection
            if (tmp <= 0)
            {
                FD_CLR(client[0].socket, &acceptedClients);
                connected--;
                printf("player 2 disconnected\n");
            }

            printf("%d)\tplayer %d\n", tmp, 2);
        }

        
        // send input to both players
        sendMessage(client, input, 2*INPUTSIZE);
        sendMessage(client+1, input, 2*INPUTSIZE);


        printf("global input: ");
        for(int i=0; i<INPUTSIZE*2; i++)
            printf("%u", input[i]);
        printf("\n");

    }

    return 0;
}
