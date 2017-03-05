	.equ SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area
	# TRISA 0x6000
	# TRISF 0x6140
	.equ TRISB, 0x6040            # TRISB address is 0xBF886040
	.equ PORTB, 0x6050            # PORTB address is 0xBF886050
	.equ LATB,  0x6060            # LATB  address is 0xBF886060
	.equ TRISE, 0x6100            # TRISE address is 0xBF886100
	.equ PORTE, 0x6110            # PORTE address is 0xBF886110
	.equ LATE,  0x6120            # LATE  address is 0xBF886120
	.data
	.text
	.globl main
main: 	lui $t1,SFR_BASE_HI
	# Set RE as OUT
	lw $t2,TRISE($t1)
	andi $t2,$t2,0xFFF0
	sw $t2,TRISE($t1)
	# Set RB as IN
	lw $t2,TRISB($t1)
	ori $t2,$t2,0x000F
	sw $t2,TRISB($t1)
	#while 1
while:	# Read from RB
	lw $t2,PORTB($t1)
	#Invert 0 & 3, keep 1 & 2
	xori $t2,$t2,0x0009
	# Write to RE
	sw $t2,LATE($t1)
	j while
	jr $ra
