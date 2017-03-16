void configDisplay(void);
void delay(int);
void sendToDisplay(unsigned const char);
unsigned char toBcd(unsigned char);
void blink(int, int);

void configDisplay(void){
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 0;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 1;
	LATB  = LATB  & 0x00FF;
	TRISB = TRISB & 0x00FF;
}

void delay(int ms){
	for (;ms > 0; ms--){
		resetCoreTimer();
		while (readCoreTimer() < 20000);
	}
}

void sendToDisplay(unsigned char value){
	static const char disp7codes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	static char dispFlag = 0;
	char msb = disp7codes[value >> 4];
	char lsb = disp7codes[value & 0x0F];
	if(dispFlag){
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
		LATB = LATB | msb;
		LATB = LATB << 8;
		if(value % 2 != 0) LATBbits.LATB15 = 1;
	}else{
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;
		LATB = LATB | lsb;
		LATB = LATB << 8;
		if(value % 2 == 0) LATBbits.LATB15 = 1;
	}
	if(value == 0) blink(500,5);
	dispFlag ^= 1;
}

unsigned char toBcd(unsigned char value){
	return ((value/10) << 4) + (value%10);
}

void blink(int onTime, int timer){
    int i = 0;
	do {
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 0;
		delay(onTime);
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 1;
	} while(++ i < (onTime*2)*timer);

}
