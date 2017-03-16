#include <detpic32.h>
#include "aux.c"

void delay(int);

int main(void) {
	LATEbits.LATE0 = 0;
	TRISEbits.TRISE0 = 0;
	while (1) {
		delay(500);
		LATEbits.LATE0 = !LATEbits.LATE0;
	}
	return 0;
}
