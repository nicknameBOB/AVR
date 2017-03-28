#ifndef UART_H_
#define UART_H_

int uart_init(unsigned int baud);
void uart_putchar(unsigned char c);
unsigned char uart_getchar();

#endif /* UART_H_ */
