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
    ;check last column to in chat to scroll
    cmp byte ptr [thiscurs]+1, 0ch
    jnz noscroll
    scrollup 0100h,0b79h
    mov thiscurs, 0b06h
    noscroll:

    ;move the cursor to next location of printing
    MOVECURSORINCHAT thiscurs

    ;read key from user without waiting
    ;if no key is pressed, return
    ;if key is pressed, store it in variable
    ;then clear the buffer to read next key
    GetKeyPress
    jnz nokey
    ret
    nokey:
    mov bufferscancode, AH
    mov bufferascii, AL
    clearbuffer
    
    ;check if key entered is f3 to end chat
    ;makes endchat flag to 1 to end the chat
    cmp bufferscancode,3dh
    jz endchat

    ;check if key entered is enter to go to next line
    cmp bufferascii,0dh ;enter
    jz displayenter

    ;check if key entered is backspace to delete last character
    cmp bufferascii,08h ;backspace
    jz backspace

    ;display the character on the screen
    DisplayChar bufferascii
    
    ;move the cursor to next location of printing
    ;check if the cursor is at the end of the line
    ;if yes, move it to the next line
    ;if no, move it to the next column
    inc thiscurs
    cmp byte ptr [thiscurs], 80
    jnz endofline
    displayenter:
    mov byte ptr [thiscurs], 6
    add byte ptr [thiscurs]+1, 1
    endofline:
    ret 

    ;deletes the last character
    ;moves the cursor to the last character 
    ;does not go to previous line
    ;deletes by displaying null character at position of last character
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
    

    endchat:
        mov chatendflag,1
    ret
sendchat endp

end main
