/**
  ADC1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.h

  @Summary
    This is the generated header file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ADC1.
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

#ifndef _ADC1_H
#define _ADC1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
/**
  Section: ISR Helper Macros
*/

/**
  Section: Data Types
*/

/** ADC1 Core 0 Channel Definition

 @Summary 
   Defines the Core 0 channels available for conversion
 
 @Description
   This routine defines the channels that are available conversion.
 
 Remarks:
   None
*/
typedef enum 
{   
    ADC1_CORE0_AN0  =  0,

    ADC1_CORE0_PGA1  =  1,

    ADC1_CORE0_AN0ALT  =  3,
} ADC1_CORE0_CHANNEL;
/** ADC1 Core 1 Channel Definition
 @Summary 
   Defines the Core 1 channels available for conversion
 
 @Description
   This routine defines the channels that are available conversion.
 
 Remarks:
   None
*/
typedef enum 
{   
    ADC1_CORE1_AN1  =  0,

    ADC1_CORE1_AN8  =  1,

    ADC1_CORE1_AN1ALT  =  3,
} ADC1_CORE1_CHANNEL;
/** ADC1 Core 2 Channel Definition
 @Summary 
   Defines the Core 2 channels available for conversion
 
 @Description
   This routine defines the channels that are available conversion.
 
 Remarks:
   None
*/
typedef enum 
{   
    ADC1_CORE2_AN2  =  0,

    ADC1_CORE2_AN11  =  1,
} ADC1_CORE2_CHANNEL;
/** ADC1 Core 3 Channel Definition
 @Summary 
   Defines the Core 3 channels available for conversion
 
 @Description
   This routine defines the channels that are available conversion.
 
 Remarks:
   None
*/
typedef enum 
{   
    ADC1_CORE3_AN3  =  0,

    ADC1_CORE3_AN15  =  1,
} ADC1_CORE3_CHANNEL;
/** ADC1 Data Format Type Definition
 
 @Summary 
   Defines the data format types available
 
 @Description
   This routine defines the data format types that are available for the module 
   to use.
 
 Remarks:
   None
 */
typedef enum 
{
    ADC1_FORM_INT   = 0, /* Integer */
    ADC1_FORM_FRACT = 1  /* Fraction */
} ADC1_FORM_TYPE;

/** ADC1 Resolution Type Definition
 
 @Summary 
   Defines the resolution types available
 
 @Description
   This routine defines the resolution types that are available for the module 
   to use.
 
 Remarks:
   None
 */
typedef enum 
{
    ADC1_RESOLUTION_6_BIT    = 0, /* 6-bit ADC1 operation */
    ADC1_RESOLUTION_8_BIT    = 1, /* 8-bit ADC1 operation */
    ADC1_RESOLUTION_10_BIT   = 0, /* 10-bit ADC1 operation */
    ADC1_RESOLUTION_12_BIT   = 1  /* 12-bit ADC1 operation */
} ADC1_RESOLUTION_TYPE;

