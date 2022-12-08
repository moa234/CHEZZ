

.model small
.286
.data
num dw 3456
mes db 'This is message','$'
InDATA db 6,?,6 dup('$')
Innum db 5,?,4 dup('$')
currpos dw 0

include pieces.inc
include macros.inc
include gameui.inc
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

    call initializegame
    

    ReadString InDATA

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main