
/**
  CMP2 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    cmp2.c

  @Summary
    This is the generated driver implementation file for the CMP2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for CMP2. 
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
#include "cmp2.h"
/**
  Section: Driver Interface
*/

void CMP2_Initialize(void)
{           

    // Disable the CMP module before the initialization
    CMP2_Enable(false);

    IEC6bits.AC2IE = 0;


    // DACOE disabled; HYSPOL Rising Edge; ALTINP Comparator; FLTREN enabled; FCLKSEL System Clock; CMPSTAT disabled; EXTREF AVDD; CMPPOL Not Inverted; CMPSIDL disabled; CMPON enabled; HYSSEL No hysteresis; INSEL CMP2A; RANGE AVDD is the maximum DAC output voltage; 
    CMP2CON = 0x8401;

    // CMREF 3724; 
    CMP2DAC = 0xE8C;
    
    // Clearing IF flag before enabling the interrupt.
    IFS6bits.AC2IF = 0;
    // Enabling CMP2 interrupt.
    IEC6bits.AC2IE = 1;

    CMP2_Enable(true);

}

void CMP2_Enable(bool enable)
{
    (CMP2CONbits.CMPON) = enable;
}

void CMP2_SetInputSource(CMP2_INPUT inpSrc)
{
    (CMP2CONbits.INSEL) = inpSrc;
}

bool CMP2_DACOutputStatusGet(void)
{
    return (CMP2CONbits.DACOE);
}

bool CMP2_StatusGet(void)
{
    return (CMP2CONbits.CMPSTAT);
}



/**
  End of File
*/
