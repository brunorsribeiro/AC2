        .equ PUT_CHAR,3
        .equ RESET_CORE_TIMER,12
        .equ READ_CORE_TIMER,11
        .data
        .text
        .globl main
main:   addiu $sp,$sp,-8
        sw $ra,0($sp)
        sw $s0,4($sp)
        or $s0,$0,$0
for:    bgt $s0,100,endf
        li $a0,1000
        jal delay
        li $a0,'K'
        li $v0,PUT_CHAR
        syscall
        li $a0,' '
        li $v0,PUT_CHAR
        syscall
        addi $s0,$s0,1
        j for
endf:   lw $ra,0($sp)
        lw $s0,4($sp)
        addiu $sp,$sp,8
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
