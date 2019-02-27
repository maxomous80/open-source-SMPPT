/**
 * SMPPT controller
 */

#include "mcc_generated_files/mcc.h"
#include <xc.h>


#define FCY  42377500UL  

#include <stdio.h>
#include <libpic30.h>
#include <string.h>
#include <math.h>

#include "serialComunication.h"
#include "serialParam.h"

//-----------------------------------------------------------------------------

//numero di medie da effettuare
#define MEDIE 256LU        //x 14us ad acquisizione + 0.23ms circa --> 3.7ms circa con 256 medie
#define DELAY_MPTT  20LU   //circa 370ms @100 x256 sample x14us interrupt adc
                           //circa 75ms @20 x256 sample x14us interrupt adc

#define TOLN 0.005
#define MPPT_PO_VAR_COEFF tbd

#define AUMENTO_VREF 100 //0.01V unit
#define AUMENTO_DUTY 20
#define AUMENTO_DUTY_MIN 10
#define AUMENTO_DUTY_MAX 1000

#define VREF_MIN 1500 //0.01V unit
#define VREF_MAX 7000 //0.01V unit

#define VREF_INIZIALE 4500

#define UART1_NUM_CHAR_RCV    (8 - UART1_ReceiveBufferSizeGet())    //UART1_CONFIG_RX_BYTEQ_LENGTH=8
#define UART2_NUM_CHAR_RCV    (64 - UART2_ReceiveBufferSizeGet())    //UART2_CONFIG_RX_BYTEQ_LENGTH=64

//12 bit - Vrefadc=3.33V - partitore (R1+R2)/R2 = 23
#define VOLT_CONV   1.88671875f //3.36 * ADC / 4096 * 23 * 100
//12 bit - Vrefadc=3.33V - shunt = 0.015 - gain = 200
#define CURR_CONV   2.734375f //3.36 * ADC / 4096 / (200*0.0015) * 1000

//-----------------------------------------------------------------------------

void debug_menu();
void get_temperatures();

void sendToWifi();
void getWiFiData();

inline void do_mppt(int *duty);
inline void mppt_po(int *duty);
inline void mppt_po_var(int *duty);
inline void mppt_po_3pt(int *duty);
inline void mppt_inc(int *duty);

uint8_t tipo_MPPT = 0; //0=P&O, 1=INC, 2=P&O variabile, 3=P&O 3-punti

//contatore somme per effettuare medie
uint16_t count = 0;

//variabili di supporto necessarie al calcolo delle medie
uint32_t Vin_m = 0;
uint32_t Iin1_m = 0;
uint32_t Iout1_m = 0;
uint32_t Iin2_m = 0;
uint32_t Iout2_m = 0;
uint32_t Vout_m = 0;

// valori mediati
uint16_t Vin = 0;
uint16_t Iin = 0;
uint16_t Iin1 = 0;
uint16_t Iout1 = 0;
uint16_t Iout = 0;
uint16_t Iin2 = 0;
uint16_t Iout2 = 0;
uint16_t Vout = 0;

uint16_t Vin_prec = 0;
uint16_t Iin_prec = 0;
uint16_t Iin1_prec = 0;
uint16_t Iout1_prec = 0;
uint16_t Iin2_prec = 0;
uint16_t Iout2_prec = 0;
uint16_t Vout_prec = 0;

float dv, di, dp, Pin, Pout, Pin_prec;
float dve, die, dg, g, dge, dgg;

uint16_t Vin_prec_mppt = 0;
uint16_t Iin_prec_mppt = 0;

uint16_t vref = VREF_INIZIALE;
// componenti della stringa parameter inviata dal microcontrollore all'FPGA
int dutyM1 = 0;
int dutyM3 = 2048;
int deadTime = 0;
int freq = 0;
bool forceDuty = false;
bool select_bootStrap = true;
bool mppt_enabled = true;
bool state_DCDC = true;//true buck, false boost

// Variabili di supporto per il funzinamento della routine di DEBUG e perr la trasmissione UART
#define DBG_RX_BUF_SIZE 10
char push[DBG_RX_BUF_SIZE] = "0"; // variabile nella quale viene salvato il valore digitato dall'utente da interfaccia seriale UART
int8_t select = -1; // variabile necessaria alla realizzazione del "menu" dell'interfaccia seriale

// Variabili utili per l'invio di dati tramite SPI da FPGA a uControllore
uint16_t dato_spi = 0;
uint16_t duty_M3_feed = 0;
uint16_t duty_M1_feed = 0;
uint16_t freq_feed = 0;
uint16_t dt_feed = 0;
bool A0 = 0;
bool A1 = 0;
bool MODE_BOOST = 0;
bool MODE_BUCK = 0;
bool MODE_BYPASS = 0;

