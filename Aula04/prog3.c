#include <detpic32.h>

int main(void) {
	LATB = (LATB & 0x00FF);
	LATD = (LATD & 0xFF9F);
	TRISB = (TRISB & 0x00FF);
	TRISD = (TRISD & 0xFF9F);
	LATD = (LATD | 0x0060);
	while (1) {
		char pressed = getChar();
		if((pressed >= 'A' && pressed <= 'G') || (pressed >= 'a' && pressed <= 'g') || pressed == '.'){
			LATB = (LATB & 0x00FF);
			switch (pressed) {
				case 'A': case 'a':
					LATB = (LATB | 0x0100);
					break;
				case 'B': case 'b':
					LATB = (LATB | 0x0200);
					break;
				case 'C': case 'c':
					LATB = (LATB | 0x0400);
					break;
				case 'D': case 'd':
					LATB = (LATB | 0x0800);
					break;
				case 'E': case 'e':
					LATB = (LATB | 0x1000);
					break;
				case 'F': case 'f':
					LATB = (LATB | 0x2000);
					break;
				case 'G': case 'g':
					LATB = (LATB | 0x4000);
					break;
				case '.':
					LATB = (LATB | 0x8000);
					break;
			}
		}
	}
	return 0;
}
