
/**
  CMP3 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    cmp3.c

  @Summary
    This is the generated driver implementation file for the CMP3 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for CMP3. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.55
        Device            :  dsPIC33EP64GS504
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.34
        MPLAB             :  MPLAB X v4.15
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
#include "cmp3.h"
/**
  Section: Driver Interface
*/

void CMP3_Initialize(void)
{           

    // Disable the CMP module before the initialization
    CMP3_Enable(false);

    IEC6bits.AC3IE = 0;


    // DACOE disabled; HYSPOL Rising Edge; ALTINP Alternate; FLTREN enabled; FCLKSEL System Clock; CMPSTAT disabled; EXTREF AVDD; CMPPOL Inverted; CMPSIDL disabled; CMPON enabled; HYSSEL No hysteresis; INSEL PGA1; RANGE AVDD is the maximum DAC output voltage; 
    CMP3CON = 0x8407;

    // CMREF 3208; 
    CMP3DAC = 0xC88;
    
    // Clearing IF flag before enabling the interrupt.
    IFS6bits.AC3IF = 0;
    // Enabling CMP3 interrupt.
    IEC6bits.AC3IE = 1;

    CMP3_Enable(true);

}

void CMP3_Enable(bool enable)
{
    (CMP3CONbits.CMPON) = enable;
}

void CMP3_SetInputSource(CMP3_INPUT inpSrc)
{
    (CMP3CONbits.INSEL) = inpSrc;
}

bool CMP3_DACOutputStatusGet(void)
{
    return (CMP3CONbits.DACOE);
}

bool CMP3_StatusGet(void)
{
    return (CMP3CONbits.CMPSTAT);
}



/**
  End of File
*/