/** ADC1 Trigger Source Definition
 
 @Summary 
   Defines the trigger sources available
 
 @Description
   This routine defines the trigger sources that are available for the module 
   to use.
 
 Remarks:
   None
*/
typedef enum 
{
    ADC1_TRIGGER_SOURCE_Common_Software_Trigger  =  0x1,
    ADC1_TRIGGER_SOURCE_PWM_Special_Event_Trigger  =  0x4,
    ADC1_TRIGGER_SOURCE_PWM3_Secondary_Trigger  =  0x11,
    ADC1_TRIGGER_SOURCE_PWM2_Primary_Trigger  =  0x6,
    ADC1_TRIGGER_SOURCE_PWM3_Current_Limit_Trigger  =  0x1a,
    ADC1_TRIGGER_SOURCE_ADCTRG31  =  0x1f,
    ADC1_TRIGGER_SOURCE_PWM2_Secondary_Trigger  =  0x10,
    ADC1_TRIGGER_SOURCE_Level_Software_Trigger  =  0x2,
    ADC1_TRIGGER_SOURCE_PWM1_Current_Limit_Trigger  =  0x18,
    ADC1_TRIGGER_SOURCE_PWM_Secondary_Special_Event_Trigger  =  0xe,
    ADC1_TRIGGER_SOURCE_PWM3_Primary_Trigger  =  0x7,
    ADC1_TRIGGER_SOURCE_PWM1_Secondary_Trigger  =  0xf,
    ADC1_TRIGGER_SOURCE_PWM2_Current_Limit_Trigger  =  0x19,
    ADC1_TRIGGER_SOURCE_PWM1_Primary_Trigger  =  0x5,
    ADC1_TRIGGER_SOURCE_OC1  =  0x16,
    ADC1_TRIGGER_SOURCE_None  =  0x0,
    ADC1_TRIGGER_SOURCE_TMR2  =  0xd,
    ADC1_TRIGGER_SOURCE_OC2  =  0x17,
    ADC1_TRIGGER_SOURCE_TMR1  =  0xc,
} ADC1_TRIGGER_SOURCE;
/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes ADC instance : 1

  @Description
    This routine initializes the ADC driver instance for : 1
    index, making it ready for clients to open and use it. It also initializes any
    internal data structures.
    This routine must be called before any other ADC routine is called. 

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Comment
    
 
  @Example
    <code>
        int conversion;
        ADC1_Initialize();
        while(!ADC1_IsCore0ConversionComplete())
        {
            ADC1_Tasks();   
        }
        conversion = ADC1_Core0ConversionResultGet();
    </code>

*/

void ADC1_Initialize (void);

/**
  @Summary
    Clears interrupt flag

  @Description
    This routine is used to clear the interrupt flag manually.
 
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

inline static void ADC1_InterruptFlagClear(void)
{
    IFS0bits.ADCIF = 0;   
}
/**
  @Summary
    Enables interrupts.

  @Description
    This routine is used to enable the ADC1 interrupt manually.
 
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/
inline static void ADC1_InterruptEnable(void)
{  
    IEC0bits.ADCIE = 1;   
}
/**
  @Summary
    Disables interrupts

  @Description
    This routine is used to disable the ADC1 interrupt manually.
 
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

inline static void ADC1_InterruptDisable(void)
{   
    IEC0bits.ADCIE = 0;
}
/**
  @Summary
    Allows module to be enabled manually

  @Description
    This routine is used to enable the ADC1 module manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
*/
inline static void ADC1_Enable(void)
{
    ADCON1Lbits.ADON = 1;
}
/**
  @Summary
    Allows module to be disabled manually

  @Description
    This routine is used to disable the ADC1 module manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
*/

inline static void ADC1_Disable(void)
{
    ADCON1Lbits.ADON = 0;
}
/**
  @Summary
    Allows software common trigger to be enabled manually

  @Description
    This routine is used to enable the ADC1 software common trigger manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function. 
 
  @Returns
    None

  @Param
    None
  
  @Example
*/

inline static void ADC1_SoftwareTriggerEnable(void)
{
    ADCON3Lbits.SWCTRG = 1;
}
/**
  @Summary
    Allows software level-sensitive common trigger to be enabled manually

  @Description
    This routine is used to enable the ADC1 software level-sensitive common trigger manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function. 
 
  @Returns
    None

  @Param
    None
  
  @Example
*/

inline static void ADC1_SoftwareLevelTriggerEnable(void)
{
    ADCON3Lbits.SWLCTRG = 1;
}
/**
  @Summary
    Callback for ADC1 common interrupt.

  @Description
    This routine is callback for ADC1 common interrupt

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to the example of ADC1_Initialize();
*/
void ADC1_CallBack(void);

/**
  Section: Interface Routines: Dedicated Core
*/
/**
  @Summary
    Enables power for Core 0 

  @Description
    This routine is used to set the analog and digital power for ADC1 Core 0.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core0PowerEnable(void);
/**
  @Summary
    Calibrates dedicated Core 0 

  @Description
    This routine is used to calibrate the ADC1 Core 0.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core0Calibration(void);
/**

  @Summary
    Sets Core 0 channel

  @Description
    This routine is used to set the ADC1 Core 0 channel manually.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

inline static void ADC1_Core0ChannelSelect(ADC1_CORE0_CHANNEL channel)
{
   ADCON4Hbits.C0CHS = channel;
}
/**
  @Summary
    Returns the ADC1 conversion value for Core 0.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The core required must be enabled and calibrated before calling this routine 
    using ADC1_Core0PowerEnable() and ADC1_Core0Calibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsCore0ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */

