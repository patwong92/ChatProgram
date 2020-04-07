/*------------------------------------------------------------------------------------------------------------------
--  SOURCE FILE:    server.h - Server part of the program
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
--  This file provides functions to allow the program to listen to connections and pass data to each connection.
------------------------------------------------------------------------------------------------------------------*/
#include "global.h"

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       run_server
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      N/A
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  INTERFACE:      void SystemFatal(const char* message)
--                      const char* message: Message to send to stdout
--
--  RETURNS:        void
--
--  NOTES:          This function sends a custom message to stdout about an error. Then, it exits the program.
--  
------------------------------------------------------------------------------------------------------------------*/
void SystemFatal(const char* );

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       run_server
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      N/A
--
--  DESIGNER:       Patrick Wong
--
--  PROGRAMMER:     Patrick Wong
--
--  INTERFACE:      int run_server(char* server_ip, int port);
--                      char* server_ip: Host IP address
--                      int port: Port number
--
--  RETURNS:        0 if function is successful
--                  1 if error exists
--
--  NOTES:
--  This function runs the server of the program. The model this server runs is multiplex I/O. In other words, the
--  server creates a buffer to listen for any sockets. Any socket is available will be called using select(), and the
--  server will read the socket's buffer. After, the server sends the contents of the buffer to all connected sockets,
--  allowing each client to receive messages from other clients.
------------------------------------------------------------------------------------------------------------------*/
int run_server(char* server_ip, int port);

