        .equ    PRINT_STR,8
        .equ    INKEY,1
        .data
str:    .asciiz "Key pressed\n"
        .text
        .globl main
main:   addiu $sp,$sp,-8
        sw $ra,0($sp)
        sw $s0,4($sp)
while:  ori $v0,$0,INKEY
        syscall
        beq $v0,0,while
        beq $v0,'\n',end
        la $a0,str
        ori $v0,$0,PRINT_STR
        syscall
        j while
end:    ori $v0,$0,1
        lw $ra,0($sp)
        lw $s0,4($sp)
        addiu $sp,$sp,4
        ori $v0,$0,1
        jr $ra
