.code
drawboostat MACRO x,y 
    mov cx,x
    mov dx,y
    mov al,0eh
    mov ah,0ch;draw pixel command
    back1:
    int 10h
    inc cx
    inc dx
    mov di,10
    add di,x
    cmp cx,di
    jnz back1;to draw the 1st diagonal line from top left to bottom rigth
    dec cx
    back2:
    int 10h
    dec cx
    cmp cx,x
    jne back2;to draw the lower horizontal line  
    inc cx
    dec dx
    back3:
    int 10h
    inc cx
    dec dx
    mov di,10
    add di,x
    cmp cx,di
    jnz back3;to draw 2nd diagonal line from bottom left to top right
    dec cx
    back4:
    int 10h
    dec cx
    mov di,1
    add di,x
    cmp cx,di
    jge back4;to draw the upper horizontal line 
    
    mov di,5
    add di,x
    cmp cx,di
    mov di,5
    add di,y
    cmp dx,di
    back5:
    int 10h
    inc dx
    inc dx
    inc dx 
    mov di,10
    add di,y
    cmp dx,di
    jle back5;to draw the dotted line
    
ENDM drawboostat