DrawRook MACRO   X,maincolor,shadowcolor
    push ax
    push es
    push di
    push cx
    pushf

    mov     ax,0A000h
    mov     es,ax
    
    cld

    mov al,shadowcolor
    mov di,x 
    add di,6
    add di,3*320
    stosb
    mov al,maincolor
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
    mov al,shadowcolor
    stosb

    ;row 3
    add di,321
    cld
    stosb
    mov al,maincolor
    mov cx,2
    rep stosb
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,3
    rep stosb

    ;row 4
    add di,319
    std
    mov cx,11
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 5
    add di,322
    cld
    stosb
    mov al,maincolor
    mov cx,9
    rep stosb

    ;row 6
    add di,319
    std
    mov cx,9
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 7
    add di,321
    cld
    stosb
    mov al,maincolor
    mov cx,9
    rep stosb

    ;row 8
    add di,317
    std
    mov al,shadowcolor
    mov cx,6
    rep stosb

    ;row 9
    add di,321
    cld
    mov cx,2h
    rep stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 10
    add di,319
    std
    mov al,maincolor
    mov cx,5
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 11
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,7
    rep stosb

    ;row 12
    add di,319
    std
    mov al,maincolor
    mov cx,7
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 13
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,7
    rep stosb
    
    ;row 14
    add di,320
    std
    mov al,maincolor
    mov cx,9
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 15
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,9
    rep stosb

    ;row 16
    add di,319
    std
    mov al,maincolor
    mov cx,9
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 17
    add di,322
    cld
    mov al,shadowcolor
    mov cx,8
    rep stosb

    ;row 18
    add di,322
    std
    mov al,maincolor
    mov cx,11
    rep stosb
    mov al,shadowcolor
    mov cx,3h
    rep stosb

    ;row 19
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,13
    rep stosb

    popf
    pop cx
    pop di
    pop es
    pop ax
ENDM DrawRook

DrawKnight MACRO   X,maincolor,shadowcolor
    push ax
    push es
    push di
    push cx
    pushf

    mov     ax,0A000h
    mov     es,ax
    
    cld

    ;row 1
    mov al,maincolor
    mov di,x 
    add di,11
    add di,2*320
    stosb

    ;row 2
    add di,321
    std 
    mov cx,3
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 3
    add di,320
    cld
    stosb
    mov al,maincolor
    mov cx,5h
    rep stosb

    ;row 4
    add di,320
    std
    mov al,maincolor
    mov cx,7h
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 5
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,8h
    rep stosb

    ;row 6
    add di,320
    std
    mov al,maincolor
    mov cx,10
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 7
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,5h
    rep stosb
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,5h
    rep stosb

    ;row 8
    add di,319
    std
    mov al,maincolor
    mov cx,4h
    rep stosb
    mov al,shadowcolor
    stosb
    dec di
    mov al,maincolor
    mov cx,5h
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 9
    add di,322
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,5h
    rep stosb
    inc di
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,2h
    rep stosb

    ;row 10
    add di,316
    std
    mov al,maincolor
    mov cx,6h
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 11
    add di,322
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,5h
    rep stosb

    ;row 12
    add di,320
    std
    mov al,maincolor
    mov cx,6h
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 13
    add di,322
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,5h
    rep stosb

    ;row 14
    add di,320
    std
    mov al,maincolor
    mov cx,7h
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 15
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,7h
    rep stosb

    ;row 16
    add di,320
    std
    mov al,maincolor
    mov cx,9h
    rep stosb
    mov al,shadowcolor
    mov cx,2
    rep stosb

    ;row 17
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,10
    rep stosb

    ;row 18
    add di,317
    std
    mov al,shadowcolor
    mov cx,7
    rep stosb

    ;row 19
    add di,317
    cld
    mov al,shadowcolor
    mov cx,3
    rep stosb
    mov al,maincolor
    mov cx,12
    rep stosb

    ;row 20
    add di,319
    std
    mov al,maincolor
    mov cx,14
    rep stosb
    mov al,shadowcolor
    stosb

    popf
    pop cx
    pop di
    pop es
    pop ax
ENDM DrawKnight

DrawPawn MACRO   X,maincolor,shadowcolor
    push ax
    push es
    push di
    push cx
    pushf
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,x
    add di,11
    add di,7*320

    ;row 1
    mov al,maincolor
    mov cx,3
    rep stosb

    ;row 2
    add di,320
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 3
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 4
    add di,319
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 5
    add di,322
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,2
    rep stosb

    ;row 6
    add di,320
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 7
    add di,322
    cld
    mov al,shadowcolor
    mov cx,3
    rep stosb

    ;row 8
    add di,319
    std
    mov al,maincolor
    mov cx,2
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 9
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 10
    add di,319
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 11
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,6
    rep stosb

    ;row 12
    add di,319
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 13
    add di,322
    cld
    mov al,shadowcolor
    mov cx,5
    rep stosb

    ;row 14
    add di,321
    std
    mov al,maincolor
    mov cx,7
    rep stosb
    mov al,shadowcolor
    mov cx,2
    rep stosb

    ;row 15
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,10
    rep stosb

    popf
    pop cx
    pop di
    pop es
    pop ax
