/*
 * File:   Lab02.c
 * Author: AnTran19CE
 *
 * Created on 07 February 2023, 17:07
 */

#include <xc.h>
#include "config18f4550.h"
#define _XTAL_FREQ 20000000
void Lab02a();
void Lab02b();
void ledBlink01();
void ledBlink02();

void main(void) {
    // Xoa bo nhó thanh ghi
    PORTB = 0x00;
    LATB = 0x00;
    PORTD = 0x00;
    LATD = 0x00;
    
    // cai dat che do lam viec IO
    TRISD = 0;
    TRISB = 1;
    
//    Lab02a();
    Lab02b();
    return;
}

void Lab02a(){
    int stLed = 0;
    RD0 = 0;
    while(1){
        if(RB0 == 1) stLed = 1 ;
        if(RB1 == 1) stLed = 0 ;
        if(stLed == 0) RD0 = 0;
        else RD0 = 1;
    }
}

void Lab02b(){
    while(1){
        if(RB0 == 1) ledBlink01();
        else ledBlink02();
    }
    
}

void ledBlink01(){
    unsigned char a = 0x01; 
    for (int i = 0; i < 8; i++){
        PORTD = a<<i;
        __delay_ms(100);
    }
}

void ledBlink02(){
    unsigned char a = 0x80; 
    for (int i = 0; i < 8; i++){
        PORTD = a>>i;
        __delay_ms(100);
    }
}