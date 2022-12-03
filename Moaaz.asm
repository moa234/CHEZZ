include macros.inc
include pieces.inc
.model small
.data
num dw 3456
mes db 'This is message','$'
InDATA db 6,?,6 dup('$')
Innum db 5,?,4 dup('$')

.code
main proc far
    ;set ds
    mov ax,@data
    mov ds,ax
    
    GraphicsMode
    mov ax,0700h
    mov bh,07h
    mov cx,0
    mov dx,1827H
    int 10h
    ;mov ah,0ch
    ;mov cx,8
    ;mov dx,5
    ;mov al,1
    ;int 10h
    DrawKnight 30225,9h,1h
    DrawKnight 30100,0ch,4h
    DrawRook 30125,9h,1h
    DrawRook 30150,0ch,4h
    DrawPawn 30175,9h,1h
    DrawPawn 30200,0ch,4h
    

    ReadString InDATA

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main