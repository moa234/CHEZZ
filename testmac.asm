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
    
    clearscreen
    GraphicsMode
    ;mov ah,0ch
    ;mov cx,8
    ;mov dx,5
    ;mov al,1
    ;int 10h
    DrawRook 0,0

    ReadString InDATA

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main