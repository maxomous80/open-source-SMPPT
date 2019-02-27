/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
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

// Configuration bits: selected in the GUI

// FSEC
#pragma config BWRP = OFF    // Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED    // Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF    // Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF    // General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED    // General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF    // Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED    // Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF    // Alternate Interrupt Vector Table bit->Disabled AIVT

// FBSLIM
#pragma config BSLIM = 8191    // Boot Segment Flash Page Address Limit bits->

// FOSCSEL
#pragma config FNOSC = FRC    // Oscillator Source Selection->FRC
#pragma config IESO = ON    // Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FOSC
#pragma config POSCMD = NONE    // Primary Oscillator Mode Select bits->Primary Oscillator disabled
#pragma config OSCIOFNC = ON    // OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    // Peripheral pin select configuration bit->Allow only one reconfiguration
#pragma config FCKSM = CSECMD    // Clock Switching Mode bits->Clock switching is enabled,Fail-safe Clock Monitor is disabled
#pragma config PLLKEN = ON    // PLL Lock Enable Bit->Clock switch to PLL source will wait until the PLL lock signal is valid

// FWDT
#pragma config WDTPOST = PS32768    // Watchdog Timer Postscaler bits->1:32768
#pragma config WDTPRE = PR128    // Watchdog Timer Prescaler bit->1:128
#pragma config WDTEN = OFF    // Watchdog Timer Enable bits->WDT and SWDTEN disabled
#pragma config WINDIS = OFF    // Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode
#pragma config WDTWIN = WIN25    // Watchdog Timer Window Select bits->WDT Window is 25% of WDT period

// FICD
#pragma config ICS = PGD2    // ICD Communication Channel Select bits->Communicate on PGEC2 and PGED2
#pragma config JTAGEN = OFF    // JTAG Enable bit->JTAG is disabled
#pragma config BTSWP = OFF    // BOOTSWP Instruction Enable/Disable bit->BOOTSWP instruction is disabled

// FDEVOPT
#pragma config PWMLOCK = ON    // PWMx Lock Enable bit->Certain PWM registers may only be written after key sequency
#pragma config ALTI2C1 = OFF    // Alternate I2C1 Pin bit->I2C1 mapped to SDA1/SCL1 pins
#pragma config ALTI2C2 = OFF    // Alternate I2C2 Pin bit->I2C2 mapped to SDA2/SCL2 pins
#pragma config DBCC = OFF    // DACx Output Cross Connection bit->No Cross Connection between DAC outputs

// FALTREG
#pragma config CTXT1 = OFF    // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits->Not Assigned
#pragma config CTXT2 = OFF    // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits->Not Assigned

// FBTSEQ
#pragma config BSEQ = 4095    // Relative value defining which partition will be active after device Reset; the partition containing a lower boot number will be active->
#pragma config IBSEQ = 0    // The one's complement of BSEQ; must be calculated by the user and written during device programming.->

// FBOOT
#pragma config BTMODE = SINGLE    // Boot Mode Configuration Bits->Device is in Single Boot (legacy) mode

#include "mcc.h"

/**
 Section: Local Variables
*/

/**
 Section: Function prototypes
*/
bool SYSTEM_ResetCauseFromSoftware(uint16_t resetCause);
bool SYSTEM_ResetCauseFromWatchdogTimer(uint16_t resetCause);
bool SYSTEM_ResetCauseFromConfigurationMismatch(uint16_t resetCause);
bool SYSTEM_ResetCauseFromIllegalOpcode(uint16_t resetCause);
bool SYSTEM_ResetCauseFromExternal(uint16_t resetCause);
bool SYSTEM_ResetCauseFromTrap(uint16_t resetCause);
void SYSTEM_ResetCauseClear(RESET_MASKS resetFlagMask);

/**
* a private place to store the error code if we run into a severe error
*/

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    INTERRUPT_Initialize();
    SPI1_Initialize();
    UART1_Initialize();
    TMR2_Initialize();
    UART2_Initialize();
    ADC1_Initialize();
    TMR3_Initialize();
    PGA1_Initialize();
    CMP2_Initialize();
    CMP1_Initialize();
    CMP3_Initialize();
    INTERRUPT_GlobalEnable();
    CORCON_ModeOperatingSet(CORCON_MODE_PORVALUES);
}

