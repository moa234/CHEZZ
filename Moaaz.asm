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
    mov bh,00h
    mov cx,0
    mov dx,1827H
    int 10h
    ;mov ah,0ch
    ;mov cx,8
    ;mov dx,5
    ;mov al,1
    ;int 10h
    DrawRook 32150,9h,1h
    DrawRook 30000,0ch,4h
    DrawRook 10000,0Dh,5h
    DrawRook 20000,0Bh,3h
    DrawRook 40000,0Ah,2h
    DrawRook 25000,0Eh,6h
    DrawRook 35000,0Fh,7h
    

    ReadString InDATA

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main