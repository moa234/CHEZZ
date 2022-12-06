include macros.inc
.model small
.286
.stack 64

.data
NotifLine db   "________________________________________________________________________________$"
player1 db "moaaz$"
player2 db "malek$"
thiscurs dw 0
thatcurs dw 0
chatendflag db 0
bufferascii db 0
bufferscancode db 0
WelcomeMessage db "Welcome to the chat room!$"

.code
main proc far
    mov ax, @data
    mov ds, ax

    
    call chat

    MOV AH, 4CH
    MOV AL, 00 ;your return code.
    INT 21H
main endp

chat proc
    call chatinitialize

    chatting:
        call sendchat
       ; call recievechat
        cmp chatendflag, 0
    je chatting
    
    mov chatendflag,0

    ret
chat endp

chatinitialize proc

    TEXTMODE
    SelectVideoPage 1
    clearscreen

    MOVECURSORINCHAT 0C00h
    DisplayString NotifLine

    MOVECURSORINCHAT 0001h
    DisplayString player1
    DisplayChar ":"
    mov thiscurs, 0106h

    MOVECURSORINCHAT 0D01h
    DisplayString player2
    DisplayChar ":"
    mov thatcurs, 0E06h

    clearbuffer
    ret

chatinitialize endp

sendchat proc
    
    MOVECURSORINCHAT thiscurs
    GetKeyPress
    mov bufferscancode, AH
    mov bufferascii, AL
    clearbuffer
    jz nokey
    
    cmp bufferscancode,3dh
    jz endchat

    cmp bufferascii,0dh ;enter
    jz displayenter

    DisplayChar bufferascii
    
    inc thiscurs
    cmp byte ptr [thiscurs], 80
    jnz endofline
    displayenter:
    mov byte ptr [thiscurs], 6
    add byte ptr [thiscurs]+1, 1
    endofline:

    ;TODO: send to other player
    jmp nokey

    endchat:
        mov chatendflag,1
    nokey:
    ret
sendchat endp

end main
