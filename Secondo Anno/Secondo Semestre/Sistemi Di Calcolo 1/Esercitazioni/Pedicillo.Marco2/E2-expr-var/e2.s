.global f
f:
    movl 4(%esp), %eax
    imull 4(%esp), %eax
    imull $2, %eax
    movl 4(%esp), %ecx
    imull $7, %ecx
    subl %ecx, %eax
    incl %eax
    ret

    
