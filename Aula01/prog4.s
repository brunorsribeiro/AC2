        .equ printStr,8
        .equ printInt,6
        .equ readInt10,5
        .equ printInt10,7
        .data
str1:   .asciiz "\nIntroduza um numero (sinal e módulo): "
str2:   .asciiz "\nValor lido em base 2: "
str3:   .asciiz "\nValor lido em base 16: "
str4:   .asciiz "\nValor lido em base 10 (unsigned): "
str5:   .asciiz "\nValor lido em base 10 (signed): "
        .text
        .globl main
main:   addiu $sp,$sp,-4
        sw $ra,0($sp)
        la $a0,str1
        ori $v0,$0,printStr
        syscall
        ori $v0,$0,readInt10
        syscall
        or $t0,$v0,$0
        la $a0,str2
        ori $v0,$0,printStr
        syscall
        or $a0,$t0,$0
        li $a1,2
        ori $v0,$0,printInt
        syscall
        la $a0,str3
        ori $v0,$0,printStr
        syscall
        ori $v0,$0,printInt
        or $a0,$0,$t0
        li $a1,16
        syscall
        la $a0,str4
        ori $v0,$0,printStr
        syscall
        ori $v0,$0,printInt
        or $a0,$t0,$0
        li $a1,10
        syscall
        la $a0,str5
        ori $v0,$0,printStr
        syscall
        ori $v0,$0,printInt10
        or $a0,$t0,$0
        syscall
        lw $ra,0($sp)
        addiu $sp,$sp,4
        ori $v0,$0,0
        jr $ra
