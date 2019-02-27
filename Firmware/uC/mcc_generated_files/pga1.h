/**
  PGA1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    pga1.h

  @Summary
    This is the generated header file for the PGA1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for PGA1.
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

#ifndef _PGA1_H
#define _PGA1_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
 Section: Data Type Definitions
*/

/**
  PGA1 Gain Enumeration

  @Summary
    Defines the gain enumeration for PGA1.

  @Description
    This defines the gain enumeration for PGA1.
 */
typedef enum {
    PGA1_GAIN_64x  = 6,
    PGA1_GAIN_32x  = 5,
    PGA1_GAIN_16x  = 4,
    PGA1_GAIN_8x   = 3,
    PGA1_GAIN_4x   = 2
}PGA1_GAIN;

/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes PGA instance : 1

  @Description
    This routine initializes hardware for PGA driver instance 
    for : 1 index. This routine must be called before any other
    PGA1 routine is called.

  @Preconditions
    None
	
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    PGA1_Initialize();
    </code>
*/
void PGA1_Initialize (void);

/**
  @Summary
    Enables PGA

  @Description
    This routine enables PGA

  @Preconditions
    The PGA1_Initialize routine must have been called for the specified
    PGA1 driver instance.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PGA1_Enable();
    </code>
*/

void PGA1_Enable( void );

/**
  @Summary
    Disables PGA

  @Description
    This routine disables PGA

  @Preconditions
    None

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PGA1_Disable();
    </code>
*/

void PGA1_Disable( void );

/**
  @Summary
    Sets gain for PGA

  @Description
    This routine sets gain for PGA

  @Preconditions
    None

  @Param
    gainValue -   Gain value to be set.

  @Returns
    None
 
  @Example 
    <code>
    PGA1_GainSet();
    </code>
*/

void PGA1_GainSet( PGA1_GAIN gainValue);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_PGA1_H
    
/**
 End of File
*/
