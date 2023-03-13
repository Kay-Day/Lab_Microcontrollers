/*
 * File:   Lab08_MasterCode.c
 * Author: TranVietAn
 *
 * Created on 17 February 2023, 07:40
 */

#include <xc.h>
#include "config16f877a.h"

#define _XTAL_FREQ 16000000
#define I2C_BaudRate 100000

void I2C_Master_Init(void);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);
unsigned char I2C_Read(void);
unsigned char I2C_Write(unsigned char Data);

void main(){
    TRISD = 0x00;
    PORTD = 0x00;
    I2C_Master_Init();
    while(1){
        I2C_Start(); 
        I2C_Write(0x41);
        PORTD = I2C_Read();
        I2C_Stop();
        __delay_ms(100);
    }
}

void I2C_Master_Init(){
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD = ((_XTAL_FREQ/4)/I2C_BaudRate) - 1;
    TRISC3 = 1;
    TRISC4 = 1;
}
void I2C_Wait(){
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Start(){
    I2C_Wait();
    SEN = 1;
}
void I2C_Stop(){
    I2C_Wait();
    PEN = 1;
}
void I2C_Restart(){
    I2C_Wait();
    RSEN = 1;
}
void I2C_ACK(void){
    I2C_Wait();
    ACKDT = 0;
    ACKEN = 1;
}
void I2C_NACK(void){
    I2C_Wait();
    ACKDT = 1; 
    ACKEN = 1; 
}
unsigned char I2C_Write(unsigned char Data){
    I2C_Wait();
    SSPBUF = Data;
    I2C_Wait();
    return ACKSTAT;
}
unsigned char I2C_Read(){
    unsigned char Data;
    I2C_Wait();
    RCEN = 1;
    I2C_Wait();
    Data = SSPBUF;
    I2C_NACK();
    return Data;
}
