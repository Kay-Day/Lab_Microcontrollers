/*
 * File:   CodeLab07.c
 * Author: TranVietAn
 *
 * Created on 16 February 2023, 08:57
 */

#include <xc.h>
#include <stdint.h>
#include "config_18f4550.h"
#define _XTAL_FREQ 20000000
#define btn_dir RD0
#define btn_sp1 RD1
#define btn_sp2 RD2
#define btn_sp3 RD3
#define btn_sp4 RD4
void direction_motor(int val);
void PWM_duty(uint16_t pwm_duty);
void PWM_init();
void main(void){
    PORTB = 0;
    PORTD = 0;
    TRISD = 1;
    TRISC = 0; 
    PWM_init();
    while(1){
       if(btn_dir == 1)  direction_motor(1);
       else direction_motor(0);
       if(btn_sp1 == 1 && btn_sp2 == 0 && btn_sp3 == 0 && btn_sp4 == 0  ) PWM_duty(0);
       else if(btn_sp1 == 0 && btn_sp2 == 1 && btn_sp3 == 0 && btn_sp4 == 0  ) PWM_duty(500);
       else if(btn_sp1 == 0 && btn_sp2 == 0 && btn_sp3 == 1 && btn_sp4 == 0  ) PWM_duty(900);
       else if(btn_sp1 == 0 && btn_sp2 == 0 && btn_sp3 == 0 && btn_sp4 == 1  ) PWM_duty(1023);
       else PWM_duty(0);
       __delay_ms(1);
    }
    return;
}
void PWM_init(){
    RC2 = 0;
    TRISC2 = 0;
    CCP1CON = 0x0c; //
    CCPR1L = 0;
    TMR2IF = 0;
    T2CON = 0x05;
    PR2 = 0xff;
}
void PWM_duty(uint16_t pwm_duty){
    CCP1CON = ((pwm_duty << 4) & 0x30)| 0x0c;
    CCPR1L = pwm_duty >> 2;
}
void direction_motor(int val){
    if(val == 0){
        RC0 = 1;
        RC1 = 0;
    }else {
        RC0 = 0;
        RC1 = 1;
    }
}