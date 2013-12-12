//
//  main.c
//  FEC
//
//  Created by Yang YanQing on 13-5-28.
//  Copyright (c) 2013年 Yang YanQing. All rights reserved.
//

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "parameters.h"
#include "init_field.h"
#include "get_msg.h"
#include "encode.h"
#include "lose_packets.h"
#include "decode.h"
#include "compare_msg.h"

int main() {
    static UNSIGNED COLBIT, BIT[15];
    
    int iter, Nrec, TNrec, seed, return_code;
    struct timeval stime, etime;
    
    prepare();
   
    /* Initialize the arrays for finite field operations */
    
    Init_field(&COLBIT, BIT, ExptoFE, FEtoExp); //初始化参数，这个初始化过程只和Lfield参数相关
    
    /* Do several iterations of encoding and decoding message */
    
    TNrec = 0;
    
    gettimeofday(&stime, 0);
    
    //设定message的信息，整形或者字符什么的
    for (iter = 0; iter < Niter; iter++) {
        Get_msg(message);
        
#ifdef PRINT
        printf("--------------------------------------\nIteration %d.\n", iter);
        printf("\nDone getting message of %d bytes \n", Mlen * 4);
#endif
        
        
        
        //编码
        Encode(COLBIT, BIT, ExptoFE, FEtoExp, packets, message);
#ifdef PRINT
        printf("Done encoding %d packets\n", Npackets);
#endif
        
        
        
        //随机丢弃一些packet，随机收到M个packets
        seed = Lose_Packets(packets, rec_packets, &Nrec);
#ifdef PRINT
        printf("Received %d packets with seed %d \n", Nrec, seed);
#endif
        
        
        
        //解码，根据之前的参数，通过解码算法和recpackets，解答出的信息放在rec-message
        return_code = Decode(COLBIT, BIT, ExptoFE, FEtoExp,
                             rec_packets, &Nrec, rec_message);
#ifdef PRINT
        printf("Done with decoding\n");
#endif
        if (return_code == 0) {
            Compare_msg(message, rec_message);
            char *character = (char *)message;
            for (int temp = 0; temp < 12; temp++) {
                printf("%c", character[temp]);
            }
            printf("\n");
            character = (char *)rec_message;
            for (temp = 0; temp < 12; temp++) {
                printf("%c", character[temp]);
            }
            printf("\n");
#ifdef PRINT
            printf("Done with comparison\n");
#endif
        }
        TNrec += Nrec;
    }
    
    gettimeofday(&etime, 0);
    
    printf("--------- Cauchy Code ---------------\n");
    printf("Number of Mbytes processed is %f \n", ((float)Elen * Niter * 4) / 1000000.0);
    printf("Time in seconds is %f \n", (float)(etime.tv_sec - stime.tv_sec)
           + (float)(etime.tv_usec - stime.tv_usec) / 1000000.0);
    printf("MBytes per second is %f \n", ((float)Elen * Niter * 4) /
           ((float)(etime.tv_sec - stime.tv_sec) * 1000000.0 + (float)(etime.tv_usec - stime.tv_usec)));
    printf("Overhead is %d\n", Mpackets);
    printf("Encoding redundancy is %f \n", 1.0 + (float)Rpackets / (float)Mpackets);
    printf("Fraction of packets received is %f \n\n", (float)TNrec / ((float)Niter * Npackets));
}