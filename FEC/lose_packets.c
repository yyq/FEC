#include "parameters.h"
#include "lose_packets.h"
#include <sys/time.h>
#include <stdio.h>

int Lose_Packets(UNSIGNED *packets, UNSIGNED *rec_packets, int *pNrec)

{
    int i,j,k,m;
    //int ranval ;
    
    /* Set up seed to random generator for losing packets */
    
    struct timeval tp ;
    struct timezone tzp;
    gettimeofday(&tp, &tzp);
    srand48(tp.tv_usec);
    
    /* Decide which packets to keep randomly
     
     *pNrec = 0 ;
     k = 0 ;
     m = 0 ;
     for (i=0; i < Npackets ; i++)
     {
     ranval = (int) mrand48();
     if (ranval <= 0xC0000000)
     {
     for (j=0; j < Plentot ; j++)
     {
     rec_packets[m] = packets[k+j] ;
     m++ ;
     } ;
     (*pNrec)++ ;
     } ;
     k += Plentot ;
     } ;
     */
    
    /* Keep last packets and only */
    
    *pNrec = 0 ;
    k = 0 ;
    m = 0 ;
    for (i=(Npackets-Mpackets)/2 ; i < (Npackets+Mpackets)/2 ; i++)
    //for (i=1 ; i < 400 ; i+= 2)

    {
        k = Plentot * i ;
        m = Plentot * (*pNrec) ;
        for (j=0; j < Plentot; j++)
            rec_packets[m+j] = packets[k+j] ;
        (*pNrec)++ ;
    } ;
    
    return tp.tv_usec ;
}