ENDM DrawPawn

DrawBishop MACRO   X,maincolor,shadowcolor
    push ax
    push es
    push di
    push cx
    pushf
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,x
    add di,12
    add di,2*320

    ;row 1
    mov al,maincolor
    stosb

    ;row 2
    add di,320
    std
    mov al,maincolor
    mov cx,2
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 3
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,2
    rep stosb
    inc di
    stosb

    ;row 4
    add di,319
    std
    mov al,maincolor
    mov cx,2
    rep stosb
    dec di
    stosb
    mov al,shadowcolor
    stosb

    ;row 5
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,6
    rep stosb

    ;row 6
    add di,319
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 7
    add di,322
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 8
    add di,319
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 9
    add di,322
    cld
    mov al,shadowcolor
    mov cx,3h
    rep stosb

    ;row 10
    add di,321
    std
    mov al,maincolor
    mov cx,5
    rep stosb
    mov al,shadowcolor
    mov cx,2
    rep stosb

    ;row 11
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,8
    rep stosb

    ;row 12
    add di,316
    std
    mov al,shadowcolor
    mov cx,3
    rep stosb

    ;row 13
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,2
    rep stosb

    ;row 14
    add di,320
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 15
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 16
    add di,320
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 17
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,6
    rep stosb

    ;row 18
    add di,318
    std
    mov al,shadowcolor
    mov cx,5
    rep stosb

    ;row 19
    add di,318
    cld
    mov al,shadowcolor
    mov cx,2
    rep stosb
    mov al,maincolor
    mov cx,9
    rep stosb

    ;row 20
    add di,320
    std
    mov al,maincolor
    mov cx,12
    rep stosb
    mov al,shadowcolor
    stosb

    popf
    pop cx
    pop di
    pop es
    pop ax
ENDM DrawBishop

DrawQueen MACRO   X,maincolor,shadowcolor
    push ax
    push es
    push di
    push cx
    pushf

    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,x
    add di,13
    add di,3*320

    ;row 1
    mov al,maincolor
    stosb

    ;row 2
    add di,320
    std 
    mov al,maincolor
    mov cx,3
    rep stosb

    ;row 3
    add di,319
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,6
    rep stosb

    ;row 4
    add di,319
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 5
    add di,322
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 6
    add di,318
    std
    mov al,shadowcolor
    mov cx,3
    rep stosb

    ;row 7
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 8
    add di,320
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 9
    add di,322
    cld
    mov al,shadowcolor
    mov cx,5h
    rep stosb

    ;row 10
    add di,318
    std
    mov al,maincolor
    mov cx,2
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 11
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,2
    rep stosb

    ;row 12
    add di,319
    std
    mov al,maincolor
    mov cx,2
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 14
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb
    

    ;row 15
    add di,319
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb
    
    ;row 17
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,6
    rep stosb

    ;row 16
    add di,319
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 18
    add di,322
    cld
    mov al,shadowcolor
    mov cx,5
    rep stosb

    ;row 19
    add di,322
    std
    mov al,maincolor
    mov cx,9
    rep stosb
    mov al,shadowcolor
    mov cx,2
    rep stosb
    

    ;row 20
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,12
    rep stosb
    

    popf
    pop cx
    pop di
    pop es
    pop ax
ENDM DrawQueen

DrawKing MACRO   X,maincolor,shadowcolor
    push ax
    push es
    push di
    push cx
    pushf
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,x
    add di,13
    add di,2*320

    ;row 1
    mov al,maincolor
    stosb

    ;row 2
    add di,320
    std
    mov al,maincolor
    mov cx,3
    rep stosb

    ;row 3
    add di,322
    cld
    mov al,maincolor
    stosb

    ;row 4
    add di,322
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 5
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,6
    rep stosb

    ;row 6
    add di,318
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 7
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 8
    add di,318
    std
    mov al,shadowcolor
    mov cx,3
    rep stosb

    ;row 9
    add di,320
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 10
    add di,320
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 11
    add di,322
    cld
    mov al,shadowcolor
    mov cx,5h
    rep stosb

    ;row 12
    add di,318
    std
    mov al,shadowcolor
    mov cx,3
    rep stosb

    ;row 13
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,2
    rep stosb

    ;row 14
    add di,320
    std
    mov al,maincolor
    mov cx,4
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 15
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,4
    rep stosb

    ;row 16
    add di,320
    std
    mov al,maincolor
    mov cx,6
    rep stosb
    mov al,shadowcolor
    stosb

    ;row 17
    add di,321
    cld
    mov al,shadowcolor
    stosb
    mov al,maincolor
    mov cx,6
    rep stosb

    ;row 18
    add di,318
    std
    mov al,shadowcolor
    mov cx,5
    rep stosb

    ;row 19
    add di,318
    cld
    mov al,shadowcolor
    mov cx,2
    rep stosb
    mov al,maincolor
    mov cx,9
    rep stosb

    ;row 20
    add di,320
    std
    mov al,maincolor
    mov cx,12
    rep stosb
    mov al,shadowcolor
    stosb


    popf
    pop cx
    pop di
    pop es
    pop ax
ENDM DrawKing