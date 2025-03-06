.globl find
find:
    movl 4(%esp), %ecx
    movl 12(%esp), %edx
    movl $0, %eax
L:
    cmpl 8(%esp), %eax
    jge E
    cmpl %edx, (%ecx, %eax,4)
    jne L2
    movl $1, %eax
    jmp E1
L2:
    incl %eax
    jmp L
E:
    xorl %eax, %eax
E1:
    ret
    
