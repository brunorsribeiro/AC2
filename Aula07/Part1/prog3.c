// fout = 1Hz
// prescale = ceil(20000000/(65536*fout)) = 305 Not Possible
#include <detpic32.h>
#include "aux.c"


static char i = 0;
int main(void){
	T3CONbits.TCKPS = 7;
	PR3 = 39061;
	TMR3 = 0;
	T3CONbits.TON = 1;
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	EnableInterrupts();
	while (1);
}


void _int_(12) isr_T3(void){
	if(i == 2){
		putChar('.');
		i = 0;
	}
	i++;
	IFS0bits.T3IF = 0;
}
