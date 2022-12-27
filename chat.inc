.code
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

    SelectVideoPage 2
    clearscreen

    MOVECURSORINCHAT 0C00h
    DisplayString NotifLine

    MOVECURSORINCHAT 0001h
    DisplayString myplayer+2
    DisplayChar ":"
    mov thiscurs, 0106h

    MOVECURSORINCHAT 0D01h
    DisplayString opponentplayer+2
    DisplayChar ":"
    mov thatcurs, 0E06h
    initializeserial
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
    jnz key
    ret
    key:
    mov bufferscancode, AH
    mov bufferascii, AL
    clearbuffer
    
    ;check if key entered is f3 to end chat
    ;makes endchat flag to 1 to end the chat
    cmp bufferscancode,3dh ;f3
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
    jmp sendchatserial

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
    
    sendchatserial:

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
        sendserial 3dh
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
    
    
    cmp bufferascii,3dh ;f3
    jz endchat@recieve


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
