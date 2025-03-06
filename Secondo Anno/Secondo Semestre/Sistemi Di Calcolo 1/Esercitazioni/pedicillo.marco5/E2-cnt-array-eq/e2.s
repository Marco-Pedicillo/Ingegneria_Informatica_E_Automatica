.globl counteq
counteq:
    pushl %esi
    pushl %edi
    pushl %ebx
    pushl %ebp
    movl 20(%esp), %ebp
    movl 24(%esp), %ebx
    movl 28(%esp), %esi
    xorl %edi, %edi
    xorl %eax, %eax
L:
    cmpl %esi, %edi
    jge E
    movw (%ebp ,%edi, 2), %dx
    cmpw %dx, (%ebx, %edi, 2)
    sete %cl
    movsbl %cl, %ecx
    addl %ecx, %eax
    incl %edi
    jmp L
E:
    popl %ebp
    popl %ebx
    popl %edi
    popl %esi
    ret

    
