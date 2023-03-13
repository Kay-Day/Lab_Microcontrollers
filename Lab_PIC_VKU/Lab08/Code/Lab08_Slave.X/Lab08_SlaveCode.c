/*
 * File:   Lab08_SlaveCode.c
 * Author: TranVietAn
 *
 * Created on 17 February 2023, 07:40
 */


#include <xc.h>
#include "config16f877a.h"

#define _XTAL_FREQ 4000000

void I2C_Slave_Init(unsigned char);

void main(void) {
    TRISB = 0xFF;
    nRBPU = 0;
    I2C_Slave_Init(0x40);
    while(1);
    return;
}

void __interrupt() ISR(void){
    if(SSPIF){
        if(!D_nA && R_nW){
            char Dummy = SSPBUF;
            SSPBUF = PORTB ;
            CKP = 1;
            while(BF);
        }  
        CKP = 1;
        SSPIF = 0;
    }
}

void I2C_Slave_Init(unsigned char Address){
    SSPADD = Address;
    SSPSTAT = 0x80;
    SSPCON = 0x36;
    SSPCON2 = 0x01;
    TRISC3 = 1;
    TRISC4 = 1;
    GIE = 1; 
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
}
