#include <detpic32.h>
#include "delay.c"

int main(void){
	unsigned char segment;
	int i;
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 0;
	LATB  = (LATB  & 0x00FF);
	TRISB = (TRISB & 0x00FF);
	TRISD = (TRISD & 0xFF9F);
	LATDbits.LATD6 = 1;
	while(1){
		LATD = LATD ^ 0x0060;
		segment = 1;
		for(i = 0; i < 7; i++){
			LATB = (LATB | segment);
			LATB = LATB << 8;
			delay(10);
			segment = segment << 1;
		}
	}
	return 0;
}
