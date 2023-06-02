#include "inet.h"
#include "utils.h"

int main(void)
{
    char *ip = "192.168.1.144";
    socketInfo server, client;
    server = resolveHost(ip, 3475);

    initServer(&server);

    u8 input[2*INPUTSIZE] = {0};
    u8 tmpInput[2*INPUTSIZE] = {0};
    //setSocketTimeout(server.socket);
    //setSocketTimeout(client.socket);

    char buffer[1024];
    int tmp;
    while(1)
    {
        memset(tmpInput, 0, 2*INPUTSIZE);

        /*
        getMessage(&server, &client,
                   (char *) tmpInput, 2*INPUTSIZE);
        */

        // mix both player inputs in global input buffer
        for(int i=0; i<2*INPUTSIZE; i++)
            input[i] = (input[i] | tmpInput[i]);

        sendMessage(&client,&server,
                    (char *) input, 2*INPUTSIZE);

        memset(tmpInput, 0, 2*INPUTSIZE);
    }

    return 0;
}