inline static uint16_t ADC1_Core0ConversionResultGet(void) 
{
    return ADCBUF0;
}
/**
  @Summary
    Allows selection of a resolution mode for conversion

  @Description
    This routine is used to select desired resolution mode for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required resolution mode from the ADC1_RESOLUTION_TYPE list
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/

inline static void ADC1_Core0ResolutionModeSet( ADC1_RESOLUTION_TYPE resolution )
{
    ADCORE0Hbits.RES = resolution;
}
/**
  @Summary
    Returns the conversion status of core0 for conversion

  @Description
    This routine is used to return the conversion status of core0 selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Core Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsCore0ConversionComplete(void)
{   
    return ADSTATLbits.AN0RDY;
}

/**
  @Summary
    Allows conversion clock prescaler value to be set

  @Description
    This routine is used to allow conversion clock prescaler value to be set manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required prescaler integer value
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static void ADC1_Core0ConversionClockPrescalerSet(uint8_t prescaler)
{
    ADCORE0Hbits.ADCS = prescaler;
}
/**
  @Summary
    Enables power for Core 1 

  @Description
    This routine is used to set the analog and digital power for ADC1 Core 1.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core1PowerEnable(void);
/**
  @Summary
    Calibrates dedicated Core 1 

  @Description
    This routine is used to calibrate the ADC1 Core 1.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core1Calibration(void);
/**

  @Summary
    Sets Core 0 channel

  @Description
    This routine is used to set the ADC1 Core 1 channel manually.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

inline static void ADC1_Core1ChannelSelect(ADC1_CORE1_CHANNEL channel)
{
   ADCON4Hbits.C1CHS = channel;
}
/**
  @Summary
    Returns the ADC1 conversion value for Core 1.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The core required must be enabled and calibrated before calling this routine 
    using ADC1_Core1PowerEnable() and ADC1_Core1Calibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsCore1ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */

inline static uint16_t ADC1_Core1ConversionResultGet(void) 
{
    return ADCBUF1;
}
/**
  @Summary
    Allows selection of a resolution mode for conversion

  @Description
    This routine is used to select desired resolution mode for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required resolution mode from the ADC1_RESOLUTION_TYPE list
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/

inline static void ADC1_Core1ResolutionModeSet( ADC1_RESOLUTION_TYPE resolution )
{
    ADCORE1Hbits.RES = resolution;
}
/**
  @Summary
    Returns the conversion status of core1 for conversion

  @Description
    This routine is used to return the conversion status of core1 selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Core Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsCore1ConversionComplete(void)
{   
    return ADSTATLbits.AN1RDY;
}

/**
  @Summary
    Allows conversion clock prescaler value to be set

  @Description
    This routine is used to allow conversion clock prescaler value to be set manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required prescaler integer value
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static void ADC1_Core1ConversionClockPrescalerSet(uint8_t prescaler)
{
    ADCORE1Hbits.ADCS = prescaler;
}
/**
  @Summary
    Enables power for Core 2 

  @Description
    This routine is used to set the analog and digital power for ADC1 Core 2.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core2PowerEnable(void);
/**
  @Summary
    Calibrates dedicated Core 2 

  @Description
    This routine is used to calibrate the ADC1 Core 2.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core2Calibration(void);
/**

  @Summary
    Sets Core 0 channel

  @Description
    This routine is used to set the ADC1 Core 2 channel manually.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

inline static void ADC1_Core2ChannelSelect(ADC1_CORE2_CHANNEL channel)
{
   ADCON4Hbits.C2CHS = channel;
}
/**
  @Summary
    Returns the ADC1 conversion value for Core 2.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The core required must be enabled and calibrated before calling this routine 
    using ADC1_Core2PowerEnable() and ADC1_Core2Calibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsCore2ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */

