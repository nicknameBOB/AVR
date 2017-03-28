/*
 * Kveld2Timers.c
 *
 * Created: 14.04.2016 15.17.59
 * Author : medlem
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED0 7
#define LED1 5	//koblet til tc1 oca gitt at oled1 er koblet til ext1
#define LED2 4	//koblet til tc1 ocb
#define LED3 3

int main(void)
{
	/*	In this exercise we will get LEDs to blink at even intervals using interrupts
		First set up the LEDs like in the previous exercise. You can either copy paste from the previous exercise or start fresh
		The timer used in this exercise is timer1, find out which LEDs it is connected to
	*/
	

			
	/*	We use clear timer on compare match (ctc) mode and set the prescaler to clk=clk/256
		This is accomplished by setting the right bits in the timer control registers A and B, see the datasheet
	*/

	
	/*	Next enable interrupts from the timer module, at least the Output Compare A interrupt*/

	/*	To be able to react to interrupts from module, the mega has to enable interrupts globally.
		This is done via the function sei(), which is located in the (already included) header file <avr/interrupt.h>
		Note that this step is NOT the same as the previous, where we enabled interrupts for the timer module.
	*/
	sei();
	
		
	/*	To setup the timer, first set the max-value of the timer to 62500 This value effectively determines the 
		frequency with which the timer will overflow(it will be the timers new TOP value).
		When everything is working, try to modify this value and observe how this change affects the period.
		Which value of the output compare register will make our uC interrupt each 1/2s?
	*/ 
	
	/* NOTE: remember to fill in the ISR in the bottom of the file, else nothing will happen */
	
    while(1)
    {
        //Do nothing, the code in the ISR will execute periodically without any involvement of the main() loop. 
    }
}

ISR (TIMER1_COMPA_vect){
	// TODO: Do something fancy with your leds.
}	

/*	BONUS: 
	Set up interrupts for output compare B. What is the period of this interrupt?
	LED1 and LED2 are connected to output compare 1 and output compare 2. 
	Try to toggle the output pins on compare match for one, then both channels
	TCCR1A |= (1<<COM1A0)|(1<<COM1B0);
*/