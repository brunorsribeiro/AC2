#include <detpic32.h>
#include "../aux.c"
#include "i2c.h"

int main(void){
	int ack,temp;
	i2c1_init(TC74_CLK_FREQ);
    int	flag = 0;
	while (1) {
		i2c1_start();
		ack = i2c1_send(ADDR_WR);
		ack += i2c1_send(RTR);
		i2c1_start();
		ack += i2c1_send(ADDR_RD);
		if(ack){
			i2c1_stop();
			printStr("ERROR");
			break;
		}
		temp = i2c1_receive(I2C_NACK);
		i2c1_stop();
		switch (flag) {
			case 1:
			printStr("\e[1;33m");
			break;
			case 2:
			printStr("\e[1;31m");
			break;
			case 3:
			printStr("\e[1;32m");
			break;
			case 4:
			printStr("\e[1;36m");
			break;
			default:
			printStr("\e[0m");
			flag = 0;
			break;
		}
		printInt10(temp);
		flag++;
		delay(250);
	}
	return 0;
}
