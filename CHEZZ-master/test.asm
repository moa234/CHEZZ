DrawPawnRed proc
    push ax
    push es
    push di
    push cx
    pushf
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,11
    add di,7*320

    ;row 1
    mov al,0ch
    mov cx,3
    rep stosb

    ;row 2
    add di,320
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,04h
    stosb

    ;row 3
    add di,321
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 4
    add di,319
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,04h
    stosb

    ;row 5
    add di,322
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,2
    rep stosb

    ;row 6
    add di,320
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,04h
    stosb

    ;row 7
    add di,322
    cld
    mov al,04h
    mov cx,3
    rep stosb

    ;row 8
    add di,319
    std
    mov al,0ch
    mov cx,2
    rep stosb
    mov al,04h
    stosb

    ;row 9
    add di,320
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 10
    add di,319
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,04h
    stosb

    ;row 11
    add di,320
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,6
    rep stosb

    ;row 12
    add di,319
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,04h
    stosb

    ;row 13
    add di,322
    cld
    mov al,04h
    mov cx,5
    rep stosb

    ;row 14
    add di,321
    std
    mov al,0ch
    mov cx,7
    rep stosb
    mov al,04h
    mov cx,2
    rep stosb

    ;row 15
    add di,320
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,10
    rep stosb

    popa

    ret
DrawPawnRed endp
