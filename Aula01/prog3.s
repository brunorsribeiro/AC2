        .equ getChar,2
        .equ putChar,3
        .data
        .text
        .globl main
main:   ori $v0,$0,getChar
        syscall
        beq $v0,'\n',end
        or $a0,$0,$v0
        ori $v0,$0,putChar
        syscall
        j main
end:    ori $v0,$0,1
        jr $ra
