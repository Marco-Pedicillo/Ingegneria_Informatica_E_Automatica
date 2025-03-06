.globl fib

fib:
    movl 4(%esp), %eax
    movl $0, %ecx
    movl $1, %edx
    test %eax, %eax
    jne L
    movl %ecx, %eax
    ret
L:
    cmpl $1, %eax
    jne L2
    movl %edx, %eax
    ret
L2:
    cmpl $1, %eax
    jbe L3
    addl %edx, %ecx
    addl %edx, %ecx
    negl %edx
    addl %ecx, %edx
    subl %edx, %ecx
    decl %eax
    jmp L2
L3:
    movl %edx, %eax
    ret
