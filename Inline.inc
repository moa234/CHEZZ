.code
inlinechatinitialize proc

    MOVECURSORINinline 0e19h
    DisplayString inlineNotfline

    MOVECURSORINinline 0619h
    DisplayString myplayer+2
    DisplayChar ":"
    mov thiscurs, 0719h

    MOVECURSORINinline 0f19h
    DisplayString opponentplayer+2
    DisplayChar ":"
    mov thatcurs, 1019h
    clearbuffer
    ret

inlinechatinitialize endp

inlinesendchat proc
    ;check last column to in chat to scroll
    cmp byte ptr [thiscurs]+1, 0eh
    jnz noscroll@inline
    scrollup 0719h,0d39h
    mov thiscurs, 0d19h
    noscroll@inline:

    ;move the cursor to next location of printing
    MOVECURSORINinline thiscurs

    ;check if key entered is enter to go to next line
    cmp bufferascii,0dh ;enter
    jz displayenter@inline

    ;check if key entered is backspace to delete last character
    cmp bufferascii,08h ;backspace
    jz backspace@inline

    ;display the character on the screen
    DisplayChar bufferascii
    
    ;move the cursor to next location of printing
    ;check if the cursor is at the end of the line
    ;if yes, move it to the next line
    ;if no, move it to the next column
    inc thiscurs
    cmp byte ptr [thiscurs], 40
    jnz endofline@inline
    displayenter@inline:
    mov byte ptr [thiscurs], 25
    add byte ptr [thiscurs]+1, 1
    endofline@inline:
    ret
    ;deletes the last character
    ;moves the cursor to the last character 
    ;does not go to previous line
    ;deletes by displaying null character at position of last character
    backspace@inline:
        dec thiscurs
        cmp byte ptr [thiscurs], 24
        jnz endofline2@inline
        ;dec byte ptr [thiscurs]+1             ;to go to the previous line if needed
        mov byte ptr [thiscurs], 25
    endofline2@inline:
        MOVECURSORINinline thiscurs
        DisplayChar 0

    ret
inlinesendchat endp

inlinerecievechat proc    

    cmp byte ptr [thatcurs]+1, 17h
    jnz noscroll@recieve@inline
    scrollup 1019h,1639h
    mov thatcurs, 1619h
    noscroll@recieve@inline:

    MOVECURSORINinline thatcurs

    cmp bufferascii,0dh ;enter
    jz displayenter@recieve@inline

    cmp bufferascii,08h ;backspace
    jz backspace@recieve@inline

    DisplayChar bufferascii
    
    inc thatcurs
    cmp byte ptr [thatcurs], 40
    jnz endofline@recieve@inline
    displayenter@recieve@inline:
    mov byte ptr [thatcurs], 25
    add byte ptr [thatcurs]+1, 1
    endofline@recieve@inline:
    ret 

    backspace@recieve@inline:
        dec thatcurs
        cmp byte ptr [thatcurs], 24
        jnz endofline2@recieve@inline
        ;dec byte ptr [thiscurs]+1             ;to go to the previous line if needed
        mov byte ptr [thatcurs], 25
    endofline2@recieve@inline:
        MOVECURSORINinline thatcurs
        DisplayChar 0
    ret
inlinerecievechat endp
