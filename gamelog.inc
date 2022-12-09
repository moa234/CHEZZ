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



movefromcelltocell proc
pusha
mov bx,row
mov ax,8
mul bx
mov bx,ax  ;bx store row*8
mov si,col ;SI store  col
mov oldcol,si
mov oldrow,bx
cmp movingopflag,1
je movingflagon

cmp board[bx][si],0   ;moving flag =0 and no piece in this square so do nothing
je nomovingneeded

mov di,1
mov movingopflag,di
mov di,currpos
mov oldcurrpos,di
jmp nomovingneeded  ;we set moving flag as moving flag =0 and there is a piece in this square

movingflagon:
mov bx,row
mov ax,8
mul bx
mov bx,ax  ;bx store row*8
mov si,col ;SI store  col
cmp board[bx][si],0
jne nomovingneeded

mov board[bx][si],1
mov bx,oldrow
mov si,oldcol
mov board[bx][si],0
;delete pawn at  old position
call DrawPawnBlue

mov di,0
mov movingopflag,di

nomovingneeded:
popa
ret
movefromcelltocell endp

highlightpawn proc
    pusha
    
    mov bx,currpos

    sub bx,320*25
    mov highlightpos,bx
    mov currpos,bx
    call updaterowandcol

    call checkpiece
    cmp al,0
    je nopiece
    jmp pawnstart
    nopiece:
        call highlightbox

    cmp selectedrow,6
    jne pawnstart

    mov bx,currpos
    sub bx,320*25
    mov currpos,bx
    call updaterowandcol
    mov highlightpos,bx

    call checkpiece
    cmp al,0
    je nopiece2
    jmp pawnstart
    nopiece2:
        call highlightbox
    pawnstart:
    
    mov ax,selectedpos
    mov currpos,ax
    call updaterowandcol

    sub ax,320*25-25
    mov currpos,ax
    call updaterowandcol
    mov highlightpos,ax

    call checkpiece
    cmp al,6
    ja enemypiece
    jmp endhighpawn
    enemypiece:
        call highlightbox
        call drawSelectedRedPiece

    mov ax,currpos
    sub ax,50
    mov currpos,ax
    call updaterowandcol
    mov highlightpos,ax

    call checkpiece
    cmp al,6
    ja enemypiece2
    jmp endhighpawn
    enemypiece2:
        call highlightbox
        call drawSelectedRedPiece
    endhighpawn:

    mov ax,selectedpos
    mov currpos,ax
    call updaterowandcol

    popa
    ret
highlightpawn endp

checkpiece proc

    mov ax,row
    mov bx,8
    mul bx
    mov bx,ax

    mov si,col
    mov al,board[bx][si]

    ret
checkpiece endp

selection proc
    pusha

    mov ax,currpos
    mov selectedpos,ax
    MOV ax,col
    mov selectedcol,ax
    mov ax,row
    mov selectedrow,ax
    mov ax,pixelcol
    mov selectedpixelcol,ax
    mov ax,pixelrow
    mov selectedpixelrow,ax

    mov bx,row
    mov ax,8
    mul bx
    mov bx,ax
    mov si,col
    mov al,board[bx][si]
    mov selectedpiece,al

    popa
    ret
selection endp

getmove proc
    pusha

    getKeyPress
    
    popa
    ret
getmove endp