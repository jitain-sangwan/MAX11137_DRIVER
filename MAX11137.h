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
#ifndef __MAX11137_H
#define __MAX11137_H

#include <stdint.h>
#include  <stdbool.h>
/* =================== DEFAUT MODE SETTING ============== */


/*        AMC SETTING       */

#define CS_RISING_EDGE_CONV  0
#define GET_CHANNEL_ID       0
#define POWER_MODE           0
#define RESET_MODE           0
#define CHANNEL_SELECTED     15
#define SCAN_MODE            2


/*         ACR SETTING       */

#define ECHO_MODE             1
#define SPM_MODE              0
#define NSCAN_MODE            3
#define NAVG_MODE             7
#define AVERAGING_ON          1
#define REFSEL_MODE           0


/*          */

/* ====================================================== */
/*
    This Union has 2 parts :-
    1: REG Var {dtype = uint16_t}

        This variable help us to write the value of the whole register in one go
        EG:-
        
        **************** TBD ************


    2: Val Struct{dtype= struct of 2 byte}

        This Structure provide you with facility to write specific value to individual part
        of the register without touching other parts

        EG:-

        ***************** TBD ************ 




*/
typedef union AMC_REG{
    uint16_t REG;
    struct{
            uint16_t RESERVED:1;
            
            uint16_t SWCNV   :1; //Set to 1 to initiate conversions with the rising edge of CS instead of cycling CNVST
                                // (internal clock mode only).
                                // This bit is used for the internal clock mode only and must be reasserted in the ADC
                                // mode control, if another conversion is desired.
            
            uint16_t CHAN_ID :1; /*External Clock Mode. Channel address is always present in internal clock mode.
                                  Set to 1, DOUT is a 16-bit data word containing a 4-bit channel address, followed by
                                  a 12-bit conversion result led by the MSB*/
            
            uint16_t PM      :2; /*Power Management Modes (Table 5). In external clock mode, PM[1:0] selects
                                  between normal mode and various power-down modes of operation. */

            uint16_t RESET   :2; /*RESET1 RESET0 FUNCTION
                                    0       0    No reset
                                    0       1    Reset the FIFO only (resets to zero)
                                    1       0    Reset all registers to default settings (includes FIFO)
                                    1       1    Unused*/

            uint16_t CHSEL   :4; /*Analog Input Channel Select register (Table 4).
                                  See Table 3 to determine which modes use CHSEL[3:0] for the channel scan
                                  instruction. READ DATA SHEET 
                                  KUCH PADH BHI LE SAB KUCH LIKHA LIKHAYA CHAHIYE KYA*/

            uint16_t SCAN    :4;  /*ADC Scan Control register (Table 3)*/
                                  
            uint16_t REG_CNTL:1;  /*Set to 0 to select the ADC Mode Control register*/
    }Val;
}AMC_REG_t;

typedef union ACR_REG{
    uint16_t REG;
    struct{

        uint16_t RESERVED    :2;

        uint16_t ECHO        :1;  /*Set to 0 to disable the instruction echo on DOUT.
                                    Set to 1 to echo back the DIN instruction given at time = n onto the DOUT line at
                                    time = n + 1. It takes 1 full cycle for the echoing to begin (Figure 8).*/
        
        uint16_t SPM         :2;  /*Set to 0 to disable the instruction echo on DOUT.
                                    Set to 1 to echo back the DIN instruction given at time = n onto the DOUT line at
                                    time = n + 1. It takes 1 full cycle for the echoing to begin (Figure 8).*/
        uint16_t NSCAN       :2;  /*Scans channel N and returns 4, 8, 12, or 16 results. Valid for repeat mode only.
                                        NSCAN1 NSCAN0 FUNCTION
                                        0       0       Scans channel N and returns 4 results.
                                        0       1       Scans channel N and returns 8 results.
                                        1       0       Scans channel N and returns 12 results.
                                        1       1       Scans channel N and returns 16 results.*/
        
        uint16_t NAVG        :2;  /*Valid for internal clock mode only.
                                    AVGON NAVG1 NAVG0 FUNCTION
                                    0       X       X   Performs 1 conversion for each requested
                                                        result.
                                    1       0       0   Performs 4 conversions and returns the
                                                        average for each requested result.
                                    1       0       1   Performs 8 conversions and returns the
                                                        average for each requested result.
                                    1       1       0   Performs 16 conversions and returns the
                                                        average for each requested result.
                                    1       1       1   Performs 32 conversions and returns the
                                                        average for each requested result*/
        
        uint16_t AVGON       :1;  /*Set to 1 to turn averaging on. Valid for internal clock mode only.
                                    Set to 0 to turn averaging off.*/

        uint16_t REFSEL      :1;  /*REFSEL VOLTAGE REFERENCE REF- CONFIGURATION
                                    0 External single-ended AIN15 ( for the 16-channel devices)
                                    1 External differential REF*/
        
        uint16_t CMD         :5;  /* Set to 10000 to select the ADC Configuration register.*/


    }Val;

}ACR_REG_t;


