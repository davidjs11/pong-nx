#include "inet.h"
#include "utils.h"

int main(void)
{
    char *ip = "192.168.1.144";
    socketInfo server, client;
    server = resolveHost(ip, 3476);

    initServer(&server);

    u8 *input[2];
    input[0] = malloc(INPUT_BUFFER_SIZE*sizeof(u8));

    while(1)
    {
        getMessage(&server, &client, (char *) input[0], INPUT_BUFFER_SIZE);
        printf("[+] Data received: \n");
        sendMessage(&client, &server, (char *) input[0], INPUT_BUFFER_SIZE);
        printf("[+] Data sent: \n");
    }

    return 0;
}
