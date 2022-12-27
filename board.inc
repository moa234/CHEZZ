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
    mov currpos,0
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

drawborder proc
    pusha
    mov     ax,0A000h
    mov     es,ax
    
    cld

    mov di,currpos
    mov al,bordercolor

    mov dx,2
    drawtopborder:
        mov cx,25
        rep stosb
        add di,320-25
        dec DX
    jnz drawtopborder

    mov dx,21
    drawsideborder:
        mov cx,2
        rep stosb
        add di,25-4
        mov cx,2
        rep stosb
        add di,320-25
        dec DX
    jnz drawsideborder

    mov dx,2
    drawbottomborder:
        mov cx,25
        rep stosb
        add di,320-25
        dec DX
    jnz drawbottomborder

    call updaterowandcol

    popa
    ret
drawborder ENDP

deleteborder proc
    pusha

    mov ax,0A000h
    mov es,ax

    cld 
    
    mov di,currpos

    GetPixelColour pixelcol,pixelrow
    ;mov al,[es:di]

    
    delete:
        mov dx,2
        deltopborder:
            mov cx,25
            rep stosb
            add di,320-25
            dec DX
        jnz deltopborder

        mov dx,21
        delsideborder:
            mov cx,2
            rep stosb
            add di,25-4
            mov cx,2
            rep stosb
            add di,320-25
            dec DX
        jnz delsideborder

        mov dx,2
        delbottomborder:
            mov cx,25
            rep stosb
            add di,320-25
            dec DX
        jnz delbottomborder

    popa
    ret
deleteborder ENDP

highlightbox proc
    pusha
    mov bl,1
    mov highlightflag,bl
    mov     ax,0A000h
    mov     es,ax
    
    cld

    MOV DI,highlightpos
    add di,3+320*3
    mov dx,19
    mov al,0ah
    backhighlight:
        mov cx,19
        rep stosb
        add di,320-19
        dec DX
    jnz backhighlight

    popa
    ret
highlightbox ENDP

