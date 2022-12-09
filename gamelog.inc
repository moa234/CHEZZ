.code

updaterowandcol proc
    pusha

    mov ax, currpos
    mov bx,320
    mov dx,0
    div bx
    mov pixelrow, ax
    mov pixelcol, dx

    push dx
    mov dx,0
    mov bx,25
    div bx
    mov row, ax
    pop dx

    mov ax,dx
    mov bx,25
    mov dx,0
    div bx
    mov col, ax

    popa
    ret
updaterowandcol endp

traversecell proc
    pusha 

    cmp ah, 48h
    je upkey
    cmp ah, 4dh
    je rightkey
    cmp ah, 4bh
    je leftkey
    cmp ah, 50h
    je downkey

    jmp notarrow
    upkey:
        cmp row, 0
        je notarrow
        call deleteborder
        sub currpos,320*25
        call drawborder
        jmp notarrow
    rightkey:
        cmp col, 7
        je notarrow
        call deleteborder
        add currpos,25
        call drawborder
        jmp notarrow
    leftkey:
        cmp col, 0 
        je notarrow
        call deleteborder
        sub currpos,25
        call drawborder
        jmp notarrow
    downkey:
        cmp row, 7
        je notarrow
        call deleteborder
        add currpos,320*25
        call drawborder
        jmp notarrow
        
    notarrow:
    popa
    ret
traversecell endp

highlightpawn proc
    pusha
    mov ax,currpos
    mov selectedpos,ax
    MOV ax,col
    mov selectedcol,ax
    mov ax,row
    mov selectedrow,ax
    mov bx,currpos
    sub bx,320*25
    mov highlightpos,bx
    call highlightbox
    mov ax,currpos
    sub ax,320*25*2
    mov highlightpos,ax
    call highlightbox
    popa
    ret
highlightpawn endp

getmove proc
    pusha

    getKeyPress
    
    popa
    ret
getmove endp