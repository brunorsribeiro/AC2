        .equ READ_CORE_TIMER,11
        .equ RESET_CORE_TIMER,12
        .equ PUT_CHAR,3
        .equ PRINT_INT,6
        .data
        .text
        .globl main
main:   ori $t0,$0,0
while:  ori $v0,READ_CORE_TIMER
#        syscall
        bge $v0,200000,endw
        j while
endw:   ori $v0,$0,RESET_CORE_TIMER
        syscall
        li $a0,32
        ori $v0,$0,PUT_CHAR
        syscall
        addi $t0,$t0,1
        or $a0,$t0,$0
        ori $a1,$0,10
        ori $v0,$0,PRINT_INT
        syscall
        jr $ra
