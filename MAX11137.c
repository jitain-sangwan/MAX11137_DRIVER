#include <stdio.h>
#include "MAX11137.h"

bool MAX11137_WRITE(uint8_t CMD,uint16_t Data)
{
    if(CMD!=AMC_R)
    {
        Data |=CMD<11;
    }
    SPI_SEND_RECIEVE((uint8_t*)&Data);
}