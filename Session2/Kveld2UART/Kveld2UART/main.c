/*
 * Kveld2UART.c
 *
 * Created: 4/18/2016 5:28:24 PM
 * Author : Vlad
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define LED0 PORTC7
#define LED1 PORTD5 //OC1A
#define LED2 PORTD4	//OC1B
#define LED3 PORTA3


int main(void)
{
	/*	Sett opp leds p� OLED1 Xplained PRO kortet som tidligere p� kvelden,
		Disse skal bli brukt som indikatorer p� at ting skjer i programmen v�r
	*/
	
	/*	Embedded debuggeren som ligger p� xplained kortet har en virtuel COM port.
		Vi skal bruke denne porten for � snakke med uCn via PCn. 
		Bruk device manager for � finne COM port nummer.
		Finn ut hvilken uart er koblet fra uC til embedded debuggeren. 
		M� pinnene p� uC settes eksplisit som innganger og utganger? (nei)
	*/
	
	/*	Sett opp RX complete og TX complete interrupts
		Bruk dem til � blinke leds n�r vi sender og mottar noen gjennom UART
		(se beskrivelse av uart control/status register B)
	*/

	sei();	//husk � sette global interrupt flag
	
	uart_init(		);	//initialiser med �nsket baud rate
		
	while (1) 
    {
		/*	Motta en karakter gjennom UART
			Send den tilbake
			Og blink en led	
		*/
    }
}

int uart_init(unsigned int baud)
{
	/*	For � kunne sende og motta gjennom UART m� man f�rst sette riktig baud rate i UART baud rate register (UBRR)
		Dette blir gj�rt for dere, men hvis dere skulle gj�re det selv kunne det v�re lurt � bruke tabellen fra seksjon 23.10 i databladet
	*/
	UBRR1 = (F_CPU/(((unsigned long)16*baud))-1);
	
	/* Sett 8 bits pakkelengde og 1 stoppebit ved � skrive UART control/status registrene B og C
	*/

	
	/*	Til slutt start UART modulen ved � enable transmit og receive fra control/status register B
	*/

	return 0; //uart init successful
}
void uart_putchar(unsigned char c)
{
	/*	Denne funksjonen skal skrive en karakter til UART:
		Vent til transmissionsbufferen er tom (data register empty i control/status register A)
		S� send karakteren til uart data register
	*/

	
	
}

unsigned char uart_getchar()
{
	/*	Denne funksjonen skal lese en karakter fra UART:
		Vent til vi har motatt noen (Receive complete flagen blir satt i ett av control/status registrene)
		S� les mottaker bufferen og returner verdien som ligger i den
	*/


	
}


ISR(USART1_RX_vect)
{
	//flash led1 n�r vi mottar noen
}

ISR(USART1_TX_vect)
{
	//flash led2 n�r vi sender noen
}