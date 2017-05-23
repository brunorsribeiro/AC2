#include <detpic32.h>
#define  DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define  EnableUart1RxInterrupt()  IEC0bits.U1RXIE = 1
#define  DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define  EnableUart1TxInterrupt()  IEC0bits.U1TXIE = 1
#define  BUF_SIZE 8
#define  INDEX_MASK (BUF_SIZE-1)

typedef struct{
	unsigned char data[BUF_SIZE];
	unsigned int tail;
	unsigned int count;
	unsigned int head;
} circularBuffer;

volatile circularBuffer txb,rxb;

void comDrv_flushRx(){
	rxb.head=0;
	rxb.tail=0;
	rxb.count=0;
}

void comDrv_flushTx(){
	txb.head=0;
	txb.tail=0;
	txb.count=0;
}

void comDrv_putc(char c){
	while(txb.count == BUF_SIZE);
	txb.data[txb.tail] = c;
	txb.tail = (txb.tail + 1) & INDEX_MASK;
	DisableUart1TxInterrupt();
	txb.count++;
	EnableUart1TxInterrupt();
}

void comDrv_puts(char *s){
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		comDrv_putc(s[i]);
	}
}

char comDrv_getc(char *pchar){
	if(rxb.count == 0) return 0;
	DisableUart1RxInterrupt();
	*pchar = rxb.data[rxb.head];
	rxb.head = (rxb.head + 1) & INDEX_MASK;
	rxb.count--;
	EnableUart1RxInterrupt();
	return 1;
}


void _int_(24) isr_uart1(void){
	if(IFS0bits.U1TXIF == 1){
		if(txb.count > 0){
			U1TXREG = txb.data[txb.head];
			txb.head = (txb.head + 1) & INDEX_MASK;
			txb.count--;
		}
		if(txb.count == 0){
			DisableUart1TxInterrupt();
		}
		IFS0bits.U1TXIF = 0;
	}
	if(IFS0bits.U1RXIF == 1){
		rxb.data[rxb.tail] = U1RXREG;
		rxb.tail = (rxb.tail + 1) & INDEX_MASK;
		if(rxb.count < BUF_SIZE){
			rxb.count++;
		}else{
			rxb.head++;
		}
		IFS0bits.U1RXIF = 0;
	}
}

void comDrv_config(int br, char parity, int stop){
	DisableUart1TxInterrupt();
	DisableUart1RxInterrupt();
	IPC6bits.U1IP = 2;
	IFS0bits.U1RXIF = 0;
	IFS0bits.U1TXIF = 0;
	U1STAbits.URXISEL = 0;
	U1STAbits.UTXSEL = 0;
	U1MODEbits.BRGH = 0;
	if(br >= 600 && br < 115200){
		U1BRG = (20000000/(16*br))-1;
	}else{
		U1BRG = 10;
	}
	switch (parity) {
		case 'e':case'E':
		U1MODEbits.PDSEL = 1;
		break;
		case 'o':case'O':
		U1MODEbits.PDSEL = 2;
		break;
		default:
		U1MODEbits.PDSEL = 0;
		break;
	}
	switch (stop) {
		case 2:
		U1MODEbits.STSEL = 1;
		break;
		default:
		U1MODEbits.STSEL = 0;
		break;
	}
	U1STAbits.URXEN = 1;
	U1STAbits.UTXEN = 1;
	U1MODEbits.ON = 1;
}

int main(void){
	comDrv_config(115200,'N',1);
	comDrv_flushTx();
	comDrv_flushRx();
	EnableInterrupts();
	char c;
	comDrv_puts("PIC32 UART Device driver");
	while(1){
		comDrv_getc(&c);
		comDrv_putc(c);
	}
	return 0;
}
