                 
#include <mega128.h> 
#include <io.h>
#include <delay.h>
#include "Char_2LineLCD.h"

void LCD_Init(void)
{
   DDRC = 0xFF;    // ��Ʈ C ��� ����
   PORTC &= 0xFB;  // E = 0;
   
   delay_ms(50);   
   
   // �ʱ�ȭ ����
   LCD_Command(0x28); // function Set
   LCD_Command(0x06); // entry mode set
   LCD_Command(0x01); // all Clear
   LCD_Command(0x0C); // display on     
}

// & ��Ʈ AND ������, &= ��Ʈ AND ���� ������, ^��Ʈ XOR ������, ^= ��Ʈ XOR ���� ������, 
// | ��Ʈ OR ������, |= ��Ʈ OR ���� ������, ~ ��Ʈ NOT ������


// RS : Register selection H: Display Data , L: Instruction Code
// R/W : Read/Wirte Selection H:Read opration , L: Write Opration

void LCD_Command(unsigned char byte)
{
   delay_ms(2); // �ʱ� ����
    
   // �ν�Ʈ���� ��������Ʈ
   PORTC = (byte & 0xF0); // ���������� mask �� ���  , 0xF0 = 0b 1111 0000 
   PORTC &= 0xFE;         // RS = 0;                  , 0xFE = 0b 1111 1110
   PORTC &= 0xFD;         // RW = 0;                  , 0xFD = 0b 1111 1101
   delay_us(1);
   PORTC |= 0x04;         // E = 1                    , 0x04 = 0b 0000 1000 , |= (bit or �������)
   delay_us(1);
   PORTC &= 0xFB;         // E = 0
   
   // �ν�Ʈ���� ��������Ʈ
   PORTC = ((byte<<4) & 0xF0); // ������ ������ ������ 4BIT �̵� , byte�� mask �� ���    PORTC &= 0xFE;              // RS = 0   PORTC &= 0xFD;              // RW = 0 
   delay_us(1);
   PORTC |= 0x04;              // E = 1
   delay_us(1);
   PORTC &= 0xFB;              // E = 0
}


// char flash : pointer declaration for program memory// char eeprom : pointer declaration for EEPROM

// ���ڿ� ��� �Լ�
void LCD_String(char flash str[])
{
  char flash *pStr = 0;
  pStr = str;
  while(*pStr)//NULL�� �ɶ� ���� ����
  {
    DataWirte(*pStr++);
  }
}

void LCD_puts(const char *s)
{
  while(*s){
    DataWirte(*s++);
  }
}


// ������ ���� �Լ�

void DataWirte(unsigned char byte)
{
   delay_ms(2); // �ʱ� ����
  
  // ������ ���� ����Ʈ 
  PORTC = (byte & 0xF0);      // ������ 
  PORTC |= 0x01;              // RS = 1 
  PORTC &= 0xFD;              // RW = 0
  delay_us(1); 
  PORTC |= 0x04;              //  E = 1
  delay_us(1);
  PORTC &= 0xFB;              //  E = 0
  
  // ������ ���� ����Ʈ 
  PORTC = ((byte<<4) & 0xF0); // ������
  PORTC |= 0x01;              //  RS = 1
  PORTC &= 0xFD;              //  RW = 0 
  delay_us(1); 
  PORTC |= 0x04;              //  E = 1
  delay_us(1);
  PORTC &= 0xFB;              //  E = 0
}  

// set print position to (x,y) where y=line number (0 or 1), x = character position 0, 1, etc.
void LcdGotoXY(unsigned char x , unsigned char y)
{
  volatile unsigned char ddram_addr;
    
  if(y==1)
  {
    ddram_addr=0xC0;   // Start print at 2and line address 0x40
    LCD_Command(ddram_addr + (x & 0x7F));
  }
  if(y==0)
  {
   ddram_addr = 0x80;
   LCD_Command(ddram_addr + (x & 0x7F));
  }
}