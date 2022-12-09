.code

drawSelectedRedPiece proc
    cmp al,7
    je Redpawn
    cmp al,8
    je Redrook
    cmp al,9
    je Redknight
    cmp al,10
    je Redbishop
    cmp al,12
    je Redqueen
    cmp al,11
    je Redking

    Redpawn:
        call DrawPawnRed
        ret
    Redrook:
        call DrawRookRed
        ret
    Redknight:
        call DrawKnightRed
        ret
    Redbishop:
        call DrawBishopRed
        ret
    Redqueen:
        call DrawQueenRed
        ret
    Redking:    
        call DrawKingRed

    ret
drawSelectedRedPiece endp

drawSelectedBluePiece proc
    cmp al,1
    je bluepawn
    cmp al,6
    je bluerook
    cmp al,5
    je blueknight
    cmp al,4
    je bluebishop
    cmp al,3
    je bluequeen
    cmp al,2
    je blueking

    bluepawn:
        call DrawPawnBlue
        ret
    bluerook:
        call DrawRookBlue
        ret
    blueknight:
        call DrawKnightBlue
        ret
    bluebishop:
        call DrawBishopBlue
        ret
    bluequeen:
        call DrawQueenBlue
        ret
    blueking:    
        call DrawKingBlue

    ret
drawSelectedBluePiece endp


DrawRookBlue PROC
    pusha

    mov     ax,0A000h
    mov     es,ax
    
    cld

    mov al,1h
    mov di,currpos 
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

    popa

    ret
DrawRookBlue ENDP

DrawRookRed PROC
    pusha

    mov     ax,0A000h
    mov     es,ax
    
    cld

    mov al,4h
    mov di,currpos 
    add di,6
    add di,3*320
    stosb
    mov al,0ch
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
    mov al,0ch
    mov cx,2
    rep stosb
    mov al,4h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,4h
    stosb
    mov al,0ch
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
    mov al,0ch
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
    mov al,0ch
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
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 10
    add di,319
    std
    mov al,0ch
    mov cx,5
    rep stosb
    mov al,4h
    stosb

    ;row 11
    add di,320
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,7
    rep stosb

    ;row 12
    add di,319
    std
    mov al,0ch
    mov cx,7
    rep stosb
    mov al,4h
    stosb

    ;row 13
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,7
    rep stosb
    
    ;row 14
    add di,320
    std
    mov al,0ch
    mov cx,9
    rep stosb
    mov al,4h
    stosb

    ;row 15
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,9
    rep stosb

    ;row 16
    add di,319
    std
    mov al,0ch
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
    mov al,0ch
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
    mov al,0ch
    mov cx,13
    rep stosb

    popa

    ret
DrawRookRed ENDP

DrawKnightBlue PROC
    pusha

    mov     ax,0A000h
    mov     es,ax
    
    cld

    ;row 1
    mov al,9h
    mov di,currpos 
    add di,11
    add di,2*320
    stosb

    ;row 2
    add di,321
    std 
    mov cx,3
    rep stosb
    mov al,1h
    stosb

    ;row 3
    add di,320
    cld
    stosb
    mov al,9h
    mov cx,5h
    rep stosb

    ;row 4
    add di,320
    std
    mov al,9h
    mov cx,7h
    rep stosb
    mov al,1h
    stosb

    ;row 5
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,8h
    rep stosb

    ;row 6
    add di,320
    std
    mov al,9h
    mov cx,10
    rep stosb
    mov al,1h
    stosb

    ;row 7
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,5h
    rep stosb
    mov al,1h
    stosb
    mov al,9h
    mov cx,5h
    rep stosb

    ;row 8
    add di,319
    std
    mov al,9h
    mov cx,4h
    rep stosb
    mov al,1h
    stosb
    dec di
    mov al,9h
    mov cx,5h
    rep stosb
    mov al,1h
    stosb

    ;row 9
    add di,322
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,5h
    rep stosb
    inc di
    mov al,1h
    stosb
    mov al,9h
    mov cx,2h
    rep stosb

    ;row 10
    add di,316
    std
    mov al,9h
    mov cx,6h
    rep stosb
    mov al,1h
    stosb

    ;row 11
    add di,322
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,5h
    rep stosb

    ;row 12
    add di,320
    std
    mov al,9h
    mov cx,6h
    rep stosb
    mov al,1h
    stosb

    ;row 13
    add di,322
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,5h
    rep stosb

    ;row 14
    add di,320
    std
    mov al,9h
    mov cx,7h
    rep stosb
    mov al,1h
    stosb

    ;row 15
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,7h
    rep stosb

    ;row 16
    add di,320
    std
    mov al,9h
    mov cx,9h
    rep stosb
    mov al,1h
    mov cx,2
    rep stosb

    ;row 17
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,10
    rep stosb

    ;row 18
    add di,317
    std
    mov al,1h
    mov cx,7
    rep stosb

    ;row 19
    add di,317
    cld
    mov al,1h
    mov cx,3
    rep stosb
    mov al,9h
    mov cx,12
    rep stosb

    ;row 20
    add di,319
    std
    mov al,9h
    mov cx,14
    rep stosb
    mov al,1h
    stosb

    popa

    ret
