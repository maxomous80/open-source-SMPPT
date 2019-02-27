
/**
  PGA1 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    pga1.c

  @Summary
    This is the generated source file for the PGA1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for PGA1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.55
        Device            :  dsPIC33EP64GS504
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.34
        MPLAB 	          :  MPLAB X v4.15
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "pga1.h"

/**
  Section: Driver Interface
*/


void PGA1_Initialize (void)
{
    uint32_t calibrationAddress;

    //Disable the module 
    PGA1CONbits.PGAEN = 0;

    calibrationAddress = 0x800E4C;  //Flash address
    TBLPAG = (uint16_t)((calibrationAddress) >> 16);

    // Calibration data from a flash location
    PGA1CAL = __builtin_tblrdl((uint16_t)((calibrationAddress) & 0xFFFF));
    // SELPI PGA1P2; PGAOEN Not Connected; SELNI Ground; PGAEN enabled; GAIN 4x; 
    PGA1CON = 0x8802;
}


void PGA1_Enable( void )
{
    /* Enable PGA */
    PGA1CONbits.PGAEN = 1;
}

void PGA1_Disable( void )
{
    /* Disable PGA */
    PGA1CONbits.PGAEN = 0;
}

void PGA1_GainSet( PGA1_GAIN gainValue)
{
    /* Sets gain for PGA */
    PGA1CONbits.GAIN = gainValue;

}

/**
 End of File
*/
