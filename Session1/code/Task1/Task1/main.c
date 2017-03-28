/*
 * Task1.c
 *
 * Created: 4/14/2016 10:11:43 AM
 * Author : Thomas Stenseth
 */ 

/**
 * F_CPU tells the timer what the CPU's clock frequency is, such that the timer will count correctly.
 * Note that this DOES NOT set the clock speed, it just informs the timer.
 * If this is set wrong, the chip will work as normal, but software delays will be too long (if set too low) or too short (if set too high).
 * Example: set F_CPU to 2 MHz => "#define F_CPU 2000000UL". UL = unsigned long
 * F_CPU must be defined before including headers.
 */

#define F_CPU 16000000UL // The ATmega324PB operates at 16 MHz

/**
 * System headers bellow
 */

#include <avr/io.h> // The pin I/O library
#include <util/delay.h> // So we can use delay functions

/**
 * Define helpers for pin bit positions.
 * The LED0 on the ATmega324PB main board is connected to pin 7 on port C (PINC7).
 * Check the datasheet to find out which pins on which ports (PINxn) the different LEDs and buttons are connected to.
 */

#define LED0 PINC7	// LED0 is defined as PINC7 ---> LED0 holds the same value as PINC7 (alternative: "#define LED0 7")

int main (void){
	/**
	 * We want to send signals to the LEDs, in order to turn the off and on.
	 * In the AVR world we have the following:
	 * DDRx: 1 is output, 0 is input
 	 * LED: 1 LED is off, 0 LED is on, this is called active-low
	 * Button: 1 button is open, 0 button is pressed, this is called active-low
	 *
	 * Remember bit set logic:
	 * Set to 1: FLAG |= ( 1 << BIT_POS ) - using 'or' so we only change the one we want and leave the others untouched
	 * Set to 0: FLAG &= ~( 1 << BIT_POS ) - same thing here but using 'and', find paper and a logic-table, and try it out if you want to know how it works
	 */

	DDRC |= (1 << LED0); // Set LED0 as output - Using "C" in DDRx since the LED is connected to port C on the microcontroller

	/*
	* The usual way to run microcontrollers is using a simple infinite loop
	*/

	while(1){
		PORTC ^= (1 << LED0); // Changes the state of LED0 by XOR-ing the last state. Check the XOR-table to find out how this works. 
		// Non-compressed: PORTC = PORTC ^ (1 << LED0);
		_delay_ms(500);  // Adds a 500ms delay to make the LED blink
	}
}