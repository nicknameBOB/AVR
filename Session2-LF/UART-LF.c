/*
 * Task2.c
 *
 * Created: 4/14/2016 6:57:09 PM
 * Author : Thomas Stenseth
 */ 

//UART

// F_CPU
#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE (((F_CPU)/(BAUD*16UL))-1)

// System headers
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

void uart_init (void){
	UBRR1H = (BAUDRATE >> 8);                   // shift the register right by 8 bits
	UBRR1L = BAUDRATE;					   		// set baud rate                       
	UCSR1B = (1 << RXEN) | (1 << TXEN);         // enable receiver, transmitter and recieve complete interrupt
	UCSR1C &= ~(1 << USBS);						// 1 stop bit
	UCSR1C |= (3 << UCSZ0);						// 8-bit character size
}
	
// function to receive data
unsigned char uart_recieve (void){
	while (!(UCSR1A & (1 << RXC)));				// wait while data is being received
	return UDR1;								// return 8-bit data to recieve buffer
}

void uart_transmit(unsigned char data){
	while (!( UCSR1A & (1 << UDRE)));
	UDR1 = data;
}

int main(void){
	
	unsigned char a; // To hold the data
	uart_init();
	
	while (1){
		a=uart_recieve();                   // save the received data in a variable
		uart_transmit(a);					// transmit the recieved data back
	}
}