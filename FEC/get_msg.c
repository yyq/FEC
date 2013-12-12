#include "parameters.h"
#include "get_msg.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Get_msg(UNSIGNED *message)
{
    //int i;
    char *x = (char *)message;
    char hello[14]="Hello World!\n";
    //for (i=0; i < Mlen; i++) message[i] = i ;
    strcpy(x, hello);
    //memcpy(x, hello, sizeof(100));
    //for (i=0; i < 4*Mlen; i++)
    //    x[i] = "abcdefghijklmnopwrstuvwxyz"[rand()%26] ;
}
