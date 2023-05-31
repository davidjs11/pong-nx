#include "inet.h"
#include "utils.h"

int main(void)
{
    char *ip = "192.168.1.144";
    socketInfo server, client;
    server = resolveHost(ip, 3475);

    initServer(&server);

    u8 input[2*INPUT_BUFFER_SIZE] = {0};
    u8 tmpInput[2*INPUT_BUFFER_SIZE] = {0};
    //setSocketTimeout(server.socket);
    //setSocketTimeout(client.socket);

    char buffer[1024];
    int tmp;
    while(1)
    {
        for(int i=0; i<2*INPUT_BUFFER_SIZE; i++)
            tmpInput[i] = 0;

        tmp = getMessage(
            &server, &client,
            (char *) tmpInput, 2*INPUT_BUFFER_SIZE);

        printf("%d inp: ", tmp);
        for(int i=0; i<2*INPUT_BUFFER_SIZE; i++)
        {
            input[i] = (input[i] | tmpInput[i]);
            printf("%u", input[i]);
        }
        printf("\n");
        printf("%d tmp: ", tmp);
        for(int i=0; i<2*INPUT_BUFFER_SIZE; i++)
        {
            printf("%u", tmpInput[i]);
        }
        printf("\n");

        /*
        sendMessage(&client,&server,
                    (char *) input, 2*INPUT_BUFFER_SIZE);
        */

        for(int i=0; i<2*INPUT_BUFFER_SIZE; i++)
            input[i] = 0;
    }

    return 0;
}
