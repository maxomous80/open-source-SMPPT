
//FOSC/2=FCY utile alla funzione delay
#define FCY  42377500UL  

#include "xc.h"
#include "serialComunication.h"
#include "mcc_generated_Files/pin_manager.h"
#include <libpic30.h>
#include <stdbool.h>


#define attesa 1

// settaggio dei pin per migliorare la lettura del codice
#define V_in   _LATA3
#define I_in   _LATA4 
#define V_out  _LATB14 
#define I_out_1 _LATB13
#define I_out_2 _LATC3


void outputMeas(uint16_t dato1, uint16_t dato2, uint16_t dato3, uint16_t dato4, uint16_t dato5) {

    // Set pin di START per segnalare l'inizio della trasmissione
    FPGA_SERIAL_IN_START_SetHigh();

    int i = 0;
    for (i = 15; i >= 0; i--) {
        
        // clear clock con temporizzazione
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetLow();

        //set dei pin di uscita bit a bit per ogni dato intero, estrapolando ogni bit tramite la funzione  &(1 << (i))) != 0
        V_in = (((unsigned int) (dato1)) & (1 << (i))) != 0;
        I_in = (((unsigned int) (dato2)) & (1 << (i))) != 0;
        V_out = (((unsigned int) (dato3)) & (1 << (i))) != 0;
        I_out_1 = (((unsigned int) (dato4)) & (1 << (i))) != 0;
        I_out_2 = (((unsigned int) (dato5)) & (1 << (i))) != 0;

        //set clock con temporizzazione, utilizzando il clock come segnale data-ready, applico una temporizzazione per assicurare la validità del dato sulla salita del clock
        __delay_us(attesa);
        FPGA_SERIAL_IN_CLK_SetHigh();

    }


    //Routine di chiusura trasmissione
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetLow();
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetHigh();
    __delay_us(attesa);
    FPGA_SERIAL_IN_START_SetLow();
    __delay_us(attesa);
    FPGA_SERIAL_IN_CLK_SetLow();

    //clear dei pin di uscita utilizzati
    V_in = 0;
    I_in = 0;
    V_out = 0;
    I_out_1 = 0;
    I_out_2 = 0;
}