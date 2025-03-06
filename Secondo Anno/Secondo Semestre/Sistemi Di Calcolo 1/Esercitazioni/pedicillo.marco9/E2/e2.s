.globl crc32b
crc32b:
    pushl %ebx
    pushl %edi
    pushl %esi
    pushl %ebp
    subl $12, %esp
    xorl %ebp, %ebp
    notl %ebp
    movl %ebp, %edi
    movl 32(%esp), %esi
    movl 36(%esp), %ebx
L:
    cmpl $0, %ebx
    jle E
    decl %ebx
    movb (%esi), %cl
    movsbl %cl, %ecx
    incl %esi
    xorl %edi, %ecx
    andl $0xFF, %ecx
    leal 8(%esp), %eax
    movl %eax, (%esp)
    movl %ecx, 4(%esp)
    call get_constant
    sarl $8, %edi
    xorl 8(%esp), %edi
    jmp L
E:
    xorl %edi, %ebp
    movl %ebp, %eax
    addl $12, %esp
    popl %ebp
    popl %esi
    popl %edi
    popl %ebx
    ret

    
