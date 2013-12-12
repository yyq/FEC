//
//  parameters.c
//  FEC
//
//  Created by Yang YanQing on 13-6-16.
//  Copyright (c) 2013年 Yang YanQing. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"

void prepare(){
    ExptoFE = (UNSIGNED *)calloc(TableLength + Lfield, sizeof(UNSIGNED));
    if (!(ExptoFE)) {
        printf("\ndriver: ExptoFE malloc failed\n"); exit(434);
    }
    
    FEtoExp = (UNSIGNED *)calloc(TableLength, sizeof(UNSIGNED));
    if (!(FEtoExp)) {
        printf("\ndriver: FEtoExp malloc failed\n"); exit(434);
    }
    
    rec_message = (UNSIGNED *)calloc(Mlen, sizeof(UNSIGNED));
    if (!(rec_message)) {
        printf("\ndriver: rec_message malloc failed\n"); exit(434);
    }
    
    message = (UNSIGNED *)calloc(Mlen, sizeof(UNSIGNED));
    printf("Message len %d\n",Mlen);
    if (!(message)) {
        printf("\ndriver: message malloc failed\n"); exit(434);
    }
    
    packets = (UNSIGNED *)calloc(Npackets * Plentot, sizeof(UNSIGNED));
    printf("packets len %d\n",Npackets * Plentot);
    if (!(packets)) {
        printf("\ndriver: packets malloc failed\n"); exit(434);
    }
    
    rec_packets = (UNSIGNED *)calloc(Npackets * Plentot, sizeof(UNSIGNED));
    if (!(rec_packets)) {
        printf("\ndriver: rec_packets malloc failed\n"); exit(434);
    }

    
}