uint16_t num_cicli = 0;

bool FPGA_started = false;

uint16_t array_freq_values[8] = {100,80,120,150,175,200,225,250}; //kHz
uint16_t array_dt_values[16] = {104,21,41,62,83,104,125,145,166,187,208,229,250,271,291,312}; //ns


int16_t temp_board1 = 0;
int16_t temp_board2 = 0;

//-----------------------------------------------------------------------------

/**
 * controlla stato switch ENABLE_MCU
 */
inline void check_enable() {
    if (ENABLE_MCU_GetValue()) {
        printf("ENABLE_MCU ON\r\n\r\n");
        RESET_FPGA_SetHigh();
        ENABLE_FPGA_SetHigh();
    } else {
        printf("ENABLE_MCU OFF\r\n\r\n");
        RESET_FPGA_SetLow();
        ENABLE_FPGA_SetLow();

    }
}

//-----------------------------------------------------------------------------

int main(void) {
    if(state_DCDC){
        dutyM1=2048;
        dutyM3=0;
    }
    else{
        dutyM1=0;
        dutyM3=2048;
    }
    // initialize the device
    SYSTEM_Initialize();

    printf("\r\n-------------\r\n    START\r\n-------------\r\n\r\n");

    // Disable the Global Interrupts per permettere li invio dei parametri per inizializzare il sistema
    INTERRUPT_GlobalDisable();

    //gestione reset ed enablee FPGA
    check_enable();
    
    //partenza da bypass disabilitata
    FORCE_BYPASS_SetLow();
    
    forceDuty=true; //disabilitato DCDC FPGA
    // invio inizializzazione parametri
    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
    
    // Enable Interrupt Spi
    IEC0bits.SPI1IE = 1;
    //Clear Flag Interrupt
    IFS0bits.SPI1IF = 0;
    // Enable all interrupt
    INTERRUPT_GlobalEnable();
    
    printf("\r\ncheck FPGA... ");
    while(!FPGA_started); //attendi avvio e ricezione primo dato da FPGA
    printf("OK \r\n\r\n");
    
    while (1) {
        //Idle();
        get_temperatures();
        debug_menu();
        getWiFiData();
        sendToWifi();
        __delay_ms(25); //imposta ritardo tra i cicli (25ms sono circa 1secondo nella pratica per via degli interrupt continui)
    }
}

inline void ADC1_CallBack() {
    WIFI_RTS_SetHigh();

    //wait for conversion complete (last conversion is AN14)
    //while (!ADC1_IsSharedChannelAN14ConversionComplete()); // wait for ANALOG_I_OUT_2 conversion..

    Vin_m = Vin_m + ADC1_Core1ConversionResultGet();
    Iin1_m = Iin1_m + ADC1_Core2ConversionResultGet();
    Iin2_m = Iin2_m + ADC1_Core3ConversionResultGet();
    Vout_m = Vout_m + ADC1_Core0ConversionResultGet();
    Iout1_m = Iout1_m + ADC1_SharedChannelAN12ConversionResultGet();
    Iout2_m = Iout2_m + ADC1_SharedChannelAN14ConversionResultGet();

    count++;
    if (count>=MEDIE) {

        // Salvataggio ultima somma (medie)
        Vin = (uint16_t)((float)Vin_m * VOLT_CONV / count);
        Iin1 = (uint16_t)((float)Iin1_m * CURR_CONV / count);
        Iin2 = (uint16_t)((float)Iin2_m * CURR_CONV / count);
        Vout = (uint16_t)((float)Vout_m * VOLT_CONV / count);
        Iout1 = (uint16_t)((float)Iout1_m * CURR_CONV / count);
        Iout2 = (uint16_t)((float)Iout2_m * CURR_CONV / count);

        //media mobile a 2 campioni
        Vin = (Vin + Vin_prec) / 2;
        Iin1 = (Iin1 + Iin1_prec) / 2;
        Iin2 = (Iin2 + Iin2_prec) / 2;
        Vout = (Vout + Vout_prec) / 2;
        Iout1 = (Iout1 + Iout1_prec) / 2;
        Iout2 = (Iout2 + Iout2_prec) / 2;
        Vin_prec = Vin;
        Iin1_prec = Iin1;
        Iin2_prec = Iin2;
        Vout_prec = Vout;
        Iout1_prec = Iout1;
        Iout2_prec = Iout2;
        
        Iin = Iin1 + Iin2;
        Iout = Iout1 + Iout2;
        
        //azzeramento di tutte le variabili necessarie per effettuare le medie
        Vin_m = 0;
        Iin1_m = 0;
        Iout1_m = 0;
        Iin2_m = 0;
        Iout2_m = 0;
        Vout_m = 0;
        count = 0;
        
        num_cicli++;
        if (!MODE_BYPASS && mppt_enabled && num_cicli >= DELAY_MPTT) {
            num_cicli=0;
            
            Pin=(float)Vin*(float)Iin/100000.0;
            Pout=(float)Vout*(float)Iout/100000.0;
            
            if (forceDuty) {
				do_mppt(&dutyM1);
                outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
            } else {
                //algoritmo P&O (DC-DC su FPGA ON)
                if ((Pin>Pin_prec && Vin>Vin_prec_mppt)||(Pin<Pin_prec && Vin<Vin_prec_mppt))
                    vref=vref-AUMENTO_VREF;
                else vref=vref+AUMENTO_VREF;
                //controllo min-max
                if (vref<VREF_MIN) vref=VREF_MIN;
                else if (vref>VREF_MAX) vref=VREF_MAX;
            }
            
            Pin_prec=Pin; Vin_prec_mppt=Vin; Iin_prec_mppt=Iin;
        }
        
        //invio dati digitalizzati all'FPGA con vref
        outputMeas(Vin, vref, Vout, Iout1, Iout2);
        //invio dati digitalizzati all'FPGA per mppt
        //outputSerial(Vin, Iin, Vout, Iout1, Iout2);
    }
    
    WIFI_RTS_SetLow();
}