inline static uint16_t ADC1_Core2ConversionResultGet(void) 
{
    return ADCBUF2;
}
/**
  @Summary
    Allows selection of a resolution mode for conversion

  @Description
    This routine is used to select desired resolution mode for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required resolution mode from the ADC1_RESOLUTION_TYPE list
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/

inline static void ADC1_Core2ResolutionModeSet( ADC1_RESOLUTION_TYPE resolution )
{
    ADCORE2Hbits.RES = resolution;
}
/**
  @Summary
    Returns the conversion status of core2 for conversion

  @Description
    This routine is used to return the conversion status of core2 selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Core Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsCore2ConversionComplete(void)
{   
    return ADSTATLbits.AN2RDY;
}

/**
  @Summary
    Allows conversion clock prescaler value to be set

  @Description
    This routine is used to allow conversion clock prescaler value to be set manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required prescaler integer value
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static void ADC1_Core2ConversionClockPrescalerSet(uint8_t prescaler)
{
    ADCORE2Hbits.ADCS = prescaler;
}
/**
  @Summary
    Enables power for Core 3 

  @Description
    This routine is used to set the analog and digital power for ADC1 Core 3.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core3PowerEnable(void);
/**
  @Summary
    Calibrates dedicated Core 3 

  @Description
    This routine is used to calibrate the ADC1 Core 3.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

void ADC1_Core3Calibration(void);
/**

  @Summary
    Sets Core 0 channel

  @Description
    This routine is used to set the ADC1 Core 3 channel manually.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example

*/

inline static void ADC1_Core3ChannelSelect(ADC1_CORE3_CHANNEL channel)
{
   ADCON4Hbits.C3CHS = channel;
}
/**
  @Summary
    Returns the ADC1 conversion value for Core 3.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.
 
  @Preconditions
    The core required must be enabled and calibrated before calling this routine 
    using ADC1_Core3PowerEnable() and ADC1_Core3Calibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsCore3ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */

inline static uint16_t ADC1_Core3ConversionResultGet(void) 
{
    return ADCBUF3;
}
/**
  @Summary
    Allows selection of a resolution mode for conversion

  @Description
    This routine is used to select desired resolution mode for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required resolution mode from the ADC1_RESOLUTION_TYPE list
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/

inline static void ADC1_Core3ResolutionModeSet( ADC1_RESOLUTION_TYPE resolution )
{
    ADCORE3Hbits.RES = resolution;
}
/**
  @Summary
    Returns the conversion status of core3 for conversion

  @Description
    This routine is used to return the conversion status of core3 selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Core Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsCore3ConversionComplete(void)
{   
    return ADSTATLbits.AN3RDY;
}

/**
  @Summary
    Allows conversion clock prescaler value to be set

  @Description
    This routine is used to allow conversion clock prescaler value to be set manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required prescaler integer value
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static void ADC1_Core3ConversionClockPrescalerSet(uint8_t prescaler)
{
    ADCORE3Hbits.ADCS = prescaler;
}

/**
  Section: Interface Routines: Shared Core
*/
/**
  @Summary
    Enables power for ADC1 shared Core

  @Description
    This routine is used to set the analog and digital power for ADC1 shared Core.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example
*/
void ADC1_SharedCorePowerEnable(void);
/**
  @Summary
    Calibrates the ADC1 shared Core  

  @Description
    This routine is used to calibrate the ADC1 shared core.
 
  @Preconditions
    None.

  @Param
    None

  @Returns
    None.

  @Example
    Refer to ADC1_Initialize() for an example
*/
void ADC1_SharedCoreCalibration(void);
/**
  @Summary
    Allows selection of a data format type for conversion

  @Description
    This routine is used to select desired data format for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required data format type from the ADC1_FORM_TYPE list
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_FormatDataSet( ADC1_FORM_TYPE form )
{
    ADCON1Hbits.FORM = form;
}
/**
  @Summary
    Allows selection of a resolution mode for conversion

  @Description
    This routine is used to select desired resolution mode for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required resolution mode from the ADC1_RESOLUTION_TYPE list
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_SharedCoreResolutionModeSet( ADC1_RESOLUTION_TYPE resolution )
{
    ADCON1Hbits.SHRRES = resolution;
}
/**
  @Summary
    Allows conversion clock prescaler value to be set

  @Description
    This routine is used to allow conversion clock prescaler value to be set manually
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    Pass in required prescaler integer value
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/
inline static void ADC1_SharedCoreConversionClockPrescalerSet(uint8_t prescaler)
{
    ADCON2Lbits.SHRADCS = prescaler;
}
/**
  @Summary
    Returns the ADC1 conversion value for the shared core channel AN4

  @Description
    This routine is used to get the analog to digital converted value for channel AN4. This
    routine gets converted values from the shared core channel AN4.
 
  @Preconditions
    The shared core must be enabled and calibrated before calling this routine 
    using ADC1_SharedCorePowerEnable() and ADC1_SharedCoreCalibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsSharedChannelAN4ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */
