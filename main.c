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
#include "main.h"

void usageError();
void run_client_process(char* server_ip, int port);
void run_server_process(char* server_ip, int port);

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
        {
            run_client_process(SERVER_IP_ADDRESS, port_number);
            printf("client!\n");
        }
        else if (strcmp(mode, "server") == 0)
        {
            run_server_process(SERVER_IP_ADDRESS, port_number);
            printf("server!\n");
        }
    }




    return 0;
}

void run_server_process(char* server_ip, int port)
{
    int sd, new_sd, bytes_to_read, n;
    struct sockaddr_in server, client;
    socklen_t client_len;
    char* bp, buf[BUFLEN];

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(sd, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        perror("Can't bind name to socket");
        exit(1);
    }

    listen(sd, 5);

    while(1)
    {
        client_len = sizeof(client);
        if ((new_sd = accept (sd, (struct sockaddr *)&client, &client_len)) == -1)
        {
            fprintf(stderr, "Can't accept client\n");
            exit(1);
        }

        printf("Remote Address: %s\n", inet_ntoa(client.sin_addr));
        bp = buf;
        bytes_to_read = BUFLEN;
        while ((n = recv(new_sd, bp, bytes_to_read, 0)) < BUFLEN)
        {
            bp += n;
            bytes_to_read -= n;
        }

        printf("Sending: %s\n", buf);
        //Multiplex I/O here
        close(new_sd);
    }

}

void run_client_process(char server[], int port)
{

}

void usageError()
{
    printf("%s\n", "Usage ./all <client/server> <port>");
}