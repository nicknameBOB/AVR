/*
 * Task3.c
 *
 * Created: 4/14/2016 10:18:13 AM
 * Author : Thomas Stenseth
 */ 

// F_CPU
/* Define F_CPU here */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

// LED
/* Define the pins for the LED here */

// Button
/* Define the pins for the button here */

int main(void){
    /*
	 * DDRx: 1 is output, 0 is input
	 * LED: 1 LED is off, 0 LED is on
	 * SW: 1 Button is open, 0 button is pressed
	 * Set to 1: FLAG |= ( 1 << BIT_POS )
	 * Set to 0: FLAG &= ~( 1 << BIT_POS )
	*/

	/*
	* Do the following:
	* Set LED and button correctly, and add a pull-up to the button
	*/
	
    while (1) {
		/* 
		* Do the following:
		* Check if button is pressed, but this time you want to toggle the light instead of turning it on/off (hint: XOR)
		* Add a button-pressed-state so that you dont't have to hold the button to turn on the light, but so that 
		* you instead toggle between light on/off when the button is pressed (like a light switch):
		* When the button is not pressed the light should hold it's current state.
		*/
    }
}

