#include <main.h>
#include <stdint.h>
/* =============================== PIN DEFINES ============================================*/
#define CS_LOW   0// add your chip select LOW function here
#define CS_HIGH  0// add your chip select HIGH function here
#define SPI      0// add your SPI Handel Here

/*=========================================================================================*/

/*=============================== Declare Functions ================================================*/
void SPI_SEND_RECIEVE(uint8_t* txbuff , uint8_t* rxbuff);