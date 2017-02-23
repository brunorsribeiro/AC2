        .equ RESET_CORE_TIMER,12
        .equ READ_CORE_TIMER,11
        .equ PRINT_INT,6
        .equ PUT_CHAR,3
        .data
        .text
        .globl main
        # 2Hz 0.5s 500ms
main:   addiu $sp,$sp,-4
        sw $ra,0($sp)
loop:   lui $t1,0xBF88
        lw $t2,0x6050($t1)
        and $t2,$t2,0x0f
        or $a0,$t2,$0
        li $a1,0x00040002
        li $v0,PRINT_INT
        syscall
        li $a0,'\n'
        li $v0,PUT_CHAR
        syscall
        sub $t2,$0,$t2
        addi $t2,$t2,16
        mul $t2,$t2,64
        or $a0,$t2,$0
        jal delay
        j loop
        lw $ra,0($sp)
        jr $ra


delay:  addiu $sp,$sp,-4
        sw $ra,0($sp)
        mul $t0,$a0,20000
dfor:   blez $a0,enddf
        li $v0,RESET_CORE_TIMER
        syscall
dwhile: li $v0,READ_CORE_TIMER
        syscall
        blt $v0,$t0,dwhile
enddf:  lw $ra,0($sp)
        addiu $sp,$sp,4
        jr $ra