/**
 * Applica uno dei metodi MPPT, in base all valore della variabile "tipo_MPPT"
 */
inline void do_mppt() {
	int *duty;
	if (state_DCDC) {
		//buck mode
		duty = &dutyM1;
		dutyM3=0;
	} else {
		//boost mode
		duty = &dutyM3;
		dutyM1=4095;
	}
	
	if (tipo_MPPT==0) {
		//algoritmo P&O (DC-DC su FPGA OFF)
		mppt_po(duty);
	} else if (tipo_MPPT==1) {
		//algoritmo INC (DC-DC su FPGA OFF)
		mppt_inc(duty);
	} else if (tipo_MPPT==2) {
		//algoritmo P&O passo variabile (DC-DC su FPGA OFF)
		mppt_po_var(duty);
	} else if (tipo_MPPT==3) {
		//algoritmo P&O a tre punti (DC-DC su FPGA OFF)
		mppt_po_3pt(duty);
	} else {
		return;
	}
	
	//controllo min-max e transizione buck-boost
	if (state_DCDC) {
		//buck mode
		if (dutyM1<120){
			dutyM1=120;
		} else if (dutyM1>4000) {
			dutyM1=4095;
			dutyM3=120;
			state_DCDC=false; //switch to boost mode
		}
	} else {
		//boost mode
		if (dutyM3<120) {
			state_DCDC=true; //switch to buck mode
			dutyM3=0;
			dutyM1=4000;
		} else if (dutyM3>4000){
			dutyM3=4000;
			dutyM1=4095;
		}
	}
}

/**
 * Metodo MPPT P&O
 * @param duty
 */
inline void mppt_po(int *duty) {
	if ((Pin>Pin_prec && Vin>Vin_prec_mppt)||(Pin<Pin_prec && Vin<Vin_prec_mppt))
		*duty=*duty-AUMENTO_DUTY;
	else *duty=*duty+AUMENTO_DUTY;
}

/**
 * Metodo MPPT P&O a passo variabile
 * @param duty
 */
inline void mppt_po_var(int *duty) {
	dp=Pin-Pin_prec;
	dv=((float)Vin-(float)Vin_prec_mppt)/100.0;
	dg=fabs(dp/dv);
	
	int passo_duty = MPPT_PO_VAR_COEFF * dg;
	if (passo_duty<AUMENTO_DUTY_MIN) {
		passo_duty=AUMENTO_DUTY_MIN;
	} else if (passo_duty>AUMENTO_DUTY_MAX){
		passo_duty=AUMENTO_DUTY_MAX;
	}
	
	if ((Pin>Pin_prec && Vin>Vin_prec_mppt)||(Pin<Pin_prec && Vin<Vin_prec_mppt))
		*duty=*duty-passo_duty;
	else *duty=*duty+passo_duty;
}


/* Variabili di supporto per l'algoritmo MPPT P&O a tre punti */
uint8_t mppt_po_3pt_state = 0;
float Pa=0, Pb=0, Pc=0;
int dutyA=0, dutyB=0, dutyC=0;

/**
 * Metodo MPPT P&O a tre punti
 * @param duty
 */
