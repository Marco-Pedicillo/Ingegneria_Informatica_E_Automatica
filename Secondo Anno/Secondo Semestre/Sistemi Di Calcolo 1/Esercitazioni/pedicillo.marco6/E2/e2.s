.globl list_equal
list_equal:
    pushl %ebx
    pushl %esi
    movl 12(%esp), %ecx
    movl 16(%esp), %edx
L:
    testl %ecx, %ecx
    je E
    testl %edx, %edx
    je E
    movw (%ecx), %si
    movw (%edx), %bx
    cmpw %si, %bx
    jne L1
    movl 4(%ecx), %ecx
    movl 4(%edx), %edx
    jmp L
L1:
    xorl %eax, %eax
    jmp A
E:
    testl %ecx, %ecx
    jne L1
    testl %edx, %edx
    jne L1
    movl $1, %eax
A:
    popl %esi
    popl %ebx
    ret
