/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
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
    Section: Includes
*/
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //    SPFI: SPI1 error
    //    Priority: 3
        IPC2bits.SPI1EIP = 3;
    //    SPII: SPI1 transfer done
    //    Priority: 3
        IPC2bits.SPI1IP = 3;
    //    UERI: UART2 Error
    //    Priority: 1
        IPC16bits.U2EIP = 1;
    //    UTXI: UART2 Transmitter
    //    Priority: 1
        IPC7bits.U2TXIP = 1;
    //    URXI: UART2 Receiver
    //    Priority: 1
        IPC7bits.U2RXIP = 1;
    //    CNI: Change Notification Interrupt
    //    Priority: 1
        IPC4bits.CNIP = 1;
    //    UERI: UART1 Error
    //    Priority: 5
        IPC16bits.U1EIP = 5;
    //    UTXI: UART1 Transmitter
    //    Priority: 5
        IPC3bits.U1TXIP = 5;
    //    URXI: UART1 Receiver
    //    Priority: 5
        IPC2bits.U1RXIP = 5;
    //    ADCAN12: ADC AN12 Convert Done
    //    Priority: 7
        IPC38bits.ADCAN12IP = 7;
    //    ADCAN0: ADC AN0 Convert Done
    //    Priority: 7
        IPC27bits.ADCAN0IP = 7;
    //    ADCAN1: ADC AN1 Convert Done
    //    Priority: 7
        IPC27bits.ADCAN1IP = 7;
    //    ADCAN2: ADC AN2 Convert Done
    //    Priority: 7
        IPC28bits.ADCAN2IP = 7;
    //    ADCAN3: ADC AN3 Convert Done
    //    Priority: 7
        IPC28bits.ADCAN3IP = 7;
    //    ADCI: ADC1 Convert Done
    //    Priority: 7
        IPC3bits.ADCIP = 7;
    //    ADCAN14: ADC AN14 Convert Done
    //    Priority: 7
        IPC39bits.ADCAN14IP = 7;
    //    ACI: Analog Comparator 3 Interrupt
    //    Priority: 1
        IPC26bits.AC3IP = 1;
    //    ACI: Analog Comparator 2 Interrupt
    //    Priority: 1
        IPC25bits.AC2IP = 1;
    //    ACI: Analog Comparator 1 Interrupt
    //    Priority: 1
        IPC4bits.AC1IP = 1;
    //    TI: Timer 3
    //    Priority: 4
        IPC2bits.T3IP = 4;
}

