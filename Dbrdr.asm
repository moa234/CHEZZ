.Model SMALL
.STACK 64
.Data

.code
drawborderat MACRO x,y
    local back
    local back2
    local back3
    local back4
    mov cx,x
    mov dx,y
    mov al,0bh;white colour
    mov ah,0ch
    back:
    int 10h
    inc cx
    cmp cx,x+25
    jnz back
    ;;;;;;;;;;;
    mov cx,x
    mov dx,y+25
    back2:
    int 10h
    inc cx
    cmp cx,x+25
    jnz back2
    ;;;;;;;;;;;;;
    mov cx,x
    mov dx,y
    back3:
    int 10h
    inc dx
    cmp dx,y+25
    jnz back3
    ;;;;;;;;;;;;
    mov cx,x+25
    mov dx,y
    back4:
    int 10h
    inc dx
    cmp dx,y+26
    jnz back4
    
ENDM drawborderat

Main proc far
    mov ax,@data
    mov ds,ax 
    mov ah, 0
    mov al, 13h
    int 10h
    drawborderat 75,50
    drawborderat 50,50
    drawborderat 0,0
    drawborderat 125,50
    drawborderat 50,0
    drawborderat 150,0


    mov ah,4ch
    mov al,01
    int 21h
    Main ENDP
End Main