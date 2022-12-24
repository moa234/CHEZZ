.Model SMALL
.STACK 64
.Data 
.code
drawboostat MACRO x,y 
    mov cx,x
    mov dx,y
    mov al,0fh
    mov ah,0ch;draw pixel command
    back1:
    int 10h
    inc cx
    inc dx
    cmp cx,x+32
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
    cmp cx,x+32
    jnz back3;to draw 2nd diagonal line from bottom left to top right
    dec cx
    back4:
    int 10h
    dec cx
    cmp cx,x+1
    jge back4;to draw the upper horizontal line 
    
    mov cx,x+16
    mov dx,y+16 
    back5:
    int 10h
    inc dx
    inc dx
    inc dx 
    cmp dx,y+32 
    jle back5;to draw the dotted line
    
    
ENDM drawboostat


Main proc far
    mov ax,@data
    mov ds,ax 
    mov ah,0
    mov al,13h
    int 10h;change to video mode
    
    drawboostat 20,120
    
    
    
  
    Main ENDP
End Main
    