inline void mppt_po_3pt(int *duty) {
	if (mppt_po_3pt_state==0) {
		mppt_po_3pt_state=1;
		Pa = Pin;
		dutyB = dutyA + AUMENTO_DUTY;
		*duty = dutyB;
	} else if (mppt_po_3pt_state==1) {
		mppt_po_3pt_state=2;
		Pb = Pin;
		dutyC = dutyA - AUMENTO_DUTY;
		*duty = dutyC;
	} else {
		mppt_po_3pt_state=0;
		Pc = Pin;
		if (Pb>=Pa && Pa>Pc) {
			dutyA = dutyB;
		} else if (Pb<Pa && Pa<=Pc) {
			dutyA = dutyC;
		}
		*duty = dutyA;
	}
}

/**
 * Metodo MPPT conduttanza incrementale
 * @param duty
 */
inline void mppt_inc(int *duty) {
	dv=((float)Vin-(float)Vin_prec_mppt)/100.0;
	di=((float)Iin-(float)Iin_prec_mppt)/1000.0;
	
	dg=di/dv;
	g=Iin/Vin;
	dgg=dg+g;
	
	dve=fabs(dv/Vmedia);
	die=fabs(di/Imedia);
	dge=fabs(dgg/g);
	
	if (dve<TOLN) {	//dv=0
		if (die<TOLN) {		//di=0
			//lascia duty invariat
		} else if (di>0) {	//di>0
			*duty=*duty-AUMENTO_DUTY;
		} else {			//di<0
			*duty=*duty+AUMENTO_DUTY;
		}
	} else {		//dv!=0
		if (dge<TOLN) {		//dg=-g
			//lascia duty invariato
		} else if (dgg>0) {	//dg>-g
			*duty=*duty-AUMENTO_DUTY;
		} else {			//dg<-g
			*duty=*duty+AUMENTO_DUTY;
		}
	}
}


//callback TMR3 1.2s (dopo aver effettuato una modific tramite MCC ricordarsi di commentare la seguente sezione duplicata in TMR3.c)

void TMR3_CallBack(void) {
}

void sendToWifi() {
    //send data to wifi module
    WIFI_IO1_SetHigh();
    
    UART2_Write('#');
    UART2_Write('S');
    UART2_Write('T');
    UART2_Write('=');
    UART2_Write((uint8_t)MODE_BOOST | ((uint8_t)MODE_BUCK << 1) | ((uint8_t)MODE_BYPASS << 2));
    UART2_Write((uint8_t)Vin);
    UART2_Write((uint8_t)(Vin >> 8));
    UART2_Write((uint8_t)Iin);
    UART2_Write((uint8_t)(Iin >> 8));
    UART2_Write((uint8_t)Vout);
    UART2_Write((uint8_t)(Vout >> 8));
    UART2_Write((uint8_t)Iout);
    UART2_Write((uint8_t)(Iout >> 8));
	UART2_Write((uint8_t)temp_board1);
    UART2_Write((uint8_t)(temp_board1 >> 8));
    UART2_Write((uint8_t)temp_board2);
    UART2_Write((uint8_t)(temp_board2 >> 8));
    
    UART2_Write((uint8_t)mppt_enabled);
    UART2_Write((uint8_t)forceDuty);
    UART2_Write((uint8_t)freq_feed);
    UART2_Write((uint8_t)dt_feed);
    UART2_Write((uint8_t)dutyM1);
    UART2_Write((uint8_t)(dutyM1 >> 8));
    UART2_Write((uint8_t)dutyM3);
    UART2_Write((uint8_t)(dutyM3 >> 8));
    UART2_Write((uint8_t)tipo_MPPT);
    
    while (!(UART2_StatusGet() & UART2_TX_COMPLETE)); //attendi buffer si sia svuotato
    //__delay_us(100);  //per svuotare buffer in uart senza interrupt
    WIFI_IO1_SetLow();
}

//*****************************************************************************/

#define WIFI_BUFFER_SIZE 256
uint8_t wifi_buffer[WIFI_BUFFER_SIZE];
uint16_t num_byte_received = 0;

#define wifi_buffer_is_full (WIFI_BUFFER_SIZE==num_byte_received)
#define wifi_buffer_is_empty (num_byte_received==0)

