#include "spi_driver.h"

void SPI_SEND_RECIEVE(uint8_t* txbuff , uint8_t* rxbuff)
{
    CS_LOW
    HAL_Delay(1);
    SPI_Transmit_Recieve(SPI,txbuff,rxbuff,2,1000);
    HAL_Delay(1);
    CS_HIGH
}