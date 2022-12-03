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
    mov bh,0fh
    mov cx,0
    mov dx,1827H
    int 10h
    ;mov ah,0ch
    ;mov cx,8
    ;mov dx,5
    ;mov al,1
    ;int 10h
    DrawKnight 0,9h,1h
    DrawKnight 25,0ch,4h
    DrawRook 50,9h,1h
    DrawRook 75,0ch,4h
    DrawPawn 100,9h,1h
    DrawPawn 125,0ch,4h
    DrawBishop 150,9h,1h
    DrawBishop 175,0ch,4h
    DrawQueen 200,9h,1h
    DrawQueen 225,0ch,4h
    DrawKing 250,9h,1h
    DrawKing 275,0ch,4h
    

    ReadString InDATA

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main