#include "global.h"
#include "client.h"
#include "server.h"

void usageError();

int main(int argc, char* argv[]) {

    int port_number;
    char mode[10];

    switch(argc)
    {
        case 2:
            port_number = SERVER_TCP_PORT;
            break;
        case 3:
            port_number = atoi(argv[2]);
            break;
        default:
            usageError();
            return 1;
    }

    strcpy(mode, argv[1]);

    if (strcmp(argv[1],"client") != 0 && strcmp(argv[1],"server") != 0)
    {
        usageError();
        return 1;
    }

    if (strcmp(mode, "client") == 0)
        run_client(SERVER_IP_ADDRESS, port_number);
        
    if (strcmp(mode, "server") == 0)
        run_server(SERVER_IP_ADDRESS, port_number);

    return 0;
}

void usageError()
{
    printf("%s\n", "Usage ./all <client/server> <port>");
}