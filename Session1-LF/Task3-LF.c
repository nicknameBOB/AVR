/*
 * Task3.c
 *
 * Created: 4/14/2016 10:18:13 AM
 * Author : Thomas Stenseth
 */ 

#define F_CPU 16000000UL // 16 MHz

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

// LED
#define LED0 PINC7

// Button
#define SW0 PINC6

int main(void){
    /*
	 * DDRx: 1 is output, 0 is input
	 * LED: 1 LED is off, 0 LED is on
	 * SW: 1 Button is open, 0 button is pressed
	 * Set to 1: FLAG |= ( 1 << BIT_POS )
	 * Set to 0: FLAG &= ~( 1 << BIT_POS )
	*/

	DDRC |= (1 << LED0); // Set LED0 as output
	DDRC &= ~(1 << SW0); // Set SW0 as input
	PORTC |= (1 << SW0); // Enable pull-up on button SW0
	int buttonState = 0; // To hold the button pressed state

    while (1) {
		if(!((1 << SW0) & PINC)){
			if (buttonState == 0){
				PORTC ^= (1 << LED0);
				buttonState = 1;
			}
		}
		else{
			buttonState = 0;			
		}
		_delay_ms(1);
    }
}

