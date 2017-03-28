//
// task3.c
//
// Created: 07.04.2016
// Author: Asbjørn Espe
//

#define F_CPU 16000000UL

// System headers
#include <avr/io.h>  // Pin io
#include <util/delay.h>

// Project headers
#include "display.h"

// In task 3 we will expand the display driver to accept tab characters ('\t').
// Open display.c and try to understand the code. Then write support for the tab character.
// Hint: Look at the implementation of '\n'.
// Finally connect the IO board and read temperatur with ADC. Display it on the screen.

void print16b(uint16_t data);

int main()
{
    DISP_init();

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128

    ADMUX |= (1 << REFS0); // Set ADC reference
    ADMUX |= (1 << MUX2); // Use ADC4

    // No MUX values needed to be changed to use ADC0

    ADCSRA |= (1 << ADATE);  // Set ADC to auto trigger
    ADCSRA |= (1 << ADEN);  // Enable ADC
    ADCSRA |= (1 << ADSC);  // Start A2D Conversions


    while(1)
    {
        DISP_clear();
        DISP_print("Light:\t");
        print16b(ADC);
        _delay_ms(500);
    }
}

void printNibble(uint8_t nibble)
{
    if(nibble < 0x0A)
    {
        DISP_putc('0' + nibble);
    }
    else
    {
        DISP_putc('A' + (nibble - 0x0A));
    }
}

void print16b(uint16_t data)
{
    DISP_print("0x");
    printNibble((data >> 12) & 0x0F);
    printNibble((data >> 8) & 0x0F);
    printNibble((data >> 4) & 0x0F);
    printNibble(data & 0x0F);
}
