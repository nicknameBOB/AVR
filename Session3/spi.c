//
// spi.c
//
// Created: 07.04.2016
// Author: Asbjørn Espe
//

#define DSP_MOSI_DDR DDRB
#define DSP_MOSI_PORT PORTB
#define DSP_MOSI_BIT 5
#define DSP_SS_DDR DDRB
#define DSP_SS_PORT PORTB
#define DSP_SS_BIT 4
#define DSP_SCK_DDR DDRB
#define DSP_SCK_PORT PORTB
#define DSP_SCK_BIT 7
#define DSP_MODE_DDR DDRA
#define DSP_MODE_PORT PORTA
#define DSP_MODE_BIT 2
#define DSP_RST_DDR DDRC
#define DSP_RST_PORT PORTC
#define DSP_RST_BIT 0

// System headers
#include <avr/io.h>

// Project headers
#include "spi.h"

// In this file, you will need to write the contents of the SPI communiaction routines.
// You need to setup SPI communication in SPI_MasterInit() and
// transmit data in SPI_MasterTransmit(...).
//
// HINT: Check out the defines in the file defines.h to see defines
// such as data direction registers and bit positions, and as always:
// RTFD


void SPI_MasterInit()
{
    // Initialize the SPI port as master
    // You will need to set MOSI, SCK, SS (slave select) as outputs
    DSP_MOSI_DDR |= (1 << DSP_MOSI_BIT);
    DSP_SCK_DDR |= (1 << DSP_SCK_BIT);
    DSP_SS_DDR |= (1 << DSP_SS_BIT);

    // Now enable SPI, Master and set clock rate
    SPCR0 = (1 << SPE0) | (1 << MSTR0) | (1 << SPR00) | (1 << CPOL0) | (1 << CPHA0);
}

void SPI_MasterTransmit(char cData)
{
    // First select the correct slave by setting the slave select (SS) bit LOW
    DSP_SS_PORT &= ~(1 << DSP_SS_BIT);

    // Then start the transmission by assigning the data to the SPI data register
    SPDR0 = cData;

    // Now wait for the data transmission to complete by periodically checking the SPI status register
    while(!(SPSR0 & (1 << SPIF0)));

    // Finally set the slave select bit HIGH before leaving the function
    DSP_SS_PORT |= (1 << DSP_SS_BIT);
}
