#include <detpic32.h>
#include "delay.c"

int main(void){
	char count = 0;
	LATE = LATE | 0xFFF0;
	TRISE = TRISE & 0xFFF0;
	while (1) {
		LATE = count;
		delay(250);
		count++;
	}
	return 0;
}