void getWiFiData() {

    while (!UART2_ReceiveBufferIsEmpty() && !wifi_buffer_is_full) {
		num_byte_received += UART2_ReadBuffer( wifi_buffer + num_byte_received, 1/*UART2_RX_BUFFER_SIZE*/);
        //printf("> %u \"%s\"\r\n", num_byte_received, wifi_buffer);
		if (wifi_buffer[num_byte_received-1]==0) num_byte_received--;
		if ( num_byte_received>1 && wifi_buffer[num_byte_received-2]=='\r' && wifi_buffer[num_byte_received-1]=='\n' ) {
			wifi_buffer[num_byte_received]='\0';
            
            //decodifico dato
            if ( strncmp((char*)wifi_buffer, "#mppt=", 6) == 0 ) {
                uint8_t value_rcv = atoi((char*)(wifi_buffer+6));
                if (value_rcv < 2) {
                    mppt_enabled = value_rcv;
                    printf("> WiFi changed setting: MPPT=%u\r\n\r\n", mppt_enabled);
                } else {
                    printf("> WiFi error getting settings\r\n\r\n");
                }
            } else if ( strncmp((char*)wifi_buffer, "#freq=", 6) == 0 ) {
                uint8_t value_rcv = atoi((char*)(wifi_buffer+6));
                if (value_rcv < 8) {
                    freq = value_rcv;
                    printf("> WiFi changed setting: Frequency=%u\r\n Sending data...", freq);
                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                } else {
                    printf("> WiFi error getting settings\r\n\r\n");
                }
            } else if ( strncmp((char*)wifi_buffer, "#dt=", 4) == 0 ) {
                uint8_t value_rcv = atoi((char*)(wifi_buffer+4));
                if (value_rcv < 16) {
                    deadTime = value_rcv;
                    printf("> WiFi changed setting: DeadTime=%u\r\n Sending data...", deadTime);
                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                } else {
                    printf("> WiFi error getting settings\r\n\r\n");
                }
            } else if ( strncmp((char*)wifi_buffer, "#m1=", 4) == 0 ) {
                uint16_t value_rcv = atoi((char*)(wifi_buffer+4));
                if (value_rcv < 4096) {
                    dutyM1 = value_rcv;
                    printf("> WiFi changed setting: DutyCycle M1=%u\r\n Sending data...", dutyM1);
                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                } else {
                    printf("> WiFi error getting settings\r\n\r\n");
                }
            } else if ( strncmp((char*)wifi_buffer, "#m3=", 4) == 0 ) {
                uint16_t value_rcv = atoi((char*)(wifi_buffer+4));
                if (value_rcv < 4096) {
                    dutyM3 = value_rcv;
                    printf("> WiFi changed setting: DutyCycle M3=%u\r\n Sending data...", dutyM3);
                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                } else {
                    printf("> WiFi error getting settings\r\n\r\n");
                }
            } else if ( strncmp((char*)wifi_buffer, "#algo=", 6) == 0 ) {
                uint8_t value_rcv = atoi((char*)(wifi_buffer+6));
                if (value_rcv < 4) {
                    tipo_MPPT = value_rcv;
                    printf("> WiFi changed setting: MPPT algorithm=%u\r\n\r\n", tipo_MPPT);
                } else {
                    printf("> WiFi error getting settings\r\n\r\n");
                }
            }
            //azzera buffer
            num_byte_received = 0;
		}
	}
}

//*****************************************************************************/

/**
 * Calcola temperatura da NTC
 * @param adc_voltage
 * @return temperature in °C x 100
 */
inline int16_t calc_temp(float adc_voltage) {
    //10k + NTC(10k) --> NTC is NB12K00103JBB, R@25°C=10k, B=3630K
	//R(ntc) = ( 10k * Vadc ) / (Vcc - Vadc)
	float ntc = (10000.0f * adc_voltage) / (3.33f - adc_voltage);
	
	float steinhart;
	steinhart = ntc / 10000.0f; // (R/Ro)
	steinhart = log(steinhart); // ln(R/Ro)
	steinhart /= 3630.0f; // 1/B * ln(R/Ro)
	steinhart += 1.0f / (25.0f + 273.15f); // + (1/To)
	steinhart = 1.0f / steinhart; // Invert
	steinhart -= 273.15f; // convert to C
	
	return (int16_t)(steinhart*100);
}

void get_temperatures() {
    ADC1_SoftwareTriggerEnable();
    //while (!ADC1_IsSharedChannelAN4ConversionComplete()); // wait for conversion.. 
    while (!ADC1_IsSharedChannelAN5ConversionComplete()); // wait for conversion..
    
    float adc = 0;
    adc = (float)ADC1_SharedChannelAN4ConversionResultGet() * 3.3f /4096;
    temp_board1 = calc_temp(adc);
    
    adc = (float)ADC1_SharedChannelAN5ConversionResultGet() * 3.3f /4096;
    temp_board2 = calc_temp(adc);
}

//*****************************************************************************/

