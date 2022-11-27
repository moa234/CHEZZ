include macros.inc
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
    
    DisplayNumber num
    
    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main