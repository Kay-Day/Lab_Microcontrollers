/*
 * File:   Code.c - LAB04
 * Author: AnTran19CE
 *
 * Created on 07 February 2023, 21:33
 */

#include <builtins.h>



#include <xc.h>
#include "config18f4550.h"
#define _XTAL_FREQ 20000000

unsigned char key1 [] = {0xff, 0x7f, 0x7b, 0x01, 0x00, 0x7f, 0x7f, 0xff};
unsigned char keyHeart [] = {0xe3, 0xc1, 0x81, 0x03, 0x81, 0xc1, 0xe3, 0xff};
unsigned char keyA [] = {0xff, 0x01, 0x00, 0xe6, 0xe6, 0x00, 0x01, 0xff};
unsigned char keyN [] = {0xff, 0x00, 0x01, 0xe3, 0xc7, 0x80, 0x00, 0xff};

void display(unsigned char key[]);
void main(void) {
    // Xoa bo nhó thanh ghi
    PORTB = 0x00;
    LATB = 0x00;
    PORTD = 0x00;
    LATD = 0x00;
    
    // cai dat che do lam viec IO
    TRISD = 0;
    TRISB = 0;
    
    while(1){
        display(keyHeart);
//        display(keyA);
//        __delay_ms(300);
//        display(keyN);
//        __delay_ms(300);
      
    }
    return;
}

void display(unsigned char key[]){
    for(int i = 0; i < 8; i++){
       PORTB = key[i];
       PORTD = 0x01<<i;
       __delay_ms(1);
       PORTD = 0x00;
    } 
    
}



