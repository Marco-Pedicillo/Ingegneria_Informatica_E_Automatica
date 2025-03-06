.globl interleave
interleave:
    pushl %esi
    movl 8(%esp), %eax
    movl 12(%esp), %ecx
    movl 16(%esp), %esi
L1:
    movb (%eax), %dl
    testb %dl, %dl
    je L2
    movb %dl, (%esi)
    incl %esi
    incl %eax
L2:
    movb (%ecx), %dl
    testb %dl, %dl
    je L3
    movb %dl, (%esi)
    incl %esi
    incl %ecx
L3:
    cmpb $0, (%eax)
    jne L1
    cmpb $0, (%ecx)
    jne L1
    movb $0, (%esi)
    popl %esi
    ret

    
