
//FOSC/2=FCY utile alla funzione delay
#define FCY  42377500UL  

#include "xc.h"
#include "serialParam.h"
#include "mcc_generated_Files/pin_manager.h"
#include "mcc_generated_files/interrupt_manager.h"
#include <libpic30.h>
#include <stdbool.h>

#define attesa 1

// settaggio del pin PARAM per migliorare la lettura del codice
#define PARAM   _LATB8


void outputParam(uint16_t dutyM1, uint16_t dutyM3, uint16_t deadTime, uint16_t freq, bool forceDuty, bool select_bootStrap) {

    //disabilita interrupt ADC
    IFS0bits.ADCIF = 0; // Clearing ADC1 interrupt.
    IEC0bits.ADCIE = 0; // Diabling ADC1 interrupt.
    INTERRUPT_GlobalDisable();
    
    // Set pin di START per segnalare l'inizio della trasmissione
    FPGA_SERIAL_IN_START_PARAM_SetHigh();

    //routine di invio duty M1
    int i = 0;
    for (i = 11; i >= 0; i--) {

        // clear clock con temporizzazione
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetLow();

        //set dei pin di uscita bit a bit per ogni dato intero, estrapolando ogni bit tramite la funzione  &(1 << (i))) != 0
        PARAM = ((dutyM1) & (1 << (i))) != 0;

        //set clock con temporizzazione, utilizzando il clock come segnale data-ready, applico una temporizzazione per assicurare la validità del dato sulla salita del clock
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetHigh();
    }

    //routine di invio duty M3
    i = 0;
    for (i = 11; i >= 0; i--) {

        // clear clock con temporizzazione
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetLow();

        //set dei pin di uscita bit a bit per ogni dato intero, estrapolando ogni bit tramite la funzione  &(1 << (i))) != 0
        PARAM = ((dutyM3) & (1 << (i))) != 0;

        //set clock con temporizzazione, utilizzando il clock come segnale data-ready, applico una temporizzazione per assicurare la validità del dato sulla salita del clock
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetHigh();
    }

    //routine di invio frequenza pwm
    i = 0;
    for (i = 2; i >= 0; i--) {

        // clear clock con temporizzazione
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetLow();

        //set dei pin di uscita bit a bit per ogni dato intero, estrapolando ogni bit tramite la funzione  &(1 << (i))) != 0
        PARAM = ((freq) & (1 << (i))) != 0;

        //set clock con temporizzazione, utilizzando il clock come segnale data-ready, applico una temporizzazione per assicurare la validità del dato sulla salita del clock
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetHigh();
    }

    //routine di invio frequenza pwm
    i = 0;
    for (i = 3; i >= 0; i--) {

        // clear clock con temporizzazione
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetLow();

        //set dei pin di uscita bit a bit per ogni dato intero, estrapolando ogni bit tramite la funzione  &(1 << (i))) != 0
        PARAM = ((deadTime) & (1 << (i))) != 0;

        //set clock con temporizzazione, utilizzando il clock come segnale data-ready, applico una temporizzazione per assicurare la validità del dato sulla salita del clock
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetHigh();
    }

    //routine di invio forzamento duty

    // clear clock con temporizzazione
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetLow();

    // set penulultimo pin del dato riferito al forzamento del duty
    PARAM = forceDuty;

    //set clock con temporizzazione
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetHigh();
    
    //routine di abilitazione bootStrap

    // clear clock con temporizzazione
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetLow();

    // set ultimo bit del dato riferito all'abilitazione del bootStrap
    PARAM = select_bootStrap;

    //set clock con temporizzazione
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetHigh();

    //routine di chiusura
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetLow();
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetHigh();
    __delay_us(attesa);
    FPGA_SERIAL_IN_START_PARAM_SetLow();
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetLow();

    //clear dei pin di uscita utilizzati
    PARAM = 0;

    //abilita interrupt ADC
    IFS0bits.ADCIF = 0; // Clearing ADC1 interrupt.
    IEC0bits.ADCIE = 1; // Enabling ADC1 interrupt.
    
    INTERRUPT_GlobalEnable();
}