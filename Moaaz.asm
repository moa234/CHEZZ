include macros.inc
include pieces.inc
.model small
.286
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
    mov bh,7h
    mov cx,0
    mov dx,1827H
    int 10h
    ;mov ah,0ch
    ;mov cx,8
    ;mov dx,5
    ;mov al,1
    ;int 10h
    DrawRook 0,9h,1h
    DrawKnight 25,9h,1h
    DrawBishop 50,9h,1h
    DrawQueen 75,9h,1h
    DrawKing 100,9h,1h
    DrawBishop 125,0ch,4h
    DrawKnight 150,0ch,4h
    DrawRook 175,0ch,4h
    DrawPawn 200,9h,1h
    DrawPawn 225,0ch,4h
    DrawQueen 250,0ch,4h
    DrawKing 275,0ch,4h
    DisplayString mes
    

    ReadString InDATA

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main