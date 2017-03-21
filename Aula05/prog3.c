#include <detpic32.h>
#include "aux.c"

int main(void){
	// Config ADC
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0; // RB4 as analog IN
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1; // Stop on Interrupt
	AD1CON3bits.SAMC = 16; // Sample Time
	AD1CON2bits.SMPI = 3; // Number of samples - 1
	AD1CHSbits.CH0SA = 4; // IN Channel
	AD1CON1bits.ON = 1; // ADC ON
	// Config RB6
	TRISBbits.TRISB6 = 0;
	int *aux;
	while (1) {
		LATBbits.LATB6 = 1;
		AD1CON1bits.ASAM = 1; // Start Convesion
		while (IFS1bits.AD1IF == 0); // poling
		LATBbits.LATB6 = 0;
		aux = (int*)(&ADC1BUF0);
		for(; aux <= (int*)(&ADC1BUFF); aux +=4){
			printInt(*aux,10|4<<10);
			putChar(' ');
		}
		IFS1bits.AD1IF = 0; // Reset Interrupt Register
	}
	return 0;
}
