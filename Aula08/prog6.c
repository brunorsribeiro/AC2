#include "detpic32.h"
#include "../aux.c"

void putc(char);
char getc(void);
void putStr(char*);

int main(void) {
	configUART(115200,'n',1,0);
	TRISBbits.TRISB6 = 0;
	while(1){
		LATBbits.LATB6 = 1;
		putc(getc());
		LATBbits.LATB6 = 0;
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

char getc(void){
	if(U1STAbits.OERR == 1) U1STAbits.OERR = 0;
	while(U1STAbits.URXDA == 0);
	if(U1STAbits.FERR == 1 || U1STAbits.PERR) return 0;
	else return U1RXREG;
}
