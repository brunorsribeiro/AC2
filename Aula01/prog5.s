        .equ STR_MAX_SIZE,20
        .equ printInt,6
        .equ printInt10,7
        .equ printStr,8
        .equ readStr,9
        .data
str1:   .space (STR_MAX_SIZE+1)
str2:   .space (STR_MAX_SIZE+1)
str3:   .space (2*STR_MAX_SIZE+1)
str4:   .asciiz "Introduza 2 strings: "
str5:   .asciiz "Resultados:\n"
        .text
        .globl main
main:   addiu $sp,$sp,-8
        sw $ra,0($sp)
        sw $s0,4($sp)
        ori $v0,$0,printStr
        la $a0,str4
        syscall
        ori $v0,$0,readStr
        la $a0,str1
        li $a1,STR_MAX_SIZE
        syscall
        la $a0,str2
        syscall
        ori $v0,$0,printStr
        la $a0,str5
        syscall
        la $a0,str1
        jal strlen
        or $a0,$v0,$0
        li $a1,10
        ori $v0,$0,printInt
        syscall
        la $a0,str2
        jal strlen
        or $a0,$v0,$0
        li $a1,10
        ori $v0,$0,printInt
        syscall
        la $a0,str3
        la $a1,str1
        jal strcpy
        la $a0,str3
        la $a1,str2
        jal strcat
        or $a0,$v0,$0
        ori $v0,$0,printStr
        syscall
        la $a0,str1
        la $a2,str2
        jal strcmp
        or $a0,$v0,$0
        ori $v0,$0,printInt10
        syscall
        ori $v0,$0,0
        lw $ra,0($sp)
        lw $s0,4($sp)
        addiu $sp,$sp,8
        jr $ra

strlen: ori $v0,$0,0
lenfor: lb $t0,0($a0)
        beqz $t0,endlf
        addi $a0,$a0,1
        addi $v0,$v0,1
        j lenfor
endlf:  jr $ra

strcpy: or $v0,$a0,$0
cpyfor: lb $t0,0($a1)
        sw $t0,0($a0)
        beqz $t0,ecpyf
        addi $a0,$a0,1
        addi $a1,$a1,1
        j cpyfor
ecpyf:  jr $ra

strcat: addiu $sp,$sp,-8
        sw $ra,0($sp)
        sw $a0,4($sp)
catfor: lb $t0,0($a0)
        beqz $t0,ecatf
        addi $a0,$a0,1
        j catfor
ecatf:  jal strcpy
        lw $ra,0($sp)
        lw $a0,4($sp)
        addiu $sp,$sp,8
        or $v0,$a0,$0
        jr $ra

strcmp: lb $t0,0($a0)
        lb $t1,0($a1)
        bne $t0,$t1,end
        beqz $t0,end
        addi $a0,$a0,1
        addi $a1,$a1,1
        j strcmp
end:    sub $v0,$t0,$t1
        jr $ra
