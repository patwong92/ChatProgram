#include "global.h"
#include <pthread.h>

#define CLIENT_BUFLEN 1024

extern pthread_mutex_t read_lock; 
extern pthread_mutex_t write_lock; 

int run_client(char* username, char serverip[], int port);


