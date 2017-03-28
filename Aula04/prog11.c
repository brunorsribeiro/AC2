#include <detpic32.h>
#include "../aux.c"

int main(void){
	unsigned char val = 0;
	int i;
	configDisplay();
	while (1) {
		i = 0;
		do {
			delay(10);
			sendToDisplay(toBcd(val));
			if(val == 0){
				int j = 0;
				LATDbits.LATD5 = 0;
				LATDbits.LATD6 = 0;
				do {
					delay(500);
					LATDbits.LATD5 ^= 1;
					LATDbits.LATD6 ^= 1;
				} while(++j < 10);
				val++;
			}
		} while(++ i < 100);
		val++;
		if(val > 59 )
			val = 0;
	}
	return 0;
}
