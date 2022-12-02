DrawRook MACRO   X
    push ax
    push es
    mov     ax,0A000h
    mov     es,ax
    
    mov al,0fh ;set color to white
    mov di,x 
    add di,8
    add di,5*320
    mov cx,2
    rep stosb
    add di,1
    mov cx,2
    rep stosb
    add di,1
    mov cx,2
    rep stosb

    add di,319
    std
    mov cx,2
    rep stosb
    sub di,1
    mov cx,2
    rep stosb
    sub di,1
    mov cx,2
    rep stosb

    add di,321
    cld
    mov cx,8
    rep stosb

    add di,319
    std
    mov cx,8
    rep stosb

    add di,322
    cld
    mov cx,6
    rep stosb

    add di,319
    std
    mov cx,6
    rep stosb

    add di,322
    cld
    mov cx,4
    rep stosb

    add di,319
    std
    mov cx,4
    rep stosb

    add di,321
    cld
    mov cx,4
    rep stosb

    add di,320
    std
    mov cx,6
    rep stosb

    add di,321
    cld
    mov cx,6
    rep stosb

    add di,320
    std
    mov cx,8
    rep stosb

    add di,321
    cld
    mov cx,8
    rep stosb

    add di,320
    std
    mov cx,10
    rep stosb

    add di,321
    cld
    mov cx,10
    rep stosb



    pop es
    pop ax
ENDM MOVECURSOR