#include "client.h"

void program_banner();

int run_client(char serverip[], int port)
{
    int n, bytes_to_read, sd;
    struct hostent *hp;
    struct sockaddr_in server;
    char *bp, rbuf[CLIENT_BUFLEN], sbuf[CLIENT_BUFLEN], **pptr;
    char str[16];

    program_banner();

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Cannot create socket\n");
        return 1;
    }

    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    
    if((hp = gethostbyname(serverip)) == NULL)
    {
        fprintf(stderr, "Unknown server address\n");
        return 1;
    }

    bcopy(hp->h_addr_list[0], (char*) &server.sin_addr, hp->h_length);

    if (connect(sd, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        fprintf(stderr, "Can't connect to server\n");
        perror("Connect");
        exit(1);
    }

    printf("Connected: Server name: %s\n", hp->h_name);
    pptr = hp->h_addr_list;
    printf("\t\t\tIP address: %s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)));
    printf("Transmit: \n");

    fgets(sbuf, BUFLEN, stdin);
    send(sd, sbuf, BUFLEN, 0);

    printf("Receive:\n");
    bp = rbuf;
    bytes_to_read = BUFLEN;

    n = 0;
    while ((n = recv(sd, bp, bytes_to_read, 0)) < BUFLEN)
    {
        bp += n;
        bytes_to_read -= n;
    }
    
    printf("%s\n", rbuf);
    fflush(stdout);
    close(sd);
    return 0;
}

void program_banner()
{
    printf("------------------------------------------------------\n");
  	printf(" \t\tClient Test\n");
  	printf("------------------------------------------------------\n");
}