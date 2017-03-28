//
// task3.c
//
// Created: 07.04.2016
// Author: Asbjørn Espe
//

#define F_CPU 16000000UL

// System headers
#include <avr/io.h>  // Pin io

// Project headers
#include "display.h"

// In task 3 we will expand the display driver to accept tab characters ('\t').
// Open display.c and try to understand the code. Then write support for the tab character.
// Hint: Look at the implementation of '\n'.
// Finally connect the IO board and read light value with ADC. Display it on the screen.

int main()
{
    DISP_init();

    // Enable ADC from the light sensor..


    while(1)
    {
        DISP_clear();
        DISP_print("Light:\t");

        // Print value from light sensor here...

        _delay_ms(500);
    }
}
