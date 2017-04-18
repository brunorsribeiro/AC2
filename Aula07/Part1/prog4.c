// T1
// fout = 2Hz
// prescale = ceil(20000000/(65536*fout)) = 153 = 256
// fout_prescale = 20000000/prescale = 78125
// PR1 = (fout_prescale/fout) - 1 = 39061
// T3
// fout = 10Hz
// prescale = ceil(20000000/(65536*fout)) = 31 = 32
// fout_prescale = 20000000/prescale = 625000
// PR3 = (fout_prescale/fout) - 1 = 62499
#include <detpic32.h>
#include "../../aux.c"

static char i = 0;
int main(void){
	// Timer 1
	T1CONbits.TCKPS = 3;
	PR1 = 39061;
	TMR1 = 0;
	IPC1bits.T1IP = 3;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	T1CONbits.TON = 1;
	// Timer 3
	T3CONbits.TCKPS = 5; // half prescale double frequency
	PR3 = 62499;
	TMR3 = 0;
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	T3CONbits.TON = 1;
	EnableInterrupts();
	while (1);
}


void _int_(4) isr_T1(void){
	putChar('1');
	IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
	putChar('3');
	IFS0bits.T3IF = 0;
}
