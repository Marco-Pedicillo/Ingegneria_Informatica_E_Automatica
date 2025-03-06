.globl fib
fib:
    pushl %esi
    pushl %ebx
    subl $4, %esp
    movl 16(%esp), %esi
    cmpl $2, %esi
    jge L
    movl $1, %eax
    jmp E
L:
    decl %esi
    movl %esi, (%esp)
    call fib 
    movl %eax, %ebx
    decl %esi
    movl %esi, (%esp)
    call fib
    addl %eax, %ebx
    movl %ebx, %eax
E:
    addl $4, %esp
    popl %ebx
    popl %esi
    ret

    
        
