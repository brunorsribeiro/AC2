// T1
// fout = 4Hz
// prescale = ceil(20000000/(65536*fout)) = 77 = 256
// fout_prescale = 20000000/prescale = 78125
// PR1 = (fout_prescale/fout) - 1 = 19530
// T3
// fout = 100Hz
// prescale = ceil(20000000/(65536*fout)) = 4 = 4
// fout_prescale = 20000000/prescale = 1250000
// PR3 = (fout_prescale/fout) - 1 = 62499
// PWM
// fout = 100Hz
// duty-cycle = 0.25
// prescale = 20000000/(65536*fout) = 4
// fout_prescale = 20000000/prescale = 5000000
// PR3 = (fout_prescale/fout) - 1 = 49999
// OC1RS = (PR3+1)*duty-cycle = 12500
#include <detpic32.h>
#include "../../aux.c"

unsigned volatile int val;

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
	// PWM
	OC1CONbits.OCM = 6;
	OC1CONbits.OCTSEL = 1;
	OC1CONbits.ON = 1;
	EnableInterrupts();
	char swtVal;
	while (1){
		swtVal = PORTB & 0x0003;
		switch (swtVal) {
			case 0:
				IEC0bits.T1IE = 1;
				setPWM(0);
			break;
			case 1:
				IEC0bits.T1IE = 0;
				setPWM(100);
			break;
			default:
				IEC0bits.T1IE = 1;
				setPWM(3*val);
			break;
		}
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
	unsigned int *aux = &ADC1BUF0;
	for(; aux <= &ADC1BUFF; aux +=4){
		val += *aux;
	}
	val /= 8;
	val=((val*33))/1023;
	IFS1bits.AD1IF = 0;
}
