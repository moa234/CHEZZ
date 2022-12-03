DrawRookBlue MACRO   X
    push ax
    push es
    push di

    mov     ax,0A000h
    mov     es,ax
    
    mov al,1h
    mov di,x 
    add di,6
    add di,3*320
    stosb
    mov al,9h
    mov cx,2
    rep stosb
    inc di
    mov cx,4
    rep stosb
    inc di
    mov cx,3
    rep stosb

    ;row 2
    add di,319 
    std
    mov cx,3
    rep stosb
    dec di
    mov cx,4
    rep stosb
    dec di
    mov cx,2
    rep stosb
    mov al,1h
    stosb

    ;row 3
    add di,321
    cld
    stosb
    mov al,9h
    mov cx,2
    rep stosb
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb
    mov al,1h
    stosb
    mov al,9h
    mov cx,3
    rep stosb

    ;row 4
    add di,319
    std
    mov cx,11
    rep stosb
    mov al,1h
    stosb

    ;row 5
    add di,322
    cld
    stosb
    mov al,9h
    mov cx,9
    rep stosb

    ;row 6
    add di,319
    std
    mov cx,9
    rep stosb
    mov al,1h
    stosb

    ;row 7
    add di,321
    cld
    stosb
    mov al,9h
    mov cx,9
    rep stosb

    ;row 8
    add di,317
    std
    mov al,1h
    mov cx,6
    rep stosb

    ;row 9
    add di,321
    cld
    mov cx,2h
    rep stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 10
    add di,319
    std
    mov al,9h
    mov cx,5
    rep stosb
    mov al,1h
    stosb

    ;row 11
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,7
    rep stosb

    ;row 12
    add di,319
    std
    mov al,9h
    mov cx,7
    rep stosb
    mov al,1h
    stosb

    ;row 13
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,7
    rep stosb
    
    ;row 14
    add di,320
    std
    mov al,9h
    mov cx,9
    rep stosb
    mov al,1h
    stosb

    ;row 15
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,9
    rep stosb

    ;row 16
    add di,319
    std
    mov al,9h
    mov cx,9
    rep stosb
    mov al,1h
    stosb

    ;row 17
    add di,322
    cld
    mov al,1h
    mov cx,8
    rep stosb

    ;row 18
    add di,322
    std
    mov al,9h
    mov cx,11
    rep stosb
    mov al,1h
    mov cx,3h
    rep stosb

    ;row 19
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,13
    rep stosb

    pop di
    pop es
    pop ax
ENDM DrawRookBlue

DrawRookRed MACRO   X
    push ax
    push es
    push di

    mov     ax,0A000h
    mov     es,ax
    
    mov al,4h
    mov di,x 
    add di,6
    add di,3*320
    stosb
    mov al,0Ch
    mov cx,2
    rep stosb
    inc di
    mov cx,4
    rep stosb
    inc di
    mov cx,3
    rep stosb

    ;row 2
    add di,319 
    std
    mov cx,3
    rep stosb
    dec di
    mov cx,4
    rep stosb
    dec di
    mov cx,2
    rep stosb
    mov al,4h
    stosb

    ;row 3
    add di,321
    cld
    stosb
    mov al,0Ch
    mov cx,2
    rep stosb
    mov al,4h
    stosb
    mov al,0Ch
    mov cx,4
    rep stosb
    mov al,4h
    stosb
    mov al,0Ch
    mov cx,3
    rep stosb

    ;row 4
    add di,319
    std
    mov cx,11
    rep stosb
    mov al,4h
    stosb

    ;row 5
    add di,322
    cld
    stosb
    mov al,0Ch
    mov cx,9
    rep stosb

    ;row 6
    add di,319
    std
    mov cx,9
    rep stosb
    mov al,4h
    stosb

    ;row 7
    add di,321
    cld
    stosb
    mov al,0Ch
    mov cx,9
    rep stosb

    ;row 8
    add di,317
    std
    mov al,4h
    mov cx,6
    rep stosb

    ;row 9
    add di,321
    cld
    mov cx,2h
    rep stosb
    mov al,0Ch
    mov cx,4
    rep stosb

    ;row 10
    add di,319
    std
    mov al,0Ch
    mov cx,5
    rep stosb
    mov al,4h
    stosb

    ;row 11
    add di,320
    cld
    mov al,4h
    stosb
    mov al,0Ch
    mov cx,7
    rep stosb

    ;row 12
    add di,319
    std
    mov al,0Ch
    mov cx,7
    rep stosb
    mov al,4h
    stosb

    ;row 13
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0Ch
    mov cx,7
    rep stosb
    
    ;row 14
    add di,320
    std
    mov al,0Ch
    mov cx,9
    rep stosb
    mov al,4h
    stosb

    ;row 15
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0Ch
    mov cx,9
    rep stosb

    ;row 16
    add di,319
    std
    mov al,0Ch
    mov cx,9
    rep stosb
    mov al,4h
    stosb

    ;row 17
    add di,322
    cld
    mov al,4h
    mov cx,8
    rep stosb

    ;row 18
    add di,322
    std
    mov al,0Ch
    mov cx,11
    rep stosb
    mov al,4h
    mov cx,3h
    rep stosb

    ;row 19
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0Ch
    mov cx,13
    rep stosb

    pop di
    pop es
    pop ax
ENDM DrawRookRed