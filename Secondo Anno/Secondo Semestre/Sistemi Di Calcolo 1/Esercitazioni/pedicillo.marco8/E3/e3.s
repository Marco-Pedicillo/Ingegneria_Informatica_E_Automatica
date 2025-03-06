.globl count_digits
count_digits:
    xorl %eax, %eax
    movl 4(%esp), %ecx
L:
    movb (%ecx), %ah
    testb %ah, %ah
    je E
    cmpb $48, %ah
    jl L1
    cmpb $57, %ah
    jg L1
    incl %eax
L1:
    incl %ecx
    jmp L
E:
    ret
        
