// fout = 2Hz
// prescale = ceil(20000000/(65536*fout)) = 153 = 256
// fout_prescale = 20000000/256 = 78125
// PR3 = (fout_prescale/fout) - 1 = 39061
#include <detpic32.h>

int main(void){
	T3CONbits.TCKPS = 7;
	PR3 = 39061;
	TMR3 = 0;
	T3CONbits.TON = 1;
	while (1) {
		while(IFS0bits.T3IF == 0);
		IFS0bits.T3IF = 0;
		putChar('.');
	}
}
