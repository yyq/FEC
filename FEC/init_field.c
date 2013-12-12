#include "parameters.h"
#include "init_field.h"
#include <stdio.h>
#include <sys/time.h>

void Init_field(UNSIGNED *pCOLBIT, UNSIGNED *BIT, UNSIGNED *ExptoFE,
                UNSIGNED *FEtoExp)
{
    /* POLYMASK is the irreducible polynomial */
    /* CARRYMASK is used to see when there is a carry in the polynomial
     and when it should be XOR'd with POLYMASK */
    
    int i ;
    static UNSIGNED CARRYMASK ;
    static UNSIGNED POLYMASK[16] =
    {0x0,     0x3,   0x7,   0xB,   0x13,   0x25,  0x43,    0x83,
        0x11D, 0x211, 0x409, 0x805, 0x1053, 0x201B, 0x402B, 0x8003} ;
    
    /* Lfield is the length of the field (This can from the table above
     be between 1 and 15, but because of restrictions in the driver.c
     program this value currently can be at most 10).
     SMultField = TableLength - 1 is the number of elements in the multiplicative
     group of the field.  COLBIT is used to make sure rows and columns have
     distinct field elements associated with them
     The BIT array is used to mask out single bits in equations: bit
     ExptoFE is the table that goes from the exponent to the finite field element
     FEtoExp is the table that goes from the finite field element to the exponent */
    
    BIT[0] = 0x1 ;
    for (i=1; i < Lfield ; i++) BIT[i] = BIT[i-1] << 1 ;
    *pCOLBIT = BIT[Lfield-1] ;
    CARRYMASK = *pCOLBIT << 1 ;
    
    ExptoFE[0] = 0x1 ;
    for (i=1; i < SMultField + Lfield - 1 ; i++)
    {
        ExptoFE[i] = ExptoFE[i-1] << 1 ;
        if (ExptoFE[i]&CARRYMASK)
            ExptoFE[i] ^= POLYMASK[Lfield] ;
    } ;
    
    FEtoExp[0] = -1 ;
    for (i=0; i < SMultField ; i++)
        FEtoExp[ExptoFE[i]] = i ;
}
