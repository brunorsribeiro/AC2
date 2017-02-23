        .equ READ_CORE_TIMER,11
        .equ RESET_CORE_TIMER,12
        .equ PUT_CHAR,3
        .equ PRINT_INT,6
        .data
        .text
        .globl main
main:   ori $t0,$0,0
while:  ori $v0,$0,READ_CORE_TIMER
        syscall
#       blt $v0,20000000,while          # 1Hz    1000 ms 1    s
#       blt $v0,4000000,while           # 5Hz    200 ms  0.2  s
#       blt $v0,2000000,while           # 10Hz   100 ms  0.1  s
#       blt $v0,200000,while            # 100Hz  10 ms   0.01 s
#       blt $v0,20000,while             # 1000Hz 1 ms    0.001s
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
        j while
        jr $ra
