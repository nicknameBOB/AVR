/*
 * Task2.c
 *
 * Created: 4/14/2016 2:24:21 PM
 * Author : Thomas Stenseth
 */ 

#define F_CPU 16000000UL // 16 MHz

/*
* System headers bellow
*/

#include <avr/io.h>
#include <util/delay.h>

/*
* Checkout the ATmega324PB datasheet to find the correct ports and pins 
*/

// LED
#define LED0 PINC7

// Button
#define SW0 PINC6 

int main (void){
	/*
	 * We want to send signals to the LEDs, in order to turn it off and on.
	 * We also want to be able to read the switches.
	 * This is done by setting bits in the DDRx register (in this case DDRC)
	 * DDRx: 1 is output, 0 is input
	 * LED: 1 LED is off, 0 LED is on
	 * Button: 1 Button is open, 0 button is pressed
	 * Bit set logic:
	 * Set to 1: FLAG |= ( 1 << BIT_POS )
	 * Set to 0: FLAG &= ~( 1 << BIT_POS )
	 */

	/**
	 * In order to read from the switches, we need to give it a ground reference, via a pull-up resistor.
	 * If we don't, the switch will have a floating ground, and hence its value will be undefined.
	 * On the ATmega324PB, we enable pull-up by setting the PORTC flags high.
	 * See datasheet section 16 (I/O-ports) and user guide section 4 (Hardware User Guide).
	 */
	 
	DDRC |= (1 << LED0); // Set LED0 as output
	DDRC &= ~(1 << SW0); // Set SW0 as input
	PORTC |= (1 << SW0); // Enable pull-up on button SW0

	while(1){
		/*
		 * Here, you want to check if a button is depressed, and if yes, turn on the corresponding LED.
		 * If no, then do the opposite.
		 * In order to check a pin value, mask out that particular bit. (use bitwise AND)
		 * Bit masking is done like this:
		 * ((1 << BIT_POS) & REGISTER), which selects bit BIT_POS from register.
		 * If that bit is 0, the result will be 0. If it is 1, the result will be other than 0 (depending on bit pos).
		 */

		if(!(PINC & (1 << SW0))){ // If button is pressed (0 - LOW)
			PORTC &= ~(1 << LED0); // Sets output to 0, turns LED0 on
		}
		else{
			PORTC |= (1 << LED0); // Sets output to 1, turns LED off
		}
	}
}