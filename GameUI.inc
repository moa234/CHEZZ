
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

drawboostat MACRO x,y 
Local back1,back2,back3,back4,back5
    pusha
    mov cx,x
    mov dx,y
    mov al,0eh
    mov ah,0ch;draw pixel command
    back1:
    int 10h
    inc cx
    inc dx
    mov si,10
    add si,x
    cmp cx,si
    jnz back1;to draw the 1st diagonal line from top left to bottom rigth
    dec cx
    back2:
    int 10h
    dec cx
    cmp cx,x
    jne back2;to draw the lower horizontal line  
    inc cx
    dec dx
    back3:
    int 10h
    inc cx
    dec dx
    mov si,10
    add si,x
    cmp cx,si
    jnz back3;to draw 2nd diagonal line from bottom left to top right
    dec cx
    back4:
    int 10h
    dec cx
    mov si,1
    add si,x
    cmp cx,si
    jge back4;to draw the upper horizontal line 
    
    mov si,5
    add si,x
    cmp cx,si
    mov si,5
    add si,y
    cmp dx,si
    back5:
    int 10h
    inc dx
    inc dx
    inc dx 
    mov si,10
    add si,y
    cmp dx,si
    jle back5;to draw the dotted line
    popa
ENDM drawboostat