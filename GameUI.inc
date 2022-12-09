
include pieces.inc
include board.inc
.code


initializegame proc
    
    GraphicsMode

    call drawboard
    call initializepieces
    mov currpos,320*25*3+25*3
    call drawborder

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