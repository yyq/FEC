#include "parameters.h"
#include "encode.h"
#include <sys/time.h>
#include <stdio.h>

void Encode(UNSIGNED COLBIT, UNSIGNED *BIT, UNSIGNED *ExptoFE,
            UNSIGNED *FEtoExp, UNSIGNED *packets, UNSIGNED *message)
{
    int i,j,k,l,m, ind_seg,col_eqn,row_eqn,ind_eqn ;
    int row, col, ExpFE ;
    struct timeval start_time, end_time ;
    
    /* Set the identifier in all the packets to be sent */
    
    for (i=0; i < Npackets ; i++)
        packets[i*Plentot] = i;
    
    /* Copy the message into the first Mpackets packets */
    
    gettimeofday(&start_time,0) ;
    
    k = 0 ;
    j = 0 ;
    for (i=0; i < Mpackets ; i++)//填充从0到200个 packet的位置，把Message从头到尾填入 packets
    {
        k ++ ;
        for (ind_eqn=0; ind_eqn < Lfield ; ind_eqn++)
        {
            for (ind_seg =0; ind_seg  < Nsegs ; ind_seg ++)
            {
                packets[k] = message[j] ;
                j++ ;
                k++ ;
            } ;
        } ;
    } ;
    
    /* Fill in values for remaining Rpackets packets */
    
    for (row=0; row < Rpackets ; row++)
    {
        
        /* Compute values of equations applied to message
         and fill into packet(row+Mpackets).  */
        
        /* First, zero out contents relevant portions of packet */
        
        j = (row+Mpackets)*Plentot ;
        for (i =1 ; i  < Plentot ; i ++)
            packets[j+i] = 0 ;
        
        /* Second, fill in contents relevant portions of packet */
        
        for (col=0 ; col < Mpackets ; col++)
        {
            m = col*Lfield * Nsegs ;
            ExpFE = (SMultField - FEtoExp[row^col^COLBIT]) % SMultField ;
            for (row_eqn=0 ; row_eqn < Lfield ; row_eqn++)
            {
                k = row_eqn * Nsegs ;
                for (col_eqn=0 ; col_eqn < Lfield ; col_eqn++)
                {
                    if (ExptoFE[ExpFE+row_eqn] & BIT[col_eqn])
                    {
                        l = col_eqn * Nsegs + m ;
                        for (ind_seg=0 ; ind_seg < Nsegs ; ind_seg++)
                        {
                            packets[j+1+ind_seg+k] ^= message[ind_seg+l] ;
                        } ;
                    } ;
                } ;
            } ;
        } ;
    } ;
    
    gettimeofday(&end_time,0) ;
#ifdef PRINT
    printf ("\n------------------------------------------------") ;
    printf ("\n encode: number of seconds is %f",
            (float)(end_time.tv_sec-start_time.tv_sec)+
            (float)(end_time.tv_usec-start_time.tv_usec)/1000000.0) ;
    printf ("\n------------------------------------------------\n\n") ;
    fflush(stdout) ;
#endif
}