inline static uint16_t ADC1_SharedChannelAN4ConversionResultGet(void) 
{
    return ADCBUF4;
}
/**
  @Summary
    Returns the conversion status of shared channel AN4 selected for conversion

  @Description
    This routine is used to return the conversion status of the shared channel AN4 
    selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Channel AN4 Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsSharedChannelAN4ConversionComplete(void)
{   
    return ADSTATLbits.AN4RDY;
}
/**
  Shared Channel ConversionResultGet and ConversionComplete APIs are only generated 
  for the AN channels selected in the MCC UI. To generate for a specific channel,
  please enable the Shared AN channel in the MCC UI.
*/
/**
  @Summary
    Returns the ADC1 conversion value for the shared core channel AN5

  @Description
    This routine is used to get the analog to digital converted value for channel AN5. This
    routine gets converted values from the shared core channel AN5.
 
  @Preconditions
    The shared core must be enabled and calibrated before calling this routine 
    using ADC1_SharedCorePowerEnable() and ADC1_SharedCoreCalibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsSharedChannelAN5ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */
inline static uint16_t ADC1_SharedChannelAN5ConversionResultGet(void) 
{
    return ADCBUF5;
}
/**
  @Summary
    Returns the conversion status of shared channel AN5 selected for conversion

  @Description
    This routine is used to return the conversion status of the shared channel AN5 
    selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Channel AN5 Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsSharedChannelAN5ConversionComplete(void)
{   
    return ADSTATLbits.AN5RDY;
}
/**
  Shared Channel ConversionResultGet and ConversionComplete APIs are only generated 
  for the AN channels selected in the MCC UI. To generate for a specific channel,
  please enable the Shared AN channel in the MCC UI.
*/
/**
  @Summary
    Returns the ADC1 conversion value for the shared core channel AN12

  @Description
    This routine is used to get the analog to digital converted value for channel AN12. This
    routine gets converted values from the shared core channel AN12.
 
  @Preconditions
    The shared core must be enabled and calibrated before calling this routine 
    using ADC1_SharedCorePowerEnable() and ADC1_SharedCoreCalibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsSharedChannelAN12ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */
inline static uint16_t ADC1_SharedChannelAN12ConversionResultGet(void) 
{
    return ADCBUF12;
}
/**
  @Summary
    Returns the conversion status of shared channel AN12 selected for conversion

  @Description
    This routine is used to return the conversion status of the shared channel AN12 
    selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Channel AN12 Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsSharedChannelAN12ConversionComplete(void)
{   
    return ADSTATLbits.AN12RDY;
}
/**
  Shared Channel ConversionResultGet and ConversionComplete APIs are only generated 
  for the AN channels selected in the MCC UI. To generate for a specific channel,
  please enable the Shared AN channel in the MCC UI.
*/
/**
  @Summary
    Returns the ADC1 conversion value for the shared core channel AN14

  @Description
    This routine is used to get the analog to digital converted value for channel AN14. This
    routine gets converted values from the shared core channel AN14.
 
  @Preconditions
    The shared core must be enabled and calibrated before calling this routine 
    using ADC1_SharedCorePowerEnable() and ADC1_SharedCoreCalibration() 
    respectively. This routine returns the conversion value only after the 
    conversion is complete. Completion status conversion can be checked using 
    ADC1_IsSharedChannelAN14ConversionComplete() routine.
   
  @Returns
    Returns the buffer containing the conversion value.

  @Param
    Buffer address
  
  @Example
    Refer to ADC1_Initialize(); for an example
 */
