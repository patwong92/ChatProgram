#include "global.h"
#include "client.h"
#include "server.h"

void usageError();

pthread_mutex_t read_lock; 
pthread_mutex_t write_lock; 

int main(int argc, char* argv[]) {

    int port_number;
    char* ip_address;
    char* name;
    char mode[10];

    switch(argc)
    {
        case 3:
        {
            ip_address = strtok(argv[2], ":");
            port_number = atoi(strtok(NULL, "\0"));
            break;
        }
        case 4:
        {
            name = argv[2];
            ip_address = strtok(argv[3], ":");
            port_number = atoi(strtok(NULL, "\0"));
            break;
        }
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
        run_client(name, ip_address, port_number);

    if (strcmp(mode, "server") == 0)
        run_server(ip_address, port_number);

    return 0;
}

void usageError()
{
    printf("%s\n", "Client Usage: ./all client <name> <ip:port>\n");
    printf("%s\n", "Server Usage: ./all server <ip:port>\n");
}