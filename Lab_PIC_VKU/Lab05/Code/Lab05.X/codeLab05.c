/*
 * File:   codeLab05.c
 * Author: AnTran19CE
 *
 * Created on 07 February 2023, 00:00
 */

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config18f4550.h"

#define _XTAL_FREQ 20000000
#define LCD_delay 5 // ~5mS
#define LCD_Startup 15 // ~15mS

#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_CURSOR_BACK 0x10
#define LCD_CURSOR_FWD 0x14
#define LCD_PAN_LEFT 0x18
#define LCD_PAN_RIGHT 0x1C
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_BLINK 0x0F
#define LCD_CURSOR_LINE2 0xC0

#define FUNCTION_SET 0x28
#define ENTRY_MODE 0x06
#define DISPLAY_SETUP 0x0C 

#define LCDLine1() LCDPutCmd(LCD_HOME) 
#define LCDLine2() LCDPutCmd(LCD_CURSOR_LINE2) 
#define shift_cursor() LCDPutCmd(LCD_CURSOR_FWD)
#define cursor_on() LCDPutCmd(LCD_CURSOR_ON)
#define DisplayClr() LCDPutCmd(LCD_CLEAR) 

#define instr 0
#define data 1

#define LCD_PORT PORTD
#define LCD_PWR PORTDbits.RD7 
#define LCD_EN PORTDbits.RD6 
#define LCD_RW PORTDbits.RD5
#define LCD_RS PORTDbits.RD4 

#define NB_LINES 2 
#define NB_COL 16 

void LCD_Initialize(void);
void LCDPutChar(char ch);
void LCDPutCmd(char ch);
void LCDPutStr(const char *); 
void LCDWriteNibble(char ch, char rs);
void LCDGoto(char pos, char ln);

void main(void) {
    OSCCON=0x72; 
    LCD_Initialize();
    LCDPutStr("  Tran Viet An  "); 
    LCDGoto(1, 1);
//    LCDPutCmd(0xc0);
    LCDPutStr("VKU - K19 - CE");
//    DisplayClr(); 
    while(1);
    return;
}

void LCD_Initialize(){
    LCD_PORT = 0;
    TRISD = 0x00;
    LCD_PWR = 1;
    __delay_ms(LCD_Startup);
    LCDPutCmd(0x32);
    LCDPutCmd(FUNCTION_SET);
    LCDPutCmd(DISPLAY_SETUP);
    DisplayClr();
    LCDPutCmd(ENTRY_MODE);
}

void LCDWriteNibble(char ch, char rs){
    ch = (ch >> 4);
    ch = (ch & 0x0F);
    LCD_PORT = (LCD_PORT & 0xF0);
    LCD_PORT = (LCD_PORT | ch);
    LCD_RS = rs;
    LCD_RW = 0;
    LCD_EN = 1;
    LCD_EN = 0;
}

void LCDPutChar(char ch){
    __delay_ms(LCD_delay);
    LCDWriteNibble(ch,data);
    ch = (ch << 4);
    LCDWriteNibble(ch,data);
}

void LCDPutCmd(char ch){
    __delay_ms(LCD_delay);
    LCDWriteNibble(ch,instr);
    ch = (ch << 4);
    __delay_ms(1);
    LCDWriteNibble(ch,instr);
}

void LCDPutStr(const char *str){
    char i=0;
    while (str[i]){
    LCDPutChar(str[i++]);
    }
}
void LCDGoto(char pos,char ln){
    if ((ln > (NB_LINES-1)) || (pos > (NB_COL-1))) return;
    LCDPutCmd((ln == 1) ? (0xc0 | pos) : (0x80 | pos));
    __delay_ms(LCD_delay);
}