DrawKnightBlue ENDP

DrawKnightRed PROC
    pusha

    mov     ax,0A000h
    mov     es,ax
    
    cld

    ;row 1
    mov al,0ch
    mov di,currpos
    add di,11
    add di,2*320
    stosb

    ;row 2
    add di,321
    std 
    mov cx,3
    rep stosb
    mov al,4h
    stosb

    ;row 3
    add di,320
    cld
    stosb
    mov al,0ch
    mov cx,5h
    rep stosb

    ;row 4
    add di,320
    std
    mov al,0ch
    mov cx,7h
    rep stosb
    mov al,4h
    stosb

    ;row 5
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,8h
    rep stosb

    ;row 6
    add di,320
    std
    mov al,0ch
    mov cx,10
    rep stosb
    mov al,4h
    stosb

    ;row 7
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,5h
    rep stosb
    mov al,4h
    stosb
    mov al,0ch
    mov cx,5h
    rep stosb

    ;row 8
    add di,319
    std
    mov al,0ch
    mov cx,4h
    rep stosb
    mov al,4h
    stosb
    dec di
    mov al,0ch
    mov cx,5h
    rep stosb
    mov al,4h
    stosb

    ;row 9
    add di,322
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,5h
    rep stosb
    inc di
    mov al,4h
    stosb
    mov al,0ch
    mov cx,2h
    rep stosb

    ;row 10
    add di,316
    std
    mov al,0ch
    mov cx,6h
    rep stosb
    mov al,4h
    stosb

    ;row 11
    add di,322
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,5h
    rep stosb

    ;row 12
    add di,320
    std
    mov al,0ch
    mov cx,6h
    rep stosb
    mov al,4h
    stosb

    ;row 13
    add di,322
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,5h
    rep stosb

    ;row 14
    add di,320
    std
    mov al,0ch
    mov cx,7h
    rep stosb
    mov al,4h
    stosb

    ;row 15
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,7h
    rep stosb

    ;row 16
    add di,320
    std
    mov al,0ch
    mov cx,9h
    rep stosb
    mov al,4h
    mov cx,2
    rep stosb

    ;row 17
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,10
    rep stosb

    ;row 18
    add di,317
    std
    mov al,4h
    mov cx,7
    rep stosb

    ;row 19
    add di,317
    cld
    mov al,4h
    mov cx,3
    rep stosb
    mov al,0ch
    mov cx,12
    rep stosb

    ;row 20
    add di,319
    std
    mov al,0ch
    mov cx,14
    rep stosb
    mov al,4h
    stosb

    popa

    ret
DrawKnightRed ENDP

