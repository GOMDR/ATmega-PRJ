#include <io.h>
#include <mega128.h>
#include <delay.h>
#include "UART_RX_TX_module.h"
    
#include <stdio.h>

#define RX_COMPLETE 0x80


void UART0_Init (void)
{       
 PORTE = 0xff;
 DDRE  = 0xfe; 
 
 UCSR0A = 0x00;
 UCSR0B = 0x98;    // USART Enable   0b1001 1000   RXCIE0 : ���� �Ϸ� ���ͷ�Ʈ �ο��̺�  
                   // �ۼ��� �ο��̺� TXEN0 = 1, RXEN0 =1 
 UCSR0C = 0x06;    // No parity , 1 stop bit , 8bit data
 UBRR0H = 0;
 UBRR0L = 103;     // 9600bps  ,X-TAL 16Mhz
 
}

// ������  ���� (�ѹ���) ---- POLLING ���
void TxChar(unsigned char chr)
{
  while((UCSR0A & 0x20) == 0);
   UDR0 = chr;
   UCSR0A |= 0x20; 

}                    

//���ڿ� ����  ---- POLLING ���
void TxString(unsigned char *str)
{
  int i = 0;
  while(str[i] != 0)
  {
        TxChar(str[i]);
        i++;
  }

}

// ������  ����  ---- POLLING ���
char RXchar(void)
{  
   char data;    

   while(1)   
   {
     while((UCSR0A & RX_COMPLETE ) == 0);
     data = UDR0;
   } 
   return data;
}

