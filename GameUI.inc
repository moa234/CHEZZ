
include pieces.inc
include board.inc
.code


initializegame proc
    
    getsystemtime
    mov startmin, cl
    mov startsec, dh
    
    GraphicsMode

    cmp startingflag,1
    je stayasis
    mov al,12
    mov board[0][3],al
    mov al,11
    mov board[0][4],al
    mov al,3
    mov board[7*8][3],al
    mov al,2
    mov board[7*8][4],al
    stayasis:

    call drawboard
    call initializepieces
    mov currpos,320*25*3+25*3
    call drawborder
     

    call displaygamenotifbar    
    ret
initializegame ENDP

initializepieces proc
    pusha

    mov di,currpos
    mov tempcurrpos,di
    mov currpos,0

    piecesloopdraw:
        call updaterowandcol
        call checkpiece
        call drawSelectedPiece

        cmp col,7
        jne samerow@pieces
        add currpos,320*25-8*25
        cmp row,7
        je lastcell@pieces
        samerow@pieces:
        add currpos,25

    jmp piecesloopdraw
    lastcell@pieces:

    mov di,tempcurrpos
    mov currpos,di
    call updaterowandcol

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