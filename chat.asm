include macros.inc
.model small
.286
.stack 64

.data
NotifLine db   "________________________________________________________________________________$"
player1 db "moaaz$"
player2 db "marwan$"
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

    ;------------------------------
    ;initialze port
    mov dx,3FbH         
    mov al,10000000b
    out dx,al

    mov dx,3f8h
    mov al,0ch
    out dx,al

    mov dx,3f9h
    mov al,00h
    out dx,al

    ;configuration
    mov dx,3fbh
    mov al,00011011b
    out dx,al
    ;--------------------------

    call chat

    MOV AH, 4CH
    MOV AL, 00 ;your return code.
    INT 21H
main endp

chat proc
    call chatinitialize

    chatting:
        call sendchat
        call recievechat
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
    jnz key
    ret
    key:
    mov bufferscancode, AH
    mov bufferascii, AL
    clearbuffer
    
    
    cmp bufferscancode,3dh ;f3
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
    jmp sendchatserial

    backspace:
        dec thiscurs
        cmp byte ptr [thiscurs], 5
        jnz endofline2
        ;dec byte ptr [thiscurs]+1             ;to go to the previous line if needed
        mov byte ptr [thiscurs], 6
    endofline2:
        MOVECURSORINCHAT thiscurs
        DisplayChar 0
    
    sendchatserial:
    ;TODO: send to other player

    ;check if can send by checking if the register is empty
    mov dx,3FDH
    in al,dx
    and al,00100000b
    jnz idk3
    ret

    idk3:

    ;transmits the data
    mov dx,3f8h
    mov al,bufferascii
    out dx,al

    ret

    endchat:
        mov chatendflag,1
    ret
sendchat endp

recievechat proc    

    mov dx,3FDH
    in al , dx 
    and al,1
    jnz continue@receiving
    ret
    ;recieve data
    continue@receiving:
    mov dx,3f8h
    in al,dx
    mov bufferascii,al

    cmp byte ptr [thatcurs]+1, 19h
    jnz noscroll@recieve
    scrollup 0e00h,1879h
    mov thatcurs, 1806h
    noscroll@recieve:

    MOVECURSORINCHAT thatcurs
    
    
    ; cmp bufferscancode,3dh ;f3
    ; jz endchat@recieve

    cmp bufferascii,0dh ;enter
    jz displayenter@recieve

    cmp bufferascii,08h ;backspace
    jz backspace@recieve

    DisplayChar bufferascii
    
    inc thatcurs
    cmp byte ptr [thatcurs], 80
    jnz endofline@recieve
    displayenter@recieve:
    mov byte ptr [thatcurs], 6
    add byte ptr [thatcurs]+1, 1
    endofline@recieve:
    ret 

    backspace@recieve:
        dec thatcurs
        cmp byte ptr [thatcurs], 5
        jnz endofline2@recieve
        ;dec byte ptr [thiscurs]+1             ;to go to the previous line if needed
        mov byte ptr [thatcurs], 6
    endofline2@recieve:
        MOVECURSORINCHAT thatcurs
        DisplayChar 0
    ret

    endchat@recieve:
        mov chatendflag,1
    ret
recievechat endp



end main
