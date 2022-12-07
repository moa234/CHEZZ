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
    SelectVideoPage 2
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

    cmp byte ptr [thiscurs]+1, 0ch
    jnz noscroll
    scrollup 0100h,0b79h
    mov thiscurs, 0b06h
    noscroll:

    MOVECURSORINCHAT thiscurs
    GetKeyPress
    jnz nokey
    ret
    nokey:
    mov bufferscancode, AH
    mov bufferascii, AL
    clearbuffer
    
    
    cmp bufferscancode,3dh
    jz endchat

    cmp bufferascii,0dh ;enter
    jz displayenter

    cmp bufferascii,08h ;backspace
    jz backspace

    DisplayChar bufferascii
    
    inc thiscurs
    cmp byte ptr [thiscurs], 80
    jnz endofline
    displayenter:
    mov byte ptr [thiscurs], 6
    add byte ptr [thiscurs]+1, 1
    endofline:
    ret 

    backspace:
        dec thiscurs
        cmp byte ptr [thiscurs], 5
        jnz endofline2
        ;dec byte ptr [thiscurs]+1             ;to go to the previous line if needed
        mov byte ptr [thiscurs], 6
    endofline2:
        MOVECURSORINCHAT thiscurs
        DisplayChar 0
    ret

    ;TODO: send to other player
    
    ;check cursor to scroll
    

    endchat:
        mov chatendflag,1
    ret
sendchat endp

end main
