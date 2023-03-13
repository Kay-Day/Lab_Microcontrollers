/*
 * File:   CodeLab1.c
 * Author: AnTran19CE
 *
 * Created on 07 February 2023, 15:24
 */


#include <xc.h>
#include "config18f4550.h"

#define _XTAL_FREQ 20000000

void ledBlink1(); // code theo kieu cai che do 1/0 cho tung chan
void ledBlink2(); // code theo kieu dich bit

void main(void) {
    // Xoa bo nho thanh ghi port D
    PORTD = 0x00;
    LATD = 0x00;
    // cai dat che do OUTPUT port D
    TRISD = 0x00;
  
    while(1){
        ledBlink2();
    }
    return ;
}

void ledBlink1(){
    RD0=1;
    __delay_ms(100);
    RD0=0;
    __delay_ms(100);
    RD1=1;
    __delay_ms(100);
    RD1=0;
    __delay_ms(100);
    RD2=1;
    __delay_ms(100);
    RD2=0;
    __delay_ms(100);
    RD3=1;
    __delay_ms(100);
    RD3=0;
    __delay_ms(100);
    RD4=1;
    __delay_ms(100);
    RD4=0;
    __delay_ms(100);
    RD5=1;
    __delay_ms(100);
    RD5=0;
    __delay_ms(100);
    RD6=1;
    __delay_ms(100);
    RD6=0;
    __delay_ms(100);
    RD7=1;
    __delay_ms(100);
    RD7=0;
    __delay_ms(100);    
}

void ledBlink2(){
    unsigned char a = 0x01; 
    for (int i = 0; i < 8; i++){
        PORTD = a<<i;
        __delay_ms(100);
    }
}