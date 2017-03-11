		.equ SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area
		# TRISA 0x6000
		# TRISF 0x6140
		.equ TRISB, 0x6040            # TRISB address is 0xBF886040
		.equ PORTB, 0x6050            # PORTB address is 0xBF886050
		.equ LATB,  0x6060            # LATB  address is 0xBF886060
		.equ TRISE, 0x6100            # TRISE address is 0xBF886100
		.equ PORTE, 0x6110            # PORTE address is 0xBF886110
		.equ LATE,  0x6120            # LATE  address is 0xBF886120
		.equ RESET_CORE_TIMER,12
		.equ READ_CORE_TIMER,11
		.data
		.text
		.globl main
main: 	addiu $sp,$sp,-20
		sw $ra,0($sp)
		sw $s0,4($sp)
		sw $s1,8($sp)
		sw $s2,12($sp)
		sw $s3,16($sp)
		lui $s1,SFR_BASE_HI
		# Set RE as OUT
		lw $s2,TRISE($s1)
		andi $s2,$s2,0xFFF0
		sw $s2,TRISE($s1)
		# Set RB as IN
		lw $s2,TRISB($s1)
		ori $s2,$s2,0x000F
		sw $s2,TRISB($s1)
		# Value displayed set in RE
		ori $s0,$0,0
#		# Up Counter
#ufor:	lw $s2,LATE($s1)
#		andi $s2,$s0,0x000F
#		sw $s2,LATE($s1)
#		li $a0,1000
#		jal delay
#		addi $s0,$s0,1
#		j ufor
#		# Down Counter
#dnfor:	lw $s2,LATE($s1)
#		andi $s2,$s0,0x000F
#		sw $s2,LATE($s1)
#		li $a0,250
#		jal delay
#		addi $s0,$s0,-1
#		j dnfor
#		# Up/Down Counter
#udfor:	# Read RB3
#		lw $s2,PORTB($s1)
#		andi $s2,$s2,0x0008
#		beq $s2,8,uif
#		addi $s0,$s0,-1
#		j eif
#uif:	addi $s0,$s0,1
#eif:	lw $s2,LATE($s1)
#		andi $s2,$s0,0x000F
#		sw $s2,LATE($s1)
#		li $a0,500
#		jal delay
#		j udfor
#		# Left Johnson counter
#ljfor:	lw $s2,LATE($s1)
#		andi $s0,$s2,0x0008
#		blt $s0,8,putz
#		sll $s2,$s2,1
#		j ends
#putz:	sll $s2,$s2,1
#		ori $s2,$s2,0x0001
#ends:	sw $s2,LATE($s1)
#		li $a0,666
#		jal delay
#		j ljfor
#		# Right Johnson counter
#rjfor:	lw $s2,LATE($s1)
#		andi $s0,$s2,0x0001
#		beq $s0,0,puto
#		srl $s2,$s2,1
#		j ends
#puto:	srl $s2,$s2,1
#		ori $s2,$s2,0x0008
#ends:	sw $s2,LATE($s1)
#		li $a0,666
#		jal delay
#		j rjfor
#		# Left/Right Johnson counter
#		# Read RB2
#lrjfor:lw $s2,PORTB($s1)
#		andi $s0,$s2,0x0004
#		beq $s0,4,left
#		lw $s2,LATE($s1)
#		andi $s0,$s2,0x0001
#		beq $s0,0,lrputo
#		srl $s2,$s2,1
#		j rend
#lrputo:srl $s2,$s2,1
#		ori $s2,$s2,0x0008
#rend:	sw $s2,LATE($s1)
#		li $a0,666
#		jal delay
#		j lrjfor
#left:	lw $s2,LATE($s1)
#		andi $s0,$s2,0x0008
#		blt $s0,8,lrputz
#		sll $s2,$s2,1
#		j lend
#lrputz:sll $s2,$s2,1
#		ori $s2,$s2,0x0001
#len	d:	sw $s2,LATE($s1)
#		li $a0,666
#		jal delay
#		j lrjfor
#		# Left/Right Ring counter
#		# Read RB1
lrrfor:	lw $s2,PORTB($s1)
		andi $s0,$s2,0x0002
		lw $s2,LATE($s1)
		beq $s0,2,right
		andi $s2,$s2,0x000F
		sll $s2,$s2,1
		beqz $s2,add1
		j rcend
add1:	ori $s2,$s2,0x0001
		j rcend
right:	andi $s2,$s2,0x000F
		srl $s2,$s2,1
 		beqz $s2,add8
		j rcend
add8:	ori $s2,$s2,0x0008
rcend:	sw $s2,LATE($s1)
		li $a0,333
		jal delay
		j lrrfor
		lw $ra,0($sp)
		lw $s0,4($sp)
		lw $s1,8($sp)
		lw $s2,12($sp)
		lw $s3,16($sp)
		addiu $sp,$sp,20

delay:  addiu $sp,$sp,-4
        sw $ra,0($sp)
dfor:   blez $a0,enddf
        li $v0,RESET_CORE_TIMER
        syscall
dwhile: li $v0,READ_CORE_TIMER
        syscall
        blt $v0,20000,dwhile
		addiu $a0,$a0,-1
		j dfor
enddf:  lw $ra,0($sp)
        addiu $sp,$sp,4
        jr $ra
