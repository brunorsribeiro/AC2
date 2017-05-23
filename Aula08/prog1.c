#include "detpic32.h"
#include "../aux.c"

void putc(char);
void putStr(char*);

int main(void) {
	configUART(1200,'o',2);
	while(1){
		putStr("String de teste\n");
		// putc('+');
		delay(1000);
	}
	return 0;
}

void putc(char c){
	while(U1STAbits.UTXBF == 1);
	U1TXREG = c;
}

void putStr(char* string){
	int i;
	for (i = 0; string[i] != '\0'; i++) {
		putc(string[i]);
	}
}
