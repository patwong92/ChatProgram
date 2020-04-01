#include <stdio.h>
#include <string.h>
#include "main.h"

int main(int argc, char* argv[]) {

    if (argc != 3)
    {
        printf("%s\n", "Usage ./all <client/server> <port>");
        return 1;
    }

    if (strcmp(argv[1],"client") == 0)
    {
        printf("%s\n", "I am client");
    }
    else if (strcmp(argv[1], "server") == 0)
    {
        printf("%s\n", "I am server");
    }
    else
    {
        printf("%s\n", "Usage ./all <client/server> <port>");
    }

    return 0;
}