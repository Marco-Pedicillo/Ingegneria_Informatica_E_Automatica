.globl list_add_first
list_add_first:
    pushl %ebx
    pushl %esi
    subl $4, %esp
    movl $8, (%esp)
    call malloc
    movl %eax, %edx
    movl 16(%esp), %ecx
    movl (%ecx), %esi
    movw 20(%esp), %bx
L:
    testl %edx, %edx
    jne E
    movl $-1, %eax
    jmp A
E:
    movw %bx, (%edx)
    movl %esi,4(%edx)
    movl %edx, (%ecx)
    xorl %eax, %eax
A:
    addl $4, %esp
    popl %esi
    popl %ebx
    ret
        