void OSCILLATOR_Initialize(void)
{
    // FRCDIV FRC/1; PLLPRE 2; DOZE 1:8; PLLPOST 1:4; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3040;
    // TUN Center frequency; 
    OSCTUN = 0x0;
    // ROON disabled; ROSEL disabled; RODIV Base clock value; ROSSLP disabled; 
    REFOCON = 0x0;
    // PLLDIV 90; 
    PLLFBD = 0x5A;
    // ENAPLL disabled; APSTSCLR 1:1; FRCSEL ASRCSEL determines input clock source; SELACLK Auxiliary Oscillators; ASRCSEL No clock input; 
    ACLKCON = 0x2700;
    // LFSR 0; 
    LFSR = 0x0;
    // CF no clock failure; NOSC FRCPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) ((0x100 >> _OSCCON_NOSC_POSITION) & 0x00FF));
    __builtin_write_OSCCONL((uint8_t) ((0x100 | _OSCCON_OSWEN_MASK) & 0xFF));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
}

uint16_t SYSTEM_GetResetCause(void)
{
    return RCON;
}

void __attribute__ ((weak)) SYSTEM_ResetCauseHandler(void)
{
    uint16_t resetCause = SYSTEM_GetResetCause();
    if(SYSTEM_ResetCauseFromTrap(resetCause))
    { 
      SYSTEM_ResetCauseClear(RESET_MASK_TRAPR); 
      //Do something 
    }
    if(SYSTEM_ResetCauseFromIllegalOpcode(resetCause))
    { 
      SYSTEM_ResetCauseClear(RESET_MASK_IOPUWR); 
      //Do something 
    }
    if(SYSTEM_ResetCauseFromConfigurationMismatch(resetCause))
    { 
      SYSTEM_ResetCauseClear(RESET_MASK_CM); 
      //Do something 
    }
    if(SYSTEM_ResetCauseFromExternal(resetCause))
    { 
      SYSTEM_ResetCauseClear(RESET_MASK_EXTR); 
      //Do something 
    }
    if(SYSTEM_ResetCauseFromSoftware(resetCause))
    { 
      SYSTEM_ResetCauseClear(RESET_MASK_SWR); 
      //Do something 
    }
    if(SYSTEM_ResetCauseFromWatchdogTimer(resetCause))
    { 
      SYSTEM_ResetCauseClear(RESET_MASK_WDTO); 
      //Do something 
    }
}

bool SYSTEM_ResetCauseFromTrap(uint16_t resetCause)
{
    bool resetStatus = false;
    if(resetCause & RESET_MASK_TRAPR)
    { 
      resetStatus = true; 
    }
    return resetStatus;
}

bool SYSTEM_ResetCauseFromIllegalOpcode(uint16_t resetCause)
{
    bool resetStatus = false;
    if(resetCause & RESET_MASK_IOPUWR)
    { 
      resetStatus = true; 
    }
    return resetStatus;
}

bool SYSTEM_ResetCauseFromConfigurationMismatch(uint16_t resetCause)
{
    bool resetStatus = false;
    if(resetCause & RESET_MASK_CM)
    { 
      resetStatus = true; 
    }
    return resetStatus;
}

bool SYSTEM_ResetCauseFromExternal(uint16_t resetCause)
{
    bool resetStatus = false;
    if(resetCause & RESET_MASK_EXTR)
    { 
      resetStatus = true; 
    }
    return resetStatus;
}

bool SYSTEM_ResetCauseFromSoftware(uint16_t resetCause)
{
    bool resetStatus = false;
    if(resetCause & RESET_MASK_SWR)
    { 
      resetStatus = true; 
    }
    return resetStatus;
}

bool SYSTEM_ResetCauseFromWatchdogTimer(uint16_t resetCause)
{
    bool resetStatus = false;
    if(resetCause & RESET_MASK_WDTO)
    { 
      resetStatus = true;
    }
    return resetStatus;
}

void SYSTEM_ResetCauseClear(RESET_MASKS resetFlagMask)
{ 
     RCON = RCON & (~resetFlagMask); 
} 

void SYSTEM_ResetCauseClearAll()
{ 
    RCON = 0x00; 
}
/**
 End of File
*/