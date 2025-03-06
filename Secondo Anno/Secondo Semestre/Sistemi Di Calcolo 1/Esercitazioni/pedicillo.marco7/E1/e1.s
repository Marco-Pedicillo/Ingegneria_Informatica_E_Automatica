.globl binsearch
binsearch:
    pushl %ebx
    pushl %esi
    pushl %edi
    pushl %ebp
    xorl %ecx, %ecx
    movl 20(%esp), %edi
    movl 24(%esp), %esi
    movl 28(%esp), %ebx
L:
    cmpl %esi, %ecx
    jge E
    leal (%ecx, %esi), %edx
    sarl %edx
    movl (%edi, %edx, 4), %ebp
    cmpl %ebx, %ebp
    jne L1
    movl $1, %eax
    jmp R
L1:
    cmpl %ebx, %ebp
    jle L2
    movl %edx, %esi
L2:
    incl %edx
    movl %edx, %ecx
    jmp L
E:
    xorl %eax, %eax
R:
    popl %ebp
    popl %edi
    popl %esi
    popl %ebx
    ret

    


        