inline void status_menu() {
    printf("Vi=%u  Ii1=%u  Ii2=%u  Pin=%f   ", Vin, Iin1,Iin2,Pin);
    printf("Vo=%u  Io1=%u  Io2=%u  Pout=%f\r\n", Vout, Iout1, Iout2, Pout);
    //printf("DUTY M1=%u M3=%u  FREQ=%u  DT=%u\r\n", duty_M1_feed, duty_M3_feed, freq_feed, dt_feed);
    printf("DUTY M1=%.2f%% M3=%.2f%%  FREQ=%ukHz  DT=%uns\r\n", 
            (float)duty_M1_feed*100/4096.0, (float)duty_M3_feed*100/4096.0, 
            array_freq_values[freq_feed], array_dt_values[dt_feed]);
    printf("Vref=%u  MODE=", vref);
    if (MODE_BOOST) printf("BOOST ");
    if (MODE_BUCK) printf("BUCK");
    if (MODE_BYPASS) printf("BYPASS");
    //printf("MPPT: A0=%u A1=%u\r\n\r\n", A0, A1);
    printf("  MPPT=%u  FORCE=%u   T1=%d T2=%d", mppt_enabled, forceDuty, 
            temp_board1, temp_board2);
    printf("\r\n\r\n");
}

#define NUM_MENU_OPTIONS 9

inline void print_menu() {
    printf("------------------------------------------------------------\r\n");
    printf("MENU:\r\n1: set duty M1 [%u]\r\n", dutyM1);
    printf("2: set duty M3 [%u]\r\n", dutyM3);
    printf("3: set dead-time [%u]\r\n", deadTime);
    printf("4: set frequency [%u]\r\n", freq);
    printf("5: force duty on/off [%u]\r\n", forceDuty);
    printf("6: bootStrap on/off [%u]\r\n", select_bootStrap);
    printf("7: set Vref [%u V]\r\n", vref/100);
    printf("8: force bypass on/off [%u]\r\n", FORCE_BYPASS_GetValue());
    printf("9: enable MPPT [%u]\r\n", mppt_enabled);
    printf("ESC: exit menu\r\n");
    printf("------------------------------------------------------------\r\n");
}

inline void print_selected() {
    uint8_t i;
    
    printf("> Selected: %u\r\n", select);
    switch (select) {
        case 1: printf("> Insert duty M1 [0-4095]\r\n"); break;
        case 2: printf("> Insert duty M3 [0-4095]\r\n"); break;
        case 3: printf("> Select dead-time [0-15]\r\n");
                for (i=0; i<16; i++) {
                    printf("    %02u = %uns \r\n",i,array_dt_values[i]);
                }
                break;
        case 4: printf("> Select frequency [0-7]\r\n");
                for (i=0; i<8; i++) {
                    printf("    %u = %ukHz \r\n",i,array_freq_values[i]);
                }
                break;
        case 7: printf("> Insert Vref (Volt) [15-70]\r\n"); break;
    }
}

