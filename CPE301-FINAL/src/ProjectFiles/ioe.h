#ifndef ioe
#define ioe

void UART_init();
unsigned char UART_getChar();
void UART_putChar(unsigned char data);

void UART_putStr(char* output);
void scanm(unsigned char* buffer);

#endif