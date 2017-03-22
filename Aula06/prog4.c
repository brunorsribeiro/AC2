#include <detpic32.h>
#include "aux.c"

static int *aux;
static int val;

void _int_(27) isr_adc(void){
	aux = (int*)(&ADC1BUF0);
	for(; aux <= (int*)(&ADC1BUFF); aux +=4){
		val += *aux;
	}
	val /= 8;
	val=((val*33)+511)/1023;
	printInt10(val);
	IFS1bits.AD1IF = 0;
}


int main(void){
	configDisplay();
	// Config RB6
	TRISBbits.TRISB6 = 0;
	// Config AD
	configAD(8);
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
	EnableInterrupts();
	AD1CON1bits.ASAM = 1; // Start Convesion
	int i = 0;
	while(1){
		delay(10);
		if(++i == 25){
			AD1CON1bits.ASAM = 1; // Start Convesion
			i = 0;
		}
		sendToDisplay(toBcd(val));
	}
	return 0;
}
