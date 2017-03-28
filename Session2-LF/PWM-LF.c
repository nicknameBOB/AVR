/*
 * Kveld2PWM.c
 *
 * Created: 4/20/2016 9:42:23 AM
 * Author : Vlad
 */ 

//section 18, timer/counter
//fast pwm

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

//PWM fra Timer 1 koblet til LED1 og LED2, gitt at OLED1 ligger paa EXT1

#define LED1 PORTD5 //OC1A
#define LED2 PORTD4	//OC1B
#define LED3 PORTA3
#define SW1	PINC1
#define SW2	PINA0
#define SW3 PINA1

bool SW1_pressed,SW2_pressed;

int main(void)
{	
	//sett opp LED pins som utgang
	DDRD |= (1<<LED1)|(1<<LED2);
	DDRA |= (1<<LED3);
	
	//husk pullups for knappene
	PORTC |= (1<<SW1);
	PORTA |= (1<<SW2)|(1<<SW3);

	/*	Set the timer/counter for 8 bit fast pwm (se i databladet etter timer/counter control register A, kap 18.11)
		Det er en av de måtene vi kan bruke timers på for å gjøre det vi trenger i oppgaven */
	TCCR1A |= (1<<WGM12)|(1<<WGM10);
	
	/* Set OC1A og OC1B pins on compare match, clear at bottom
		Dette er en inverterende mode pga leds er koblet som active low. 
		Da er lysutgangen proporsjonelt med verdien som ligger i output compare register
		*/
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0);
	
	/*	velg clock source til prescaler og sette den til en fornuftig verdi 
		(her er vi ikke interesert i perioden paa timeren, bare duty cycle til PWM)
		Denne operasjonen starter timeren.*/
	TCCR1B |= (1<<CS11);
	
	/*	output compare registerene bestemmer PWM duty cycle når timeren er i 8bit Fast PWM.
		prøv å leke med verdiene i registrene for å se hvordan PWM og lysstyrken blir påvirket*/
	OCR1A = 0x00;	//fadeLevel;
	OCR1B = 0xff;
	
		
    while (1) 
    {
		/*	Nå skal dere få det til at hvis man trykker på SW0,minske lysstyrken til LED1 mens lysstyrken til LED2 øker
			Og akkurat motsatt for SW1 */
		//hvis sw1 er trykt
		if (! (PINC & (1<<SW1)))
		{
			if (!SW1_pressed)
			{
				//output compare register bestemmer PWM duty cycle
				//saa vi vil øke duty cycle for første leds mens vi minker for den andre
				OCR1A = (OCR1A<<1) + 1;	//leg til 1 saa vi ikke shifter tilbake til 0
				OCR1B >>= 1;
				SW1_pressed=true;
			}
		}
		else
			SW1_pressed=false;
	
		//akkurat motsatt for den andre switch
		if (! (PINA & (1<<SW2)))
		{
			if (!SW2_pressed)
			{
				OCR1A >>=1;
				OCR1B = (OCR1B<<1) + 1;
				SW2_pressed=true;
			}
		}
		else
			SW2_pressed=false;

    }
}