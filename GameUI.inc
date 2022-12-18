
include pieces.inc
include board.inc
.code


initializegame proc
    
    GraphicsMode

    call drawboard
    call initializepieces
    mov currpos,320*25*3+25*3
    call drawborder
    getsystemtime
    mov startmin, cl
    mov startsec, dh 

    mov cx,8*8*2
    mov dl,startsec
    mov dh,startmin

    

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
    call DrawQueenRed
    add currpos,25
    call DrawKingRed
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
    call DrawQueenBlue
    add currpos,25
    call DrawKingBlue
    add currpos,25
    call DrawBishopBlue
    add currpos,25
    call DrawKnightBlue
    add currpos,25
    call DrawRookBlue



    popa
    ret
initializepieces endp

draw3 proc
    pusha

    mov ax,0A000h
    mov es,ax

    cld
    mov di,currpos
    mov cx,4
    mov al,2
    rep stosb

    add di,319
    stosb

    add di,316
    mov cx,4
    rep stosb

    add di,319
    stosb

    add di,316
    mov cx,4
    rep stosb

    popa
    ret
draw3 endp

draw2 proc 
    pusha
    mov ax,0A000h
    mov es,ax

    cld
    mov di,currpos

    mov ax,pixelrow
    sub ax,1
    GetPixelColour pixelcol,ax
    add di,3*320+3
    stosb

    mov di,currpos
    mov cx,4
    mov al,2
    rep stosb

    add di,319
    stosb

    add di,316
    mov cx,4
    rep stosb

    add di,320
    sub di,4
    stosb

    add di,319
    mov cx,4
    rep stosb

    



    popa
    ret
draw2 endp

draw1 proc
    pusha

    mov ax,0A000h
    mov es,ax

    cld
    mov di,currpos
    mov ax,pixelrow
    sub ax,1
    GetPixelColour pixelcol,ax
    stosb
    add di,1
    mov cx,2
    rep stosb

    add di,319
    stosb

    add di,316
    stosb
    add di,1
    mov cx,2
    rep stosb

    add di,316
    stosb

    add di,322
    stosb

    mov di,currpos
    mov al,2
    add di,320
    mov cx,2
    rep stosb

    add di,320*2-1
    stosb

    popa
    ret
draw1 endp

deletetimer proc
    pusha
    mov ax,0A000h
    mov es,ax

    cld
    mov di,currpos
    mov bx,5
    loopbox:
        mov ax,pixelrow
        sub ax,1
        GetPixelColour pixelcol,ax
        mov cx,4
        rep stosb
        add di,316
        dec bx
        cmp bx,0
    jne loopbox

    popa
    ret
deletetimer ENDP