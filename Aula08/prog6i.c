#include "detpic32.h"
#include "../aux.c"

void putc(char);
char getc(void);
void putStr(char*);

int main(void) {
	configUART(115200,'n',1,1);
	EnableInterrupts();
	TRISBbits.TRISB6 = 0;
	while(1);
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

void _int_(24) isr_uart1(void){
	putc(U1RXREG);
	if(IFS0bits.U1TXIF == 1) IFS0bits.U1TXIF = 0;
	if(IFS0bits.U1EIF == 1) IFS0bits.U1EIF = 0;
	IFS0bits.U1RXIF = 0;
}
