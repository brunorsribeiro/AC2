	.equ RESET_CORE_TIMER,12
	.equ READ_CORE_TIMER,11
	.equ SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area
	.equ TRISE, 0x6100            # TRISE address is 0xBF886100
	.equ PORTE, 0x6110            # PORTE address is 0xBF886110
	.equ LATE,  0x6120            # LATE  address is 0xBF886120
	.data
	.text
	.globl main
main:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	ori $s0,$0,0
	lui $s1,SFR_BASE_HI
	# Set RE0 as Out
	lw $s2,TRISE($s1)
	andi $s2,$s2,0xFFFE
	sw $s2,TRISE($s1)
	#while 1
while:	lw $s2,LATE($s1)
	or $s2,$s0,$0
 	sw $s2,LATE($s1)
	# Uncoment ONE to set delay
	li $a0,500
#	li $a0,20
#	li $a0,10
	jal delay
	xori $s0,$s0,1
	j while
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	addiu $sp,$sp,16
	jr $ra

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
