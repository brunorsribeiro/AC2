// T1
// fout = 4Hz
// prescale = ceil(20000000/(65536*fout)) = 77 = 256
// fout_prescale = 20000000/prescale = 78125
// PR1 = (fout_prescale/fout) - 1 = 19530
// T3
// fout = 100Hz
// prescale = ceil(20000000/(65536*fout)) = 4 = 4
// fout_prescale = 20000000/prescale = 5000000
// PR3 = (fout_prescale/fout) - 1 = 49999
// PWM
// fout = 100Hz
// duty-cycle = 0.25
// prescale = 20000000/(65536*fout) = 4
// fout_prescale = 20000000/prescale = 5000000
// PR3 = (fout_prescale/fout) - 1 = 49999
// OC1RS = (PR3+1)*duty-cycle = 12500
#include <detpic32.h>
#include "../aux.c"
void putc(unsigned char);
char getc(void);
void putStr(char*);

static int *aux;
static int val;
static int voltMin = 50,voltMax = 0;

int main(void){
	// Timer 1
	T1CONbits.TCKPS = 1;
	PR1 = 19530;
	TMR1 = 0;
	IPC1bits.T1IP = 3;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	T1CONbits.TON = 1;
	// Timer 3
	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	T3CONbits.TON = 1;
	// Config AD
	configAD(8);
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
	configDisplay();
	// Config Switches
	TRISB = TRISB | 0x0003;
	// PWM
	OC1CONbits.OCM = 6;
	OC1CONbits.OCTSEL = 1;
	OC1CONbits.ON = 1;
	configUART(115200,'n',1,1);
	EnableInterrupts();
	char swtVal;
	while (1){
		swtVal = PORTB & 0x0003;
		switch (swtVal) {
			case 0:
				IEC0bits.T1IE = 1;
				setPWM(0);
			break;
			case 1:
				IEC0bits.T1IE = 0;
				setPWM(100);
			break;
			default:
				IEC0bits.T1IE = 1;
				setPWM(3*val);
			break;
		}
	}
}

void _int_(4) isr_T1(void){
	AD1CON1bits.ASAM = 1; // Start Convesion
	IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
	static int i = 0;
	if(++i == 100){
		putc((val/10)+48);
		putc((val%10)+48);
		i = 0;
	}
	sendToDisplay(toBcd(val));
	IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){
	aux = (int*)(&ADC1BUF0);
	for(; aux <= (int*)(&ADC1BUFF); aux +=4){
		val += *aux;
	}
	val /= 8;
	val=((val*33)+511)/1023;
	if(val > voltMax) voltMax = val;
	if(val < voltMin) voltMin = val;
	IFS1bits.AD1IF = 0;
}

void putc(unsigned char c){
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
	if(U1RXREG == 'l' || U1RXREG == 'L'){
		putc((voltMin/10)+48);
		putc((voltMin%10)+48);
		putc((voltMax/10)+48);
		putc((voltMax%10)+48);
		}
	IFS0bits.U1RXIF = 0;
}
