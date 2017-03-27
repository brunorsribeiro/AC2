// T1
// fout = 4Hz
// prescale = ceil(20000000/(65536*fout)) = 77 = 256
// fout_prescale = 20000000/prescale = 78125
// PR1 = (fout_prescale/fout) - 1 = 19530
// T3
// fout = 100Hz
// prescale = ceil(20000000/(65536*fout)) = 4 = 4
// fout_prescale = 20000000/prescale = 5000000
// PR3 = (fout_prescale/fout) - 1 = 49999
#include <detpic32.h>
#include "aux.c"

static int *aux;
static int val;

int main(void){
	// Timer 1
	T1CONbits.TCKPS = 3;
	PR1 = 19530;
	TMR1 = 0;
	IPC1bits.T1IP = 3;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	T1CONbits.TON = 1;
	// Timer 3
	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	T3CONbits.TON = 1;
	// Config AD
	configAD(8);
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
	configDisplay();
	// Config Switches
	TRISB = TRISB | 0x0003;
	EnableInterrupts();
	while (1){
		if(PORTBbits.RB0 == 0 && PORTBbits.RB1 == 1) IEC0bits.T3IE = 0;
		else IEC0bits.T3IE = 1;
	}
}

void _int_(4) isr_T1(void){
	AD1CON1bits.ASAM = 1; // Start Convesion
	IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
	sendToDisplay(toBcd(val));
	IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){
	aux = (int*)(&ADC1BUF0);
	for(; aux <= (int*)(&ADC1BUFF); aux +=4){
		val += *aux;
	}
	val /= 8;
	val=((val*33)+511)/1023;
	printInt10(val);
	IFS1bits.AD1IF = 0;
}