typedef union SCAN1_REG{

    uint16_t REG;
    struct {
        uint16_t RESERVED   :3; 
        uint16_t SCAN0      :1; /*Set to 1 to scan AIN0. Set to 0 to omit AIN0*/
        uint16_t SCAN1      :1; /*Set to 1 to scan AIN1. Set to 0 to omit AIN1*/
        uint16_t SCAN2      :1; /*Set to 1 to scan AIN2. Set to 0 to omit AIN2*/
        uint16_t SCAN3      :1; /*Set to 1 to scan AIN3. Set to 0 to omit AIN3*/
        uint16_t SCAN4      :1; /*Set to 1 to scan AIN4. Set to 0 to omit AIN4*/
        uint16_t SCAN5      :1; /*Set to 1 to scan AIN5. Set to 0 to omit AIN5*/
        uint16_t SCAN6      :1; /*Set to 1 to scan AIN6. Set to 0 to omit AIN6*/
        uint16_t SCAN7      :1; /*Set to 1 to scan AIN7. Set to 0 to omit AIN7*/
        uint16_t CMD        :5; /*Set to 10101 to select the Custom Scan1 register.*/

    }Val;
}SCAN1_REG_t;


typedef union SCAN0_REG{

    uint16_t REG;
    struct {
        uint16_t RESERVED    :3;
        uint16_t SCAN8       :1; /*Set to 1 to scan AIN8. Set to 0 to omit AIN8*/
        uint16_t SCAN9       :1; /*Set to 1 to scan AIN9. Set to 0 to omit AIN9*/
        uint16_t SCAN10      :1; /*Set to 1 to scan AIN10. Set to 0 to omit AIN10*/
        uint16_t SCAN11      :1; /*Set to 1 to scan AIN11. Set to 0 to omit AIN11*/
        uint16_t SCAN12      :1; /*Set to 1 to scan AIN12. Set to 0 to omit AIN12*/
        uint16_t SCAN13      :1; /*Set to 1 to scan AIN13. Set to 0 to omit AIN13*/
        uint16_t SCAN14      :1; /*Set to 1 to scan AIN14. Set to 0 to omit AIN14*/
        uint16_t SCAN15      :1; /*Set to 1 to scan AIN15. Set to 0 to omit AIN15*/
        uint16_t CMD         :5; /*Set to 10100 to select the Custom Scan1 register*/

    }Val;
}SCAN0_REG_t;


typedef union SAMP_SET_REG{
    uint16_t REG;
    struct {
        uint16_t RESERVED    :3;
        uint16_t SEQ_LENGTH  :8; /*8-bit binary word indicating desired sequence length. The equation is:
                                    Sequence length = SEQ_LENGTH + 1
                                    00000000 = Sequence length = 1
                                    11111111 = Sequence length = 256
                                    Coding: Straight binary
                                    Maximum length: 256 ADC conversions*/
        uint16_t cmd         :5;
    }Val;
}SAMP_SET_REG_t;


typedef enum
{

    AMC_R   = 0,
    ACR_R   = 16,
    SCAN1_R = 21,
    SCAN0_R = 20

}commands;






/* ============================== FUNCTION DECLARATIONS =============================== */

bool MAX11137_WRITE(uint8_t CMD,uint16_t* Data);
#endif