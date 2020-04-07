/*------------------------------------------------------------------------------------------------------------------
--  SOURCE FILE:    main.h - Main entry to the chat program
--
--  PROGRAM:        ChatProgram
--
--  FUNCTIONS:
--                  int main(int argc, char* argv[]);
--                  void usageError();       
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
--  This file provides functions to allow the program to run either as the client or as the server.
------------------------------------------------------------------------------------------------------------------*/
#include "global.h"
#include "client.h"
#include "server.h"

pthread_mutex_t read_lock; 
pthread_mutex_t write_lock; 

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       main
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      April 7, 2020 (Updated argument list)
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  INTERFACE:      int main(int argc, char* argv[])  
--                      int argc: Number of arguments
--                      char* argv[]: Character array of arguments
--
--  RETURNS:        0 if function is successful
--                  1 if function is unsucbcessful
--
--  NOTES:
--  Main entry to the chat program. Function will check the number of arguments first. If there are 3 arguments, then
--  the program behaves as a client. If there are 4 arguments, then the program behaves as a client. 
--
--  The function will next check each argument if it is valid. If any of the arguments are invalid, then the program
--  exits and outputs the expected argument sequence.
--
--  To run the program as a server, type:
--      ./all server <ip_address>:<port>
--      Example) ./all server 192.0.0.1:8000
--
--  To run the program as a client, type:
--      ./all client <username> <ip_address>:<port>
--      Example) ./all client TestUser 192.0.0.1:8000
------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char* argv[]);

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       main
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      N/A
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  INTERFACE:      void usageError(void)
--
--  RETURNS:        void
--
--  NOTES:
--  Outputs the argument sequence to run as either a server or as a client.
------------------------------------------------------------------------------------------------------------------*/
void usageError();

