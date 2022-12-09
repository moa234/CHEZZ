.code

updaterowandcol proc
    pusha
    mov ax, currpos
    mov bx,320
    mov dx,0
    div bx
    mov row, ax
    mov col, dx
    popa
    ret
updaterowandcol endp

traversecell proc
    pusha 

    getKeyPress
    jz notarrow
    clearbuffer
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
        cmp col, 25*7
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
        cmp row, 25*7
        je notarrow
        call deleteborder
        add currpos,320*25
        call drawborder
        jmp notarrow
        
    notarrow:
    popa
    ret
traversecell endp