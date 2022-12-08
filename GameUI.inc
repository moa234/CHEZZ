
.code

drawboxwhite proc
    pusha
    mov     ax,0A000h
    mov     es,ax
    
    cld

    MOV DI,currpos
    mov dx,25
    mov al,0fh

    back:
        mov cx,25
        rep stosb
        add di,320-25
        dec DX
    jnz back

    POPa

    ret
drawboxwhite ENDP

drawboxgrey proc
    pusha
    mov     ax,0A000h
    mov     es,ax
    
    cld

    MOV DI,currpos
    mov dx,25
    mov al,7h
    backgrey:
        mov cx,25
        rep stosb
        add di,320-25
        dec DX
    jnz backgrey

    popa
    ret
drawboxgrey ENDP

drawboard proc    

    rows:
        mov cx,4
        row1:
            call drawboxwhite
            add currpos,25
            call drawboxgrey
            add currpos,25
        loop row1

        mov cx,4
        add currpos,320*25-25*8
        row2:
            call drawboxgrey
            add currpos,25
            call drawboxwhite
            add currpos,25
        loop row2

        add currpos,320*25-25*8
        cmp currpos,320*25*8
    jnz rows
    
    ret
drawboard ENDP

initializegame proc
    
    GraphicsMode

    call drawboard
    call initializepieces

    ret
initializegame ENDP

initializepieces proc
    pusha

    mov currpos,0

    call DrawRookRed
    add currpos,25
    call DrawKnightRed
    add currpos,25
    call DrawBishopRed
    add currpos,25
    call DrawKingRed
    add currpos,25
    call DrawQueenRed
    add currpos,25
    call DrawBishopRed
    add currpos,25
    call DrawKnightRed
    add currpos,25
    call DrawRookRed
    mov currpos,320*25
    mov cx,8
    pawndrawred:
        call DrawPawnRed
        add currpos,25
    loop pawndrawred

    mov currpos,320*25*6
    mov cx,8
    pawndrawblue:
        call DrawPawnBlue
        add currpos,25
    loop pawndrawblue

    mov currpos,320*25*7
    call DrawRookBlue
    add currpos,25
    call DrawKnightBlue
    add currpos,25
    call DrawBishopBlue
    add currpos,25
    call DrawKingBlue
    add currpos,25
    call DrawQueenBlue
    add currpos,25
    call DrawBishopBlue
    add currpos,25
    call DrawKnightBlue
    add currpos,25
    call DrawRookBlue



    popa
    ret
initializepieces endp