void debug_menu() {
    // switch per le varie sezioni del menu dell'interfaccia seriale
    switch (select) {

        // caso di default stampa a schermo valori acquisiti dall'ADC e home paga menu di scelta
        case -1:
        {
            status_menu();
            
            //controllo del buffer per leggere l'inserimento da seriale
            if (!UART1_ReceiveBufferIsEmpty()) {
                //lettura del buffer e salvataggio del dato sullla variabile push
                UART1_ReadBuffer((uint8_t*)push, UART1_NUM_CHAR_RCV);

                //controllo dell'errore sull'inserimento
                if (push[0]==27) {  //tasto ESC
                    select = -1;
                } else if (push[0]==48) {  //tasto 0
                    select = 0;
                    print_menu();
                } else if (atoi(push) <= NUM_MENU_OPTIONS) {
                    select = atoi(push);
                    print_selected();
                }
                //clear della variabile push per evitare errori sull'istruzione atoi
                memset(push, 0, DBG_RX_BUF_SIZE);
            }            
            break;
        }
        
        case 0:
        {
            //controllo del buffer per leggere l'inserimento da seriale
            if (!UART1_ReceiveBufferIsEmpty()) {
                //lettura del buffer e salvataggio del dato sullla variabile push
                UART1_ReadBuffer((uint8_t*)push, UART1_NUM_CHAR_RCV);
                
                //controllo dell'errore sull'inserimento
                if (push[0]==27) {  //tasto ESC
                    select = -1;
                } else if (atoi(push) <= NUM_MENU_OPTIONS) {
                    select = atoi(push);
                    print_selected();
                } else {
                    printf("!!!!ERRORE!!!!\r\n");
                    select = 0;
                }
                //clear della variabile push per evitare errori sull'istruzione atoi
                memset(push, 0, DBG_RX_BUF_SIZE);
            }
            break;
        }

        //caso scelta inserimento nuovo duty di M1
        case 1:
        {
            //controllo del buffer per leggere l'inserimento da seriale
            if (UART1_NUM_CHAR_RCV >= 4) {      //attende almeno 4 char
                //lettura del buffer e salvataggio del dato sullla variabile push
                UART1_ReadBuffer((uint8_t*)push, UART1_NUM_CHAR_RCV);
                
                //controllo dell'errore sull'inserimento
                if (push[0]==27) {  //tasto ESC
                    select = 0;
                } else if (atoi(push) < 4096) {
                    dutyM1 = atoi(push);
                    printf("> Selected: %u\r\n Sending data...", dutyM1);
                  
                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                    
                    //ripristino scelta menu
                    select = -1;
                } else {
                    printf("!!!!ERRORE!!!!\r\n");
                    select = -1;
                }
                //clear della variabile push per evitare errori sull'istruzione atoi
                memset(push, 0, DBG_RX_BUF_SIZE);
            }
            break;
        }
            
        //caso scelta inserimento nuovo duty di M3
        case 2:
        {
            //controllo del buffer per leggere l'inserimento da seriale
            if (UART1_NUM_CHAR_RCV >= 4) {      //attende almeno 4 char
                //lettura del buffer e salvataggio del dato sullla variabile push
                UART1_ReadBuffer((uint8_t*)push, UART1_NUM_CHAR_RCV);
                
                //controllo dell'errore sull'inserimento
                if (push[0]==27) {  //tasto ESC
                    select = 0;
                } else if (atoi(push) < 4096) {                    
                    dutyM3 = atoi(push);
                    printf("> Selected: %u\r\n Sending data...", dutyM3);

                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                    
                    //ripristino scelta menu
                    select = -1;
                } else {
                    printf("!!!!ERRORE!!!!\r\n");
                    select = -1;
                }
                //clear della variabile push per evitare errori sull'istruzione atoi
                memset(push, 0, DBG_RX_BUF_SIZE);
            }
            break;
        }

        //caso scelta inserimento nuovo valore di dead time
        case 3:
        {
            //controllo del buffer per leggere l'inserimento da seriale
            if (UART1_NUM_CHAR_RCV >= 2) {      //attende almeno 2 char
                //lettura del buffer e salvataggio del dato sullla variabile push
                UART1_ReadBuffer((uint8_t*)push, UART1_NUM_CHAR_RCV);
                
                //controllo dell'errore sull'inserimento
                if (push[0]==27) {  //tasto ESC
                    select = 0;
                } else if (atoi(push) < 16) {
                    deadTime = atoi(push);
                    printf("> Selected: %u\r\n Sending data...", deadTime);

                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                    
                    //ripristino scelta menu
                    select = -1;
                } else {
                    printf("!!!!ERRORE!!!!\r\n");
                    select = -1;
                }
                //clear della variabile push per evitare errori sull'istruzione atoi
                memset(push, 0, DBG_RX_BUF_SIZE);
            }
            break;
        }

        //caso scelta inserimento nuovo valore di dead time
        case 4:
        {
            //controllo del buffer per leggere l'inserimento da seriale
            if (!UART1_ReceiveBufferIsEmpty()) {    //attende almeno 1 char
                //lettura del buffer e salvataggio del dato sullla variabile push
                UART1_ReadBuffer((uint8_t*)push, UART1_NUM_CHAR_RCV);
                
                //controllo dell'errore sull'inserimento
                if (push[0]==27) {  //tasto ESC
                    select = 0;
                } else if (atoi(push) < 8) {
                    freq = atoi(push);
                    printf("> Selected: %u\r\n Sending data...", freq);

                    // invio nuovi parametri all'FPGA
                    outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
                    printf(" OK\r\n\r\n");
                    
                    //ripristino scelta menu
                    select = -1;
                } else {
                    printf("!!!!ERRORE!!!!\r\n");
                    select = -1;
                }
                //clear della variabile push per evitare errori sull'istruzione atoi
                memset(push, 0, DBG_RX_BUF_SIZE);
            }
            break;
        }

        //Caso attivazione forzamento duty
        case 5:
        {
            forceDuty = !forceDuty;            
            printf("> Set forceDuty = %u\r\n Sending data...", forceDuty);

            // invio nuovi parametri all'FPGA
            outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
            printf(" OK\r\n\r\n");

            //ripristino scelta menu
            select = -1;
            
            //print_menu();
            break;
        }

        case 6:
        {
            select_bootStrap = !select_bootStrap;
            printf("> Set bootstrap = %u\r\n Sending data...", select_bootStrap);

            // invio nuovi parametri all'FPGA
            outputParam(dutyM1, dutyM3, deadTime, freq, forceDuty, select_bootStrap);
            printf(" OK\r\n\r\n");

            //ripristino scelta menu
            select = -1;
            
            //print_menu();
            break;
        }

        case 7:
        {
            if (UART1_NUM_CHAR_RCV >= 2) {      //attende almeno 2 char
                //lettura del buffer e salvataggio del dato sullla variabile push
                UART1_ReadBuffer((uint8_t*)push, UART1_NUM_CHAR_RCV);
                
                //controllo dell'errore sull'inserimento
                if (push[0]==27) {  //tasto ESC
                    select = 0;
                } else if (atoi(push) <= 70 && atoi(push) >= 15) {
                    // aggiornamento vref
                    vref = atoi(push);                    
                    printf("> Selected: %u.00 V\r\n\r\n", vref);
                    vref = vref * 100;

                    //ripristino scelta men 
                    select = -1;
                } else {
                    printf("!!!!ERRORE!!!!\r\n");
                    select = -1;
                }
                //clear della variabile push per evitare errori sull'istruzione atoi
                memset(push, 0, DBG_RX_BUF_SIZE);
            }
            break;
        }
            
        case 8:
        {
            FORCE_BYPASS_Toggle();
            printf("> Toogle BYPASS\r\n\r\n");

            //ripristino scelta menu
            select = -1;
            break;
        }

        case 9:
        {
            mppt_enabled = !mppt_enabled;
            printf("> MPPT enabled=%u\r\n\r\n", mppt_enabled);
            
            //ripristino scelta menu
            select = -1;
            break;
        }

        default:
            select = -1;
            break;
    }
}

