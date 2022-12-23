.model small
.286
.data
sentdata dw 0

.code
include macros.inc
main proc far
    mov ax, @data
    mov ds, ax
    initializeserial
    wiletrue:
    recieveserialword sentdata
    jmp wiletrue
    MOV AH, 4CH
    MOV AL, 00 ;your return code.
    INT 21H
main endp
end main