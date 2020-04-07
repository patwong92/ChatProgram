/*------------------------------------------------------------------------------------------------------------------
--  SOURCE FILE:    global.h - Common resouce file
--
--  PROGRAM:        ChatProgram
--
--  FUNCTIONS:      N/A
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
--  This file provides libaries and macros for other files that rely on some or all of them.
------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <netinet/ip.h>
#include <signal.h>

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_TCP_PORT 9000
#define BUFLEN 255
#define LISTEN_QUEUE 5
