#include <detpic32.h>
#include "aux.c"

int main(void) {
	static const char disp7codes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	int swtVal;
	LATB = LATB & 0x00FF;
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 0;
	TRISB = TRISB & 0x00FF;
	TRISD = TRISD & 0xFF9F;
	TRISB = TRISB | 0x000F;
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 1;
	while (1) {
		swtVal = PORTB & 0x000F;
		LATB = LATB | disp7codes[swtVal];
		LATB = LATB << 8;
	}
	return 0;
}
