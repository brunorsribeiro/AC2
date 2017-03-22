#include <detpic32.h>
#include "aux.c"



void _int_(27) isr_adc(void){
	LATBbits.LATB6 = 0;
	printInt(ADC1BUF0,16|3<<16);
	AD1CON1bits.ASAM = 1; // Start Convesion
	LATBbits.LATB6 = 1;
	IFS1bits.AD1IF = 0;
	LATBbits.LATB6 = 1;
}


int main(void){
	// Config RB6
	TRISBbits.TRISB6 = 0;
	// Config AD
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0; // RB4 as analog IN
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1; // Stop on Interrupt
	AD1CON3bits.SAMC = 16; // Sample Time
	AD1CON2bits.SMPI = 0; // Number of samples - 1
	AD1CHSbits.CH0SA = 4; // IN Channel
	AD1CON1bits.ON = 1; // ADC ON
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
	EnableInterrupts();
	AD1CON1bits.ASAM = 1; // Start Convesion
	while(1){
		LATBbits.LATB6 = 0;
	}
	return 0;
}
