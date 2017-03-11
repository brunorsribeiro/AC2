void delay(int ms){
	for (;ms > 0; ms--){
		resetCoreTimer();
		printInt(readCoreTimer(),10);
		printStr("\n");
		while (readCoreTimer() < 20000){
			printInt(readCoreTimer(),10);
			printStr("\n");
		}
	}
}
