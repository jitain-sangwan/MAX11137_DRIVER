/*
 * MAX11137 Library
 * Author: Jitain Sangwan (A.k.a Pheonix)
 * 
 * This library provides functions for interacting with the MAX11137 ADC IC.
 * The functions enable the user to retrieve ADC counts from the MAX11137 and send
 * them to a microcontroller for further processing.
 * 
 * The library is released under the MIT License.
 * Feel free to use and modify the code for your projects.
 */


#include <stdio.h>
#include "MAX11137.h"

bool MAX11137_WRITE(uint8_t CMD,uint16_t Data)
{
    if(CMD!=AMC_R)
    {
        Data |=CMD<11;
    }
    SPI_SEND_RECIEVE((uint8_t*)&Data);
    return false;
}