                 
#include <mega128.h> 
#include <io.h>
#include <delay.h>
#include "Char_2LineLCD.h"

void LCD_Init(void)
{
   DDRC = 0xFF;    // 포트 C 출력 설정
   PORTC &= 0xFB;  // E = 0;
   
   delay_ms(50);   
   
   // 초기화 과정
   LCD_Command(0x28); // function Set
   LCD_Command(0x06); // entry mode set
   LCD_Command(0x01); // all Clear
   LCD_Command(0x0C); // display on     
}

// & 비트 AND 연산자, &= 비트 AND 대입 연산자, ^비트 XOR 연산자, ^= 비트 XOR 대입 연산자, 
// | 비트 OR 연산자, |= 비트 OR 대입 연산자, ~ 비트 NOT 연산자


// RS : Register selection H: Display Data , L: Instruction Code
// R/W : Read/Wirte Selection H:Read opration , L: Write Opration

void LCD_Command(unsigned char byte)
{
   delay_ms(2); // 초기 지연
    
   // 인스트럭션 상위바이트
   PORTC = (byte & 0xF0); // 상위데이터 mask 후 출력  , 0xF0 = 0b 1111 0000 
   PORTC &= 0xFE;         // RS = 0;                  , 0xFE = 0b 1111 1110
   PORTC &= 0xFD;         // RW = 0;                  , 0xFD = 0b 1111 1101
   delay_us(1);
   PORTC |= 0x04;         // E = 1                    , 0x04 = 0b 0000 1000 , |= (bit or 연산대입)
   delay_us(1);
   PORTC &= 0xFB;         // E = 0
   
   // 인스트럭션 하위바이트
   PORTC = ((byte<<4) & 0xF0); // 데이터 하위를 상위로 4BIT 이동 , byte을 mask 후 출력    PORTC &= 0xFE;              // RS = 0   PORTC &= 0xFD;              // RW = 0 
   delay_us(1);
   PORTC |= 0x04;              // E = 1
   delay_us(1);
   PORTC &= 0xFB;              // E = 0
}


// char flash : pointer declaration for program memory// char eeprom : pointer declaration for EEPROM

// 문자열 출력 함수
void LCD_String(char flash str[])
{
  char flash *pStr = 0;
  pStr = str;
  while(*pStr)//NULL이 될때 까지 동작
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


// 데이터 쓰기 함수

void DataWirte(unsigned char byte)
{
   delay_ms(2); // 초기 지연
  
  // 데이터 상위 바이트 
  PORTC = (byte & 0xF0);      // 데이터 
  PORTC |= 0x01;              // RS = 1 
  PORTC &= 0xFD;              // RW = 0
  delay_us(1); 
  PORTC |= 0x04;              //  E = 1
  delay_us(1);
  PORTC &= 0xFB;              //  E = 0
  
  // 데이터 하위 바이트 
  PORTC = ((byte<<4) & 0xF0); // 데이터
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