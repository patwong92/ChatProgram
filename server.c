#include "server.h"
#include <stdio.h>

void run_server_process(char* server_ip, int port)
{
    printf("This is server process\n");

    // int sd, new_sd, bytes_to_read, n;
    // struct sockaddr_in server, client;
    // socklen_t client_len;
    // char* bp, buf[BUFLEN];

    // if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	// {
	// 	perror ("Can't create a socket");
	// 	exit(1);
	// }

    // bzero((char *)&server, sizeof(struct sockaddr_in));
    // server.sin_family = AF_INET;
	// server.sin_port = htons(port);
	// server.sin_addr.s_addr = htonl(INADDR_ANY); 

    // if (bind(sd, (struct sockaddr*) &server, sizeof(server)) == -1)
    // {
    //     perror("Can't bind name to socket");
    //     exit(1);
    // }

    // listen(sd, 5);

    // while(1)
    // {
    //     client_len = sizeof(client);
    //     if ((new_sd = accept (sd, (struct sockaddr *)&client, &client_len)) == -1)
    //     {
    //         fprintf(stderr, "Can't accept client\n");
    //         exit(1);
    //     }

    //     printf("Remote Address: %s\n", inet_ntoa(client.sin_addr));
    //     bp = buf;
    //     bytes_to_read = BUFLEN;
    //     while ((n = recv(new_sd, bp, bytes_to_read, 0)) < BUFLEN)
    //     {
    //         bp += n;
    //         bytes_to_read -= n;
    //     }

    //     printf("Sending: %s\n", buf);
    //     //Multiplex I/O here
    //     close(new_sd);
    // }

}