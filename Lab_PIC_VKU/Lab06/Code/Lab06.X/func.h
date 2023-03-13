#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xc.h>
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


#define X_1 RB0
#define X_2 RB1
#define X_3 RB2
#define X_4 RB3
#define Y_1 RB4
#define Y_2 RB5
#define Y_3 RB6
#define Y_4 RB7
#define Keypad_PORT PORTB
#define Keypad_PORT_Direction TRISB  

char keypad_scanner(void)  {           
    X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1;    
    if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '7'; }
    if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '8'; }
    if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '9'; }
    if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return '/'; }
    X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1;    
    if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '4'; }
    if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '5'; }
    if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '6'; }
    if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return '*'; }
    X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1;    
    if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '1'; }
    if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '2'; }
    if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '3'; }
    if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return '-'; }
    X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0;    
    if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return 'c'; }
    if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '0'; }
    if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '='; }
    if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return '+'; }        
    return 'n';                   
}
void InitKeypad(void){
    Keypad_PORT = 0x00;        // Set Keypad port pin values zero
    Keypad_PORT_Direction = 0xF0;      // Last 4 pins input, First 4 pins output        
    RBPU = 0;
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
int char2num(char ch){
	int num = 0;
	switch(ch){
		case '0': num = 0; break;
		case '1': num = 1; break;
		case '2': num = 2; break;
		case '3': num = 3; break;
		case '4': num = 4; break;
		case '5': num = 5; break;
		case '6': num = 6; break;
		case '7': num = 7; break;
		case '8': num = 8; break;
		case '9': num = 9; break;
    }
    return num;
}
int num2char(int ch){
	char num = 0;
	switch(ch){
		case 0: num = '0'; break;
		case 1: num = '1'; break;
		case 2: num = '2'; break;
		case 3: num = '3'; break;
		case 4: num = '4'; break;
		case 5: num = '5'; break;
		case 6: num = '6'; break;
		case 7: num = '7'; break;
		case 8: num = '8'; break;
		case 9: num = '9'; break;
    }
    return num;
}
void result(int numb) {	
	unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
	unsigned char TenthDigit = 0;  //It will contain 10th position digit of numb
//    LCDGoto(1,1);
	if(numb<0)
	{
	LCDGoto(14,1);
        numb = -1*numb;          // Make number positive
		LCDPutChar('-');	 // Display a negative sign on LCD
	}
    LCDGoto(15,1);
    LCDPutChar(num2char(numb));

//	TenthDigit = (numb/10);	                  // Findout Tenth Digit
//
//	if( TenthDigit != 0)	                  // If it is zero, then don't display
//		LCDPutChar(TenthDigit + 0x30);	  // Make Char of TenthDigit and then display it on LCD
//
//	UnitDigit = numb - TenthDigit*10;
//	LCDPutChar(UnitDigit + 0x30);	  // Make Char of UnitDigit and then display it on LCD
}

void printERROR(){
    LCDGoto(1,1);
    LCDPutStr("Wrong Function");
    __delay_ms(500);
    DisplayClr();
}