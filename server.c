#include "server.h"

static void SystemFatal(const char* );
void parseBufferForServer(char* buffer);

int run_server(char* server_ip, int port)
{
    int listen_sd, new_sd, bytes_to_read, n;
    int i, maxi, sockfd, maxfd, client[FD_SETSIZE];
    int nready;
    struct sockaddr_in server, client_addr;
    socklen_t client_len;
    fd_set rset, sset, allset;
    char* bp, buf[BUFLEN];

    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(listen_sd, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        perror("Can't bind name to socket");
        close(listen_sd);
        exit(1);
    }

    printf("Server connection successful!\n");

    listen(listen_sd, LISTEN_QUEUE);

    maxfd = listen_sd;
    maxi = -1;

    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;

    FD_ZERO(&allset);
    FD_SET(listen_sd, &allset);

    while(1)
    {
        rset = allset;
        sset = allset;

        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listen_sd, &rset))
        {
            client_len = sizeof(client_addr);
            if ((new_sd = accept(listen_sd, (struct sockaddr*) &client_addr, &client_len)) == -1)
                SystemFatal("accept error");

            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = new_sd;
                    break;
                }
            }
  
            if (i == FD_SETSIZE)
            {
                printf("Too many clients\n");
                exit(1);
            }

            FD_SET(new_sd, &allset);

            if (new_sd > maxfd)
                maxfd = new_sd;

            if (i > maxi)
                maxi = i;

            if (--nready <= 0)
                continue;

        }

        for (i = 0; i <= maxi; i++)
        {
            if ((sockfd = client[i]) < 0)
                continue;

            if (FD_ISSET(sockfd, &rset))
            {
                // char display_buf[BUFLEN];

                memset(buf, 0, sizeof(buf));
                bp = buf;
                bytes_to_read = BUFLEN;
                
                while ((n = read(sockfd, bp, bytes_to_read)) > 0)
                {
                    bp += n;
                    bytes_to_read -= n;
                }

                printf("%s", buf);

                // strcpy(display_buf, buf);
                // parseBufferForServer(display_buf);

                // nready_send = select(maxfd + 1, NULL, &sset, NULL, NULL);

                for (int i = 0; i < LISTEN_QUEUE; i++)
                {
                    if (FD_ISSET(client[i], &sset))
                    {
                        write(client[i], buf, BUFLEN);
                    }    
                }

                // if (n == 0)
                // {
                //     printf("Remote address: %s closed connection\n", inet_ntoa(client_addr.sin_addr));
                //     close(sockfd);
                //     FD_CLR(sockfd, &allset);
                //     client[i] = -1;
                // }

                if (--nready <= 0)
                    break;
            }

        }

    }

    printf("End server process\n");

    return 0;
}

// Prints the error stored in errno and aborts the program.
static void SystemFatal(const char* message)
{
    perror (message);
    exit (EXIT_FAILURE);
}

void parseBufferForServer(char* buffer)
{
    char* username;
    char* message;
    username = strtok(buffer," ");
    message = strtok(NULL, " ");

    printf("Received from %s %s", username, message);
}