DrawPawnBlue proc
    pusha
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,11
    add di,7*320

    ;row 1
    mov al,09h
    mov cx,3
    rep stosb

    ;row 2
    add di,320
    std
    mov al,09h
    mov cx,4
    rep stosb
    mov al,01h
    stosb

    ;row 3
    add di,321
    cld
    mov al,01h
    stosb
    mov al,09h
    mov cx,4
    rep stosb

    ;row 4
    add di,319
    std
    mov al,09h
    mov cx,4
    rep stosb
    mov al,01h
    stosb

    ;row 5
    add di,322
    cld
    mov al,01h
    stosb
    mov al,09h
    mov cx,2
    rep stosb

    ;row 6
    add di,320
    std
    mov al,09h
    mov cx,4
    rep stosb
    mov al,01h
    stosb

    ;row 7
    add di,322
    cld
    mov al,01h
    mov cx,3
    rep stosb

    ;row 8
    add di,319
    std
    mov al,09h
    mov cx,2
    rep stosb
    mov al,01h
    stosb

    ;row 9
    add di,320
    cld
    mov al,01h
    stosb
    mov al,09h
    mov cx,4
    rep stosb

    ;row 10
    add di,319
    std
    mov al,09h
    mov cx,4
    rep stosb
    mov al,01h
    stosb

    ;row 11
    add di,320
    cld
    mov al,01h
    stosb
    mov al,09h
    mov cx,6
    rep stosb

    ;row 12
    add di,319
    std
    mov al,09h
    mov cx,6
    rep stosb
    mov al,01h
    stosb

    ;row 13
    add di,322
    cld
    mov al,01h
    mov cx,5
    rep stosb

    ;row 14
    add di,321
    std
    mov al,09h
    mov cx,7
    rep stosb
    mov al,01h
    mov cx,2
    rep stosb

    ;row 15
    add di,320
    cld
    mov al,01h
    stosb
    mov al,09h
    mov cx,10
    rep stosb

    popa

    ret
DrawPawnBlue endp

DrawPawnRed proc
    pusha
    
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

DrawBishopBlue proc
    pusha
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,12
    add di,2*320

    ;row 1
    mov al,9h
    stosb

    ;row 2
    add di,320
    std
    mov al,9h
    mov cx,2
    rep stosb
    mov al,1h
    stosb

    ;row 3
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,2
    rep stosb
    inc di
    stosb

    ;row 4
    add di,319
    std
    mov al,9h
    mov cx,2
    rep stosb
    dec di
    stosb
    mov al,1h
    stosb

    ;row 5
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,6
    rep stosb

    ;row 6
    add di,319
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 7
    add di,322
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 8
    add di,319
    std
    mov al,9h
    mov cx,4
    rep stosb
    mov al,1h
    stosb

    ;row 9
    add di,322
    cld
    mov al,1h
    mov cx,3h
    rep stosb

    ;row 10
    add di,321
    std
    mov al,9h
    mov cx,5
    rep stosb
    mov al,1h
    mov cx,2
    rep stosb

    ;row 11
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,8
    rep stosb

    ;row 12
    add di,316
    std
    mov al,1h
    mov cx,3
    rep stosb

    ;row 13
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,2
    rep stosb

    ;row 14
    add di,320
    std
    mov al,9h
    mov cx,4
    rep stosb
    mov al,1h
    stosb

    ;row 15
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 16
    add di,320
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 17
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,6
    rep stosb

    ;row 18
    add di,318
    std
    mov al,1h
    mov cx,5
    rep stosb

    ;row 19
    add di,318
    cld
    mov al,1h
    mov cx,2
    rep stosb
    mov al,9h
    mov cx,9
    rep stosb

    ;row 20
    add di,320
    std
    mov al,9h
    mov cx,12
    rep stosb
    mov al,1h
    stosb

    popa

    ret
DrawBishopBlue endp

DrawBishopRed proc
    pusha
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,12
    add di,2*320

    ;row 1
    mov al,0ch
    stosb

    ;row 2
    add di,320
    std
    mov al,0ch
    mov cx,2
    rep stosb
    mov al,04h
    stosb

    ;row 3
    add di,320
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,2
    rep stosb
    inc di
    stosb

    ;row 4
    add di,319
    std
    mov al,0ch
    mov cx,2
    rep stosb
    dec di
    stosb
    mov al,04h
    stosb

    ;row 5
    add di,320
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,6
    rep stosb

    ;row 6
    add di,319
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,04h
    stosb

    ;row 7
    add di,322
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 8
    add di,319
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,04h
    stosb

    ;row 9
    add di,322
    cld
    mov al,04h
    mov cx,3h
    rep stosb

    ;row 10
    add di,321
    std
    mov al,0ch
    mov cx,5
    rep stosb
    mov al,04h
    mov cx,2
    rep stosb

    ;row 11
    add di,320
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,8
    rep stosb

    ;row 12
    add di,316
    std
    mov al,04h
    mov cx,3
    rep stosb

    ;row 13
    add di,321
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,2
    rep stosb

    ;row 14
    add di,320
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,04h
    stosb

    ;row 15
    add di,321
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 16
    add di,320
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,04h
    stosb

    ;row 17
    add di,321
    cld
    mov al,04h
    stosb
    mov al,0ch
    mov cx,6
    rep stosb

    ;row 18
    add di,318
    std
    mov al,04h
    mov cx,5
    rep stosb

    ;row 19
    add di,318
    cld
    mov al,04h
    mov cx,2
    rep stosb
    mov al,0ch
    mov cx,9
    rep stosb

    ;row 20
    add di,320
    std
    mov al,0ch
    mov cx,12
    rep stosb
    mov al,04h
    stosb

    popa

    ret
DrawBishopRed endp

DrawQueenBlue proc
    pusha

    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,12
    add di,3*320

    ;row 1
    mov al,9h
    stosb

    ;row 2
    add di,320
    std 
    mov al,9h
    mov cx,3
    rep stosb

    ;row 3
    add di,319
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,6
    rep stosb

    ;row 4
    add di,319
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 5
    add di,322
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 6
    add di,318
    std
    mov al,1h
    mov cx,3
    rep stosb

    ;row 7
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 8
    add di,320
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 9
    add di,322
    cld
    mov al,1h
    mov cx,5h
    rep stosb

    ;row 10
    add di,318
    std
    mov al,9h
    mov cx,2
    rep stosb
    mov al,1h
    stosb

    ;row 11
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,2
    rep stosb

    ;row 12
    add di,319
    std
    mov al,9h
    mov cx,2
    rep stosb
    mov al,1h
    stosb

    ;row 14
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb
    

    ;row 15
    add di,319
    std
    mov al,9h
    mov cx,4
    rep stosb
    mov al,1h
    stosb
    
    ;row 17
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,6
    rep stosb

    ;row 16
    add di,319
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 18
    add di,322
    cld
    mov al,1h
    mov cx,5
    rep stosb

    ;row 19
    add di,322
    std
    mov al,9h
    mov cx,9
    rep stosb
    mov al,1h
    mov cx,2
    rep stosb
    

    ;row 20
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,12
    rep stosb
    

    popa

    ret
DrawQueenBlue endp

DrawQueenRed proc
    pusha

    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,12
    add di,3*320

    ;row 1
    mov al,0ch
    stosb

    ;row 2
    add di,320
    std 
    mov al,0ch
    mov cx,3
    rep stosb

    ;row 3
    add di,319
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,6
    rep stosb

    ;row 4
    add di,319
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,4h
    stosb

    ;row 5
    add di,322
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 6
    add di,318
    std
    mov al,4h
    mov cx,3
    rep stosb

    ;row 7
    add di,320
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 8
    add di,320
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,4h
    stosb

    ;row 9
    add di,322
    cld
    mov al,4h
    mov cx,5h
    rep stosb

    ;row 10
    add di,318
    std
    mov al,0ch
    mov cx,2
    rep stosb
    mov al,4h
    stosb

    ;row 11
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,2
    rep stosb

    ;row 12
    add di,319
    std
    mov al,0ch
    mov cx,2
    rep stosb
    mov al,4h
    stosb

    ;row 14
    add di,320
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb
    

    ;row 15
    add di,319
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,4h
    stosb
    
    ;row 17
    add di,320
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,6
    rep stosb

    ;row 16
    add di,319
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,4h
    stosb

    ;row 18
    add di,322
    cld
    mov al,4h
    mov cx,5
    rep stosb

    ;row 19
    add di,322
    std
    mov al,0ch
    mov cx,9
    rep stosb
    mov al,4h
    mov cx,2
    rep stosb
    

    ;row 20
    add di,320
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,12
    rep stosb
    

    popa

    ret
DrawQueenRed endp

DrawKingBlue proc
    pusha
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,12
    add di,2*320

    ;row 1
    mov al,9h
    stosb

    ;row 2
    add di,320
    std
    mov al,9h
    mov cx,3
    rep stosb

    ;row 3
    add di,322
    cld
    mov al,9h
    stosb

    ;row 4
    add di,322
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 5
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,6
    rep stosb

    ;row 6
    add di,318
    std
    mov al,9h
    mov cx,4
    rep stosb
    mov al,1h
    stosb

    ;row 7
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 8
    add di,318
    std
    mov al,1h
    mov cx,3
    rep stosb

    ;row 9
    add di,320
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 10
    add di,320
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 11
    add di,322
    cld
    mov al,1h
    mov cx,5h
    rep stosb

    ;row 12
    add di,318
    std
    mov al,1h
    mov cx,3
    rep stosb

    ;row 13
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,2
    rep stosb

    ;row 14
    add di,320
    std
    mov al,9h
    mov cx,4
    rep stosb
    mov al,1h
    stosb

    ;row 15
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,4
    rep stosb

    ;row 16
    add di,320
    std
    mov al,9h
    mov cx,6
    rep stosb
    mov al,1h
    stosb

    ;row 17
    add di,321
    cld
    mov al,1h
    stosb
    mov al,9h
    mov cx,6
    rep stosb

    ;row 18
    add di,318
    std
    mov al,1h
    mov cx,5
    rep stosb

    ;row 19
    add di,318
    cld
    mov al,1h
    mov cx,2
    rep stosb
    mov al,9h
    mov cx,9
    rep stosb

    ;row 20
    add di,320
    std
    mov al,9h
    mov cx,12
    rep stosb
    mov al,1h
    stosb


    popa

    ret
DrawKingBlue endp

DrawKingRed proc
    pusha
    
    mov     ax,0A000h
    mov     es,ax

    cld

    mov di,currpos
    add di,12
    add di,2*320

    ;row 1
    mov al,0ch
    stosb

    ;row 2
    add di,320
    std
    mov al,0ch
    mov cx,3
    rep stosb

    ;row 3
    add di,322
    cld
    mov al,0ch
    stosb

    ;row 4
    add di,322
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,4h
    stosb

    ;row 5
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,6
    rep stosb

    ;row 6
    add di,318
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,4h
    stosb

    ;row 7
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 8
    add di,318
    std
    mov al,4h
    mov cx,3
    rep stosb

    ;row 9
    add di,320
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 10
    add di,320
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,4h
    stosb

    ;row 11
    add di,322
    cld
    mov al,4h
    mov cx,5h
    rep stosb

    ;row 12
    add di,318
    std
    mov al,4h
    mov cx,3
    rep stosb

    ;row 13
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,2
    rep stosb

    ;row 14
    add di,320
    std
    mov al,0ch
    mov cx,4
    rep stosb
    mov al,4h
    stosb

    ;row 15
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,4
    rep stosb

    ;row 16
    add di,320
    std
    mov al,0ch
    mov cx,6
    rep stosb
    mov al,4h
    stosb

    ;row 17
    add di,321
    cld
    mov al,4h
    stosb
    mov al,0ch
    mov cx,6
    rep stosb

    ;row 18
    add di,318
    std
    mov al,4h
    mov cx,5
    rep stosb

    ;row 19
    add di,318
    cld
    mov al,4h
    mov cx,2
    rep stosb
    mov al,0ch
    mov cx,9
    rep stosb

    ;row 20
    add di,320
    std
    mov al,0ch
    mov cx,12
    rep stosb
    mov al,4h
    stosb


    popa

    ret
DrawKingRed endp