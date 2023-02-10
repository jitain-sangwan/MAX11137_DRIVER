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
// typedef struct Register{
//     void *ptr;
// }Register_t;

// Register_t Register_array[5];



bool MAX11137_WRITE(uint8_t CMD,uint16_t Data)
{
    switch (CMD)
    {
    case AMC_R:
        AMC_REG_t AMC;
        AMC.Val.SWCNV   = 0;
        AMC.Val.CHAN_ID = CHANNEL_SELECTED;
        AMC.Val.PM      = POWER_MODE;
        AMC.Val.RESET   = RESET_MODE;
        AMC.Val.CHSEL   = CS_RISING_EDGE_CONV;
        AMC.Val.SCAN    = SCAN_MODE;
        AMC.Val.REG_CNTL= 0;
        Data = AMC.REG;
        break;
    
    default:
        break;
    }

    if(CMD!=AMC_R)
    {
        Data |=CMD<11;
    }
    // datas
    SPI_SEND_RECIEVE((uint8_t*)&Data);
    return false;
}