//
// spi.c
//
// Created: 07.04.2016
// Author: Asbjørn Espe
//


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
    //
    // CODE GOES HERE


    // Now enable SPI, Master and set clock rate
    //
    // CODE GOES HERE
}

void SPI_MasterTransmit(char cData)
{
    // First select the correct slave by setting the slave select (SS) bit LOW
    //
    // CODE GOES HERE


    // Then start the transmission by assigning the data to the SPI data register
    //
    // CODE GOES HERE


    // Now wait for the data transmission to complete by periodically checking the SPI status register
    //
    // CODE GOES HERE


    // Finally set the slave select bit HIGH before leaving the function
    //
    // CODE GOES HERE

}
