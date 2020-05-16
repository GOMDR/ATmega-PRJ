#ifndef _Char_2LineLCD_INCLUDED_
#define _Char_2LineLCD_INCLUDED_

#pragma used+

void LCD_Init(void);
void LCD_Command(unsigned char byte);
void LCD_String(char flash str[]);
void DataWirte(unsigned char byte);
void LcdGotoXY(unsigned char x , unsigned char y);

void LCD_puts(const char *s);
#pragma used-

#endif