#include "global.h"
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

void usageError();

int main(int argc, char* argv[]) {

    int port_number;
    char mode[10];
    pid_t pid;

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

    pid = fork();
    if (pid == -1)
    {   
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    {
        if (strcmp(mode, "client") == 0)
            run_client_process(SERVER_IP_ADDRESS, port_number);

        if (strcmp(mode, "server") == 0)
            run_server_process(SERVER_IP_ADDRESS, port_number);
    }

    return 0;
}

void usageError()
{
    printf("%s\n", "Usage ./all <client/server> <port>");
}