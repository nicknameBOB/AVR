//
// task2.c
//
// Created: 07.04.2016
// Author: Asbjørn Espe
//

#define F_CPU 16000000UL

// System headers
#include <avr/io.h>  // Pin io
#include <util/delay.h>  // _delay_ms();
#include <stdbool.h>  // Boolean type
#include <stdlib.h>  // rand(), srand()
#include <time.h>  // time functions for random number seed

// Project headers
#include "display.h"

// In task 2 we will use the function for writing strings to the display. We want to make a simple game.
// Make the game Simon Says (or any equivalent simple game of your choice).
// The game should display instructions on the screen, and should use LEDs and buttons for interactivity.

// Example: Simon Says
// A pattern is played back on the LEDs. The user is now tasked with repeating the sequence on the buttons.
// If the user repeats the sequence correctly, the difficulty is increased, such that a new random number is added
// to the sequence. When there is a certain number in the sequence and the user correctly repeats the pattern
// the game is won.

// You are encouraged to reuse functions and code from earlier exercises.

int main()
{
    // CODE GOES HERE
    //
    // Good luck!


    // Infinite loop to keep the chip going
    while(1);
}