//*****************************************************************************/

// Interrupt ricezione dato SPI
void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt() {

    //Lettura dato SPI
    dato_spi = SPI1_Exchange16bit(2);

    // salvataggio dato del nella variabile, tramite l'if viene letto l'header
    // per discriminare la tipologia del dato inviato

    //--------------------------------------------------------------------|
    //                 Formato stringa inviata dall' FPGA                 |
    //-------|------------------------------------------------------------|
    //header |                          dato                              |
    //-------|------------------------------------------------------------|
    // 0001  |                        dutyM1(12)                          |
    // 0010  |                        dutyM3(12)                          |
    // 0100  |deadTime(4)|frequenza(3)|A0|A1|Mod_buck|Mod_boost|Mod_Bypass|
    //-------|------------------------------------------------------------|


    if (((dato_spi) & (1 << (12))) != 0) {

        duty_M1_feed = (dato_spi << 4) >> 4;

    } else if (((dato_spi) & (1 << (13))) != 0) {

        duty_M3_feed = (dato_spi << 4) >> 4;

    } else if (((dato_spi) & (1 << (14))) != 0) {

        dt_feed = (dato_spi << 4) >> 12;
        freq_feed = (dato_spi << 8) >> 13;
        MODE_BUCK = (dato_spi << 13) >> 15;
        MODE_BOOST = (dato_spi << 14) >> 15;
        MODE_BYPASS = (dato_spi << 15) >> 15;
        A0 = (dato_spi << 11) >> 15;
        A1 = (dato_spi << 12) >> 15;
    }
    
    FPGA_started = true;

    // Clear Flag
    IFS0bits.SPI1IF = 0;
}


/* Interrupt service routine for the CNI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _CNInterrupt ( void )
{
    if(IFS1bits.CNIF == 1)
    {
        check_enable();
        // Clear the flag
        IFS1bits.CNIF = 0;
    }
}

//CMP1 -> AN0/CMP1A = VOUT > 70V    CMREF=4090 (CMREF/4096*3.33*23=76.5)
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CMP1Interrupt(void)
{
    dutyM3=dutyM3-AUMENTO_DUTY;
    vref=vref-AUMENTO_VREF;
    printf("limit Vout\r\n");
    // clear the CMP1 interrupt flag
    IFS1bits.AC1IF = 0;
}

//CMP2 -> AN2/CMP2A = IIN1 > 10A    CMREF=3724 (CMREF/4096*3.33/(0.0015*200)=10)
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CMP2Interrupt(void)
{
    dutyM3=dutyM3-AUMENTO_DUTY;
    vref=vref-AUMENTO_VREF;
    printf("limit Iin1\r\n");
    // clear the CMP2 interrupt flag
    IFS6bits.AC2IF = 0;
}

//CMP3 -> PGA1OUT = 4x AN1/PGA1P2 = VIN < 15V (inverted)   CMREF=3208 (CMREF/4096/4*3.33*23=15)
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CMP3Interrupt(void)
{
    dutyM3=dutyM3-AUMENTO_DUTY; //TODO disabilitare o andare in BYPASS???
    vref=vref-AUMENTO_VREF;
    printf("limit Vin\r\n");
    // clear the CMP3 interrupt flag
    IFS6bits.AC3IF = 0;
}

/**
 End of File
 */
