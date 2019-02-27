
/**
  CMP1 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    cmp1.c

  @Summary
    This is the generated driver implementation file for the CMP1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for CMP1. 
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
#include "cmp1.h"
/**
  Section: Driver Interface
*/

void CMP1_Initialize(void)
{           

    // Disable the CMP module before the initialization
    CMP1_Enable(false);

    IEC1bits.AC1IE = 0;


    // DACOE disabled; HYSPOL Rising Edge; ALTINP Comparator; FLTREN enabled; FCLKSEL System Clock; CMPSTAT disabled; EXTREF AVDD; CMPPOL Not Inverted; CMPSIDL disabled; CMPON enabled; HYSSEL No hysteresis; INSEL CMP1A; RANGE AVDD is the maximum DAC output voltage; 
    CMP1CON = 0x8401;

    // CMREF 4090; 
    CMP1DAC = 0xFFA;
    
    // Clearing IF flag before enabling the interrupt.
    IFS1bits.AC1IF = 0;
    // Enabling CMP1 interrupt.
    IEC1bits.AC1IE = 1;

    CMP1_Enable(true);

}

void CMP1_Enable(bool enable)
{
    (CMP1CONbits.CMPON) = enable;
}

void CMP1_SetInputSource(CMP1_INPUT inpSrc)
{
    (CMP1CONbits.INSEL) = inpSrc;
}

bool CMP1_DACOutputStatusGet(void)
{
    return (CMP1CONbits.DACOE);
}

bool CMP1_StatusGet(void)
{
    return (CMP1CONbits.CMPSTAT);
}



/**
  End of File
*/
