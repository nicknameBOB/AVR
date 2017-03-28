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

// In task 2 we will use function for writing strings to the display. We want to make a simple game.
// Make the game Simon Says (or any equivalent simple game of your choice).
// The game should display instructions on the screen, and should use LEDs and buttons for interactivity.

// Example: Simon Says
// A pattern is played back on the LEDs. The user is now tasked with repeating the sequence on the buttons.
// If the user repeats the sequence correctly, the difficulty is increased, such that a new random number is added
// to the sequence. When there is a certain number in the sequence and the user correctly repeats the pattern
// the game is won.

// You are encouraged to reuse functions and code from earlier exercises.

#define SW1_BIT 1
#define SW1_PIN PINC
#define SW1_PORT PORTC
#define SW1_DDR DDRC
#define SW2_BIT 0
#define SW2_PIN PINA
#define SW2_PORT PORTA
#define SW2_DDR DDRA
#define SW3_BIT 1
#define SW3_PIN PINA
#define SW3_PORT PORTA
#define SW3_DDR DDRA

#define LED1_BIT 5
#define LED1_PORT PORTD
#define LED1_DDR DDRD
#define LED2_BIT 4
#define LED2_PORT PORTD
#define LED2_DDR DDRD
#define LED3_BIT 3
#define LED3_PORT PORTA
#define LED3_DDR DDRA

uint8_t waitForBtnPress(int btn);
void waitForBtnRelease(int btn);
void setLED(int led);
void resetLED(int led);
void flashLED(int led);
void showSequence();
bool trySequence();

#define WIN_CNT 10
#define LED_DELAY 500
int8_t sequence[WIN_CNT];
int curDifficulty = 3;

int main()
{
    time_t time1, time2;
    time(&time1);
    DISP_init();

    SW1_PORT &= ~(1 << SW1_BIT);
    SW1_PIN |= (1 << SW1_BIT); // enable pull-up
    SW2_PORT &= ~(1 << SW2_BIT);
    SW2_PIN |= (1 << SW2_BIT); // enable pull-up
    SW3_PORT &= ~(1 << SW3_BIT);
    SW3_PIN |= (1 << SW3_BIT); // enable pull-up

    LED1_DDR |= (1 << LED1_BIT);
    LED2_DDR |= (1 << LED2_BIT);
    LED3_DDR |= (1 << LED3_BIT);
    LED1_PORT |= (1 << LED1_BIT);
    LED2_PORT |= (1 << LED2_BIT);
    LED3_PORT |= (1 << LED3_BIT);

    DISP_print("Welcome to\n");
    DISP_print("   SIMON SAYS\n");
    DISP_print("Press any button");
    DISP_print("to start game!");

    for(int i = 0; i < WIN_CNT; i++)
    {
        sequence[i] = -1;
    }

    waitForBtnPress(-1);

    time(&time2);

    srand(difftime(time1, time2));

    while(true)
    {
        for(int i = 0; i < WIN_CNT; i++)
        {
            if(sequence[i] == -1 && i < curDifficulty)
            {
                sequence[i] = rand() % 3;
            }
        }

        showSequence();

        if(trySequence())
        {
            DISP_clear();
            DISP_print("Correct!\n");
            if(curDifficulty == WIN_CNT - 1)
            {
                DISP_print("Game won!");
                break;
            }
            else
            {
                curDifficulty++;
                DISP_print("Increasing\n");
                DISP_print("difficulty to ");
                DISP_putc('0' + curDifficulty);
                DISP_print("\nPress any button");
                waitForBtnPress(-1);
                continue;
            }
        }
        else
        {
            DISP_clear();
            DISP_print("Incorrect!\n\n");
            DISP_print("Game over.");
            break;
        }
    }

    while(1);
}

bool trySequence()
{
    DISP_clear();
    DISP_print("Try to repeat\n");
    DISP_print("it now!\n\n");

    int i = 0;
    bool correct = true;

    while(correct)
    {
        uint8_t btn = waitForBtnPress(-1);
        setLED(btn);
        waitForBtnRelease(btn);
        correct = sequence[i] == btn;
        resetLED(btn);

        i++;
        if(sequence[i] == -1)
        {
            break;
        }
    }

    return correct;
}

void showSequence()
{
    DISP_clear();
    DISP_print("Watch the\n");
    DISP_print("sequence\n");
    DISP_print("carefully.");
    _delay_ms(3000);


    for(int i = 0; i < curDifficulty; i++)
    {
        flashLED(sequence[i]);
    }
}

void waitForBtnRelease(int btn)
{
    bool curState[3];
    curState[0] = SW1_PIN & (1 << SW1_BIT);
    curState[1] = SW2_PIN & (1 << SW2_BIT);
    curState[2] = SW3_PIN & (1 << SW3_BIT);

    while(!curState[btn])
    {
        system_tick();

        curState[0] = SW1_PIN & (1 << SW1_BIT);
        curState[1] = SW2_PIN & (1 << SW2_BIT);
        curState[2] = SW3_PIN & (1 << SW3_BIT);
    }
}

uint8_t waitForBtnPress(int btn)
{
    bool curState[3];
    bool lastState[3];
    curState[0] = SW1_PIN & (1 << SW1_BIT);
    curState[1] = SW2_PIN & (1 << SW2_BIT);
    curState[2] = SW3_PIN & (1 << SW3_BIT);

    while(true)
    {
        system_tick();

        lastState[0] = curState[0];
        lastState[1] = curState[1];
        lastState[2] = curState[2];
        curState[0] = SW1_PIN & (1 << SW1_BIT);
        curState[1] = SW2_PIN & (1 << SW2_BIT);
        curState[2] = SW3_PIN & (1 << SW3_BIT);

        if(btn != -1)
        {
            if(!curState[btn] && lastState[btn])
            {
                return btn;
            }
        }
        else
        {
            for(uint8_t i = 0; i < 3; i++)
            {
                if(!curState[i] && lastState[i])
                {
                    return i;
                }
            }
        }
    }
}

void setLED(int led)
{
    switch(led)
    {
        case 0:
           LED1_PORT &= ~(1 << LED1_BIT);
           break;

        case 1:
           LED2_PORT &= ~(1 << LED2_BIT);
           break;

        case 2:
           LED3_PORT &= ~(1 << LED3_BIT);
           break;
    }
}

void resetLED(int led)
{
    switch(led)
    {
        case 0:
           LED1_PORT |= (1 << LED1_BIT);
           break;

        case 1:
           LED2_PORT |= (1 << LED2_BIT);
           break;

        case 2:
           LED3_PORT |= (1 << LED3_BIT);
           break;
    }
}

void flashLED(int led)
{
    setLED(led);
    _delay_ms(LED_DELAY);
    resetLED(led);
    _delay_ms(LED_DELAY * 0.5);
}
