.globl f

f:                                     # int f(int x, int y){
    movl 4(%esp), %ecx                 # int c = x;
    movl 8(%esp), %edx                 # int d = y
    decl %edx                          # d = d - 1 
    imull %edx, %ecx                   # c = c * d;
    subl $4, %ecx                      # c = c - 4;
    addl 8(%esp), %ecx                 # c = c + y;  
    movl %ecx, %eax
    ret                                # return c; 
