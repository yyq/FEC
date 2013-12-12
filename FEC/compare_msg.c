#include "parameters.h"
#include "compare_msg.h"
#include <stdio.h>

void Compare_msg(UNSIGNED *message, UNSIGNED *rec_message)
{
    //int i,j,k,l,m,n;
    int i;
    for (i=0; i < Mlen; i++)
    {
        if (message[i] != rec_message[i])
		{
            printf("*** Error: mismatch between %x and %x in word %d\n",message[i], rec_message[i], i) ;
		};
	};
}
