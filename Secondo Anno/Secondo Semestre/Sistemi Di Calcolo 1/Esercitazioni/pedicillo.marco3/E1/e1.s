.globl min

min:
    movl 4(%esp), %eax
    movl 8(%esp), %ecx
    movl 12(%esp), %edx
    cmpl %ecx, %eax
    jge L
    cmpl %edx, %eax
    jge L4
    jmp L5
L:
    cmpl %edx, %ecx
    jge L2
    jmp L3
L2:
    movl 12(%esp), %eax
    ret
L3:
    movl 8(%esp), %eax
    ret
L4:
    movl 12(%esp), %eax
    ret
L5:
    ret

    

    
