#include "main.h"

/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:       main
--
--  DATE:           April 6, 2020
--
--  REVISIONS:      April 7, 2020 (Updated argument list)
--
--  DESIGNER:       Patrick Wong / Mikhaela Layon
--
--  PROGRAMMER:     Patrick Wong / Mikhaela Layon
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
void usageError()
{
    printf("%s\n", "Client Usage: ./all client <name> <ip:port>\n");
    printf("%s\n", "Server Usage: ./all server <ip:port>\n");
}