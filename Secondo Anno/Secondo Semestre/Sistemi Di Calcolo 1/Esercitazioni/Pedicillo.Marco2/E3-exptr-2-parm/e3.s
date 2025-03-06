.global f
f:
    movl 4(%esp), %eax
    addl 8(%esp), %eax
    movl 4(%esp), %ecx
    subl 8(%esp), %ecx
    imull %ecx, %eax
    ret

    
