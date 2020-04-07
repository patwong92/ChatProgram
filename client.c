#include "client.h"

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       run_client
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      N/A
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  INTERFACE:      int run_client(char* username, char serverip[], int port);
--                      void* socket: struct that stores the socket descriptor.
--
--  RETURNS:        void
--
--  NOTES:
--  This thread function continously reads for data in the socket buffer. If a data exists in the buffer, then the
--  function will display the date to stdout.
------------------------------------------------------------------------------------------------------------------*/
int run_client(char* username, char serverip[], int port)
{
    int sd;
    struct hostent *hp;
    struct sockaddr_in server;
    char readin[BUFLEN],sbuf[CLIENT_BUFLEN];
    char* sb;
    pthread_t read_thread;
    // pthread_t save_file_thread;
    int fd, sret;
    fd_set readfds;
    struct timeval timeout;

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

    printf("Connected to Server: %s\n", hp->h_name);

    struct client_info* ci = (struct client_info*)malloc(sizeof(struct client_info));
    ci->socket_descriptor = sd;
    sb = malloc(sizeof(char)*SAVE_BUFFER_SIZE);
    memset(sb, 0, sizeof(char)*SAVE_BUFFER_SIZE);
    ci->save_buffer = sb;
    strcpy(ci->save_buffer, "Chat log\n");

    if (pthread_create(&read_thread, NULL, read_conversation, (void*) ci) != 0)
    {
        printf("Thread creation failed\n");
        close(sd);
        free(sb);
        free(ci);
        return 1;
    }

    memset(sbuf, 0, sizeof(sbuf));
    strcat(sbuf, username);
    strcat(sbuf, "(");
    strcat(sbuf, serverip);
    strcat(sbuf, ") has joined the server.\r\n");

    pthread_mutex_lock(&write_lock);
    send(sd, sbuf, BUFLEN, 0);
    pthread_mutex_unlock(&write_lock);

    fd = 0;

    while(1)
    {
        char savecmd[BUFLEN] = "$save$\n";

        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        sret = select(8, &readfds, NULL, NULL, &timeout);

        if (sret != 0)
        {
            memset((void*) readin, 0, sizeof(readin));
            read(fd, (void*) readin, BUFLEN);

            if (strcmp(readin, savecmd) == 0)
            {
                char filepath[255];
                strcpy(filepath, "chatlog.txt");
                // printf("%s\n", ci->save_buffer);
                save_file(filepath, ci->save_buffer, strlen(ci->save_buffer));
                printf("Saved chat log to file.\n");
                fflush(stdout);
                continue;
            }

            memset(sbuf, 0, sizeof(sbuf));
            strcat(sbuf, "[");
            strcat(sbuf, username);
            strcat(sbuf, "]: ");
            strcat(sbuf, readin);

            pthread_mutex_lock(&write_lock);
            send(sd, sbuf, BUFLEN, 0);
            pthread_mutex_unlock(&write_lock);
            fflush(stdout);
        }
    }

    pthread_join(read_thread, NULL);
    free(sb);
    close(sd);
    free(ci);
    return 0;
}



/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       program_banner
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      N/A
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  INTERFACE:      void program_banner(void)
--
--  RETURNS:        void
--
--  NOTES:
--  This function outputs the title of the chat room.
------------------------------------------------------------------------------------------------------------------*/
void program_banner()
{
    printf("------------------------------------------------------\n");
  	printf(" \t\t\tThe Chat Room\n");
  	printf("------------------------------------------------------\n");
}

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       read_conversation
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      N/A
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  INTERFACE:      void* read_conversation(void* socket);
--                      void* socket: struct that stores the socket descriptor.
--
--  RETURNS:        void
--
--  NOTES:
--  This thread function continously reads for data in the socket buffer. If a data exists in the buffer, then the
--  function will display the date to stdout.
------------------------------------------------------------------------------------------------------------------*/
void* read_conversation(void* socket)
{
    int n, bytes_to_read, sd;
    char* bp, rbuf[CLIENT_BUFLEN];
    char* sb;

    
    sd = ((struct client_info*)socket)->socket_descriptor;
    sb = ((struct client_info*)socket)->save_buffer;
    bp = rbuf;
    bytes_to_read = BUFLEN;
    n = 0;

    while(1)
    {
        pthread_mutex_lock(&read_lock);

        while ((n = recv(sd, bp, bytes_to_read, 0)) < BUFLEN)
        {
            bp += n;
            bytes_to_read -= n;
        }
        
        strcat(sb, rbuf);
        printf("%s", rbuf);

        pthread_mutex_unlock(&read_lock);
    }
}


int save_file(char* file_path, char* buffer, int buffer_size)
{
    FILE *fptr;

    if ((fptr = fopen(file_path, "w")) == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    fwrite(buffer, sizeof(char), buffer_size, fptr);

    fclose(fptr);
    return 0;
}