inline static uint16_t ADC1_SharedChannelAN14ConversionResultGet(void) 
{
    return ADCBUF14;
}
/**
  @Summary
    Returns the conversion status of shared channel AN14 selected for conversion

  @Description
    This routine is used to return the conversion status of the shared channel AN14 
    selected for conversion.
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    The value of the Channel AN14 Conversion register

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/

inline static bool ADC1_IsSharedChannelAN14ConversionComplete(void)
{   
    return ADSTATLbits.AN14RDY;
}
/**
  Shared Channel ConversionResultGet and ConversionComplete APIs are only generated 
  for the AN channels selected in the MCC UI. To generate for a specific channel,
  please enable the Shared AN channel in the MCC UI.
*/
/**
  Section: Interface Routines: Digital Comparator
*/
/**
  @Summary
    Allows setting of a the enable bit for the digital comparator 0

  @Description
    This routine is used to enable the digital comparator 0
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator0Enable(void)
{
    ADCMP0CONbits.CMPEN = 1;
}
/**
  @Summary
    Allows setting of a the disable bit for the digital comparator 0

  @Description
    This routine is used to disable the digital comparator 0
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator0Disable(void)
{
    ADCMP0CONbits.CMPEN = 0;		
}
/**
  @Summary
    Allows setting of a the low threshold for the digital comparator 0

  @Description
    This routine is used to set the desired low threshold for the digital comparator 0
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    threshold value required
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator0LowThresholdSet(uint16_t threshold )
{
    ADCMP0LO = threshold;	
}
/**
  @Summary
    Allows setting of a the high threshold for the digital comparator 0

  @Description
    This routine is used to set the desired high threshold for the digital comparator 0
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    threshold value required
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator0HighThresholdSet(uint16_t threshold )
{
    ADCMP0HI = threshold;		
}
/**
  @Summary
    Returns the Comparator 0 status bit

  @Description
    This routine is used to get the status bit for the digital comparator 0
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static uint16_t ADC1_Comparator0EventStatusGet(void)
{
    return ADCMP0CONbits.STAT;    	
}
/**
  @Summary
    Returns the channel that generated Comparator 0 event 

  @Description
    This routine is used to get the ADC1 channel that generated the 
    event for the digital comparator 0
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/
inline static uint16_t ADC1_ComparatorEvent0ChannelGet(void)
{
    return ADCMP0CONbits.CHNL;    		
} 
/**
  @Summary
    Allows setting of a the enable bit for the digital comparator 1

  @Description
    This routine is used to enable the digital comparator 1
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator1Enable(void)
{
    ADCMP1CONbits.CMPEN = 1;
}
/**
  @Summary
    Allows setting of a the disable bit for the digital comparator 1

  @Description
    This routine is used to disable the digital comparator 1
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator1Disable(void)
{
    ADCMP1CONbits.CMPEN = 0;		
}
/**
  @Summary
    Allows setting of a the low threshold for the digital comparator 1

  @Description
    This routine is used to set the desired low threshold for the digital comparator 1
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    threshold value required
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator1LowThresholdSet(uint16_t threshold )
{
    ADCMP1LO = threshold;	
}
/**
  @Summary
    Allows setting of a the high threshold for the digital comparator 1

  @Description
    This routine is used to set the desired high threshold for the digital comparator 1
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    threshold value required
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static void ADC1_Comparator1HighThresholdSet(uint16_t threshold )
{
    ADCMP1HI = threshold;		
}
/**
  @Summary
    Returns the Comparator 1 status bit

  @Description
    This routine is used to get the status bit for the digital comparator 1
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
*/
inline static uint16_t ADC1_Comparator1EventStatusGet(void)
{
    return ADCMP1CONbits.STAT;    	
}
/**
  @Summary
    Returns the channel that generated Comparator 1 event 

  @Description
    This routine is used to get the ADC1 channel that generated the 
    event for the digital comparator 1
  
  @Preconditions
    ADC1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to ADC1_Initialize(); for an example
 
*/
inline static uint16_t ADC1_ComparatorEvent1ChannelGet(void)
{
    return ADCMP1CONbits.CHNL;    		
} 
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_ADC1_H
    
/**
 End of File
*/
