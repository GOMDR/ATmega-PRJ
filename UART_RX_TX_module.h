#ifndef _UART_RX_TX_module_INCLUDED_
#define _UART_RX_TX_module_INCLUDED_

#pragma used+

void UART0_Init (void);
void TxChar(unsigned char chr);
char RXchar(void);
void TxString(unsigned char *str);



#pragma used-

#endif
