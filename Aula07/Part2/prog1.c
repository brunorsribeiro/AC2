// fout = 100Hz
// duty-cycle = 0.25
// prescale = 20000000/(65536*fout) = 4
// fout_prescale = 20000000/prescale = 5000000
// PR3 = (fout_prescale/fout) - 1 = 49999
// OC1RS = (PR3+1)*duty-cycle = 12500
// Res = log(PR2+1)

#include <detpic32.h>
#include "../../aux.c"

int main(void){
	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	IFS0bits.T3IF = 0;
	T3CONbits.TON = 1;
	OC1CONbits.OCM = 6;
	OC1CONbits.OCTSEL = 1;
	OC1RS = 12500;
	OC1CONbits.ON = 1;
	while (1){
		setPWM(0);
	}
	return 0;
}
