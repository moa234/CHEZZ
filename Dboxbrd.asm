.Model SMALL
.STACK 64
.Data

.code
drawboxat MACRO x,y,colour
    local back
    local back2
    mov cx,x
    mov dx,y
    mov al,colour;white colour
    mov ah,0ch
    back2: 
    back:
    int 10h
    inc cx
    cmp cx,25+x
    jnz back
    mov cx,x
    inc dx
    cmp dx,25+y
    jnz back2
ENDM drawboxat



Main proc far
    mov ax,@data
    mov ds,ax 
    mov ah, 0
    mov al, 13h
    int 10h

    drawboxat 0,0,0fh
    drawboxat 25,0,7h
    drawboxat 50,0,0fh
    drawboxat 75,0,7h
    drawboxat 100,0,0fh
    drawboxat 125,0,7h
    drawboxat 150,0,0fh
    drawboxat 175,0,7h
    ;;;;;;;;;;;;;;;;
    drawboxat 0,25,7h
    drawboxat 25,25,0fh
    drawboxat 50,25,7h
    drawboxat 75,25,0fh
    drawboxat 100,25,7h
    drawboxat 125,25,0fh
    drawboxat 150,25,7h
    drawboxat 175,25,0fh
    ;;;;;;;;;;;;;;;
    drawboxat 0,50, 0fh
    drawboxat 25,50,7h
    drawboxat 50,50,0fh
    drawboxat 75,50,7h
    drawboxat 100,50,0fh
    drawboxat 125,50,7h
    drawboxat 150,50,0fh
    drawboxat 175,50,7h
    ;;;;;;;;;;;;;;;;
    drawboxat 0,75,7h
    drawboxat 25,75,0fh
    drawboxat 50,75,7h
    drawboxat 75,75,0fh
    drawboxat 100,75,7h
    drawboxat 125,75,0fh
    drawboxat 150,75,7h
    drawboxat 175,75,0fh
    ;;;;;;;;;;;;;;;
    drawboxat 0,100,0fh
    drawboxat 25,100,7h
    drawboxat 50,100,0fh
    drawboxat 75,100,7h
    drawboxat 100,100,0fh
    drawboxat 125,100,7h
    drawboxat 150,100,0fh
    drawboxat 175,100,7h
    ;;;;;;;;;;;;;;;;
    drawboxat 0,125,7h
    drawboxat 25,125,0fh
    drawboxat 50,125,7h
    drawboxat 75,125,0fh
    drawboxat 100,125,7h
    drawboxat 125,125,0fh
    drawboxat 150,125,7h
    drawboxat 175,125,0fh
    ;;;;;;;;;;;;;;;;;
    drawboxat 0,150,0fh
    drawboxat 25,150,7h
    drawboxat 50,150,0fh
    drawboxat 75,150,7h
    drawboxat 100,150,0fh
    drawboxat 125,150,7h
    drawboxat 150,150,0fh
    drawboxat 175,150,7h
    ;;;;;;;;;;;;;;;;
    drawboxat 0,175,7h
    drawboxat 25,175,0fh
    drawboxat 50,175,7h
    drawboxat 75,175,0fh
    drawboxat 100,175,7h
    drawboxat 125,175,0fh
    drawboxat 150,175,7h
    drawboxat 175,175,0fh
    
    
    mov ah,4ch
    mov al,01
    int 21h
    Main ENDP
End Main
    