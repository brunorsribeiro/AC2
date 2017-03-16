#include <detpic32.h>
#include "aux.c"

int main(void){
	unsigned char val = 0;
	int i;
	configDisplay();
	while (1) {
		i = 0;
		do {
			delay(10);
			sendToDisplay(toBcd(val));
		} while(++ i < 100);
		val++;
		if(val > 59 )
			val = 0;
	}
	return 0;
}
