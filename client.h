/*------------------------------------------------------------------------------------------------------------------
--  SOURCE FILE:    client.h - Client part of the program
--
--  PROGRAM:        ChatProgram
--
--  FUNCTIONS:
--                  int run_client(char* username, char serverip[], int port);
--                  void program_banner();
--                  void* read_conversation(void* socket);
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      April 6, 2020 (Initialization)
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  NOTES:
--  This file provides functions to allow the program to send data to clients and receive data from clients.
------------------------------------------------------------------------------------------------------------------*/
#include "global.h"
#include <pthread.h>

#define CLIENT_BUFLEN 1024

extern pthread_mutex_t read_lock; 
extern pthread_mutex_t write_lock; 

struct client_info
{
    int socket_descriptor;
    char* save_buffer;
};

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
int run_client(char* username, char serverip[], int port);


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
void program_banner();

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
void* read_conversation(void* socket);

int save_file(char* file_path, char* buffer, int buffer_size);

