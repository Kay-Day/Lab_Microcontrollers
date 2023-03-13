/*
 * File:   Code.c
 * Author: AnTran19CE
 *
 * Created on 07 February 2023, 21:33
 */


#include <xc.h>
#include "config18f4550.h"
#define _XTAL_FREQ 20000000

unsigned char segAnode[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90 };
void main(void) {
    // Xoa bo nhó thanh ghi
    PORTB = 0x00;
    LATB = 0x00;
    PORTD = 0x00;
    LATD = 0x00;
    
    // cai dat che do lam viec IO
    TRISD = 0;
    TRISB = 1;
    
    if (RB7 == 0){
        for (int i = 0; i < 10; i++){
            PORTD = segAnode[i];
            __delay_ms(100);
        }
    }else {
        for(int i = 9; i >= 0; i--){
            PORTD = segAnode[i];
            __delay_ms(100);
        }
    }
    return;
}



