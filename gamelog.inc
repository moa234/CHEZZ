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

deleteselctedpiece proc
    pusha
    GetPixelColour selectedpixelcol, selectedpixelrow
    mov di,currpos;;;;;;;
    mov tempcurrpos,di;;;;;;
    mov di,selectedpos;;;;;;
    mov currpos,di;;;;;;
    cmp al,07h
    jne boxiswhite
    call drawboxgrey
    jmp drawisfinished
    boxiswhite:
    call drawboxwhite
    drawisfinished:
    mov di,tempcurrpos;;;;;
    mov currpos,di;;;;;;;
    popa
    ret
deleteselctedpiece endp

movefromcelltocell proc
    pusha
    mov bx,row
    mov ax,8
    mul bx
    mov bx,ax  ;bx store row*8
    mov si,col ;SI store  col
    
    cmp movingopflag,1
    je movingflagon

    cmp board[bx][si],0   ;moving flag =0 and no piece in this square so do nothing
    je nomovingneeded

    mov di,1
    mov movingopflag,di
    jmp nomovingneeded  ;we set moving flag as moving flag =0 and there is a piece in this square


    movingflagon:
    ;call checkboxcolor
    ;cmp boxcolor,0ah
    ;jne nomovingneeded

    mov bx,row
    mov ax,8
    mul bx
    mov bx,ax  ;bx store row*8
    mov si,col ;SI store  col
    cmp board[bx][si],6
    ja movingneeded
    cmp board[bx][si],0
    je movingneeded
    jmp nomovingneeded

    movingneeded:
    mov al,selectedpiece
    mov board[bx][si],al
    call drawSelectedBluePiece

    mov bx,selectedrow
    mov ax,8
    mul bx
    mov bx,ax  ;bx store row*8
    mov si,selectedcol

    mov dl,0
    mov board[bx][si],dl
    call deleteselctedpiece

    mov dx,0
    mov movingopflag,dx
    mov selectedpiece,dl

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
    jmp notrightpawn
    enemypiece:
    call highlightbox
    call drawSelectedRedPiece
    
    notrightpawn:
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

highlightRook proc
    pusha

    whilenopieceup@Rook:
        cmp row,0
        je piecefoundup@rook
        mov bx,currpos
        sub bx,320*25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightup@rook
        cmp al,6
        ja enemypiecefoundup@rook
        jmp piecefoundup@rook
        enemypiecefoundup@rook:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundup@rook
        
        highlightup@rook:
        call highlightbox
        

        
        jmp whilenopieceup@Rook
        piecefoundup@rook:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopieceleft@rook:
        cmp col,0
        je piecefoundleft@rook
        mov bx,currpos
        sub bx,25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightleft@rook
        cmp al,6
        ja enemypiecefoundleft@rook
        jmp piecefoundleft@rook
        enemypiecefoundleft@rook:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundleft@rook
        
        highlightleft@rook:
        call highlightbox
        

        
        jmp whilenopieceleft@rook
        piecefoundleft@rook:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopiecedown@rook:
        cmp row,7
        je piecefounddown@rook
        mov bx,currpos
        add bx,320*25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightdown@rook
        cmp al,6
        ja enemypiecefounddown@rook
        jmp piecefounddown@rook
        enemypiecefounddown@rook:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefounddown@rook
        
        highlightdown@rook:
        call highlightbox
        

        
        jmp whilenopiecedown@rook
        piecefounddown@rook:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopieceright@rook:
        cmp col,7
        je piecefoundright@rook
        mov bx,currpos
        add bx,25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightright@rook
        cmp al,6
        ja enemypiecefoundright@rook
        jmp piecefoundright@rook
        enemypiecefoundright@rook:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundright@rook
        
        highlightright@rook:
        call highlightbox
        

        
        jmp whilenopieceright@rook
        piecefoundright@rook:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    popa
    ret
highlightRook endp

highlightBishop proc
    pusha

    whilenopieceup@Bishop:
        cmp row,0
        je piecefoundup@Bishop
        cmp col,7
        je piecefoundup@Bishop
        mov bx,currpos
        sub bx,320*25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightup@Bishop
        cmp al,6
        ja enemypiecefoundup@Bishop
        jmp piecefoundup@Bishop
        enemypiecefoundup@Bishop:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundup@Bishop
        
        highlightup@Bishop:
        call highlightbox
        

        
        jmp whilenopieceup@Bishop
        piecefoundup@Bishop:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopieceleft@Bishop:
        cmp col,0
        je piecefoundleft@Bishop
        cmp row,0
        je piecefoundleft@Bishop
        mov bx,currpos
        sub bx,320*25+25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightleft@Bishop
        cmp al,6
        ja enemypiecefoundleft@Bishop
        jmp piecefoundleft@Bishop
        enemypiecefoundleft@Bishop:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundleft@Bishop
        
        highlightleft@Bishop:
        call highlightbox
        

        
        jmp whilenopieceleft@Bishop
        piecefoundleft@Bishop:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopiecedown@Bishop:
        cmp row,7
        je piecefounddown@Bishop
        cmp col,0
        je piecefounddown@Bishop
        mov bx,currpos
        add bx,320*25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightdown@Bishop
        cmp al,6
        ja enemypiecefounddown@Bishop
        jmp piecefounddown@Bishop
        enemypiecefounddown@Bishop:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefounddown@Bishop
        
        highlightdown@Bishop:
        call highlightbox
        

        
        jmp whilenopiecedown@Bishop
        piecefounddown@Bishop:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopieceright@Bishop:
        cmp col,7
        je piecefoundright@Bishop
        cmp row,7
        je piecefoundright@Bishop
        mov bx,currpos
        add bx,25+320*25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        call checkpiece
        cmp al,0
        je highlightright@Bishop
        cmp al,6
        ja enemypiecefoundright@Bishop
        jmp piecefoundright@Bishop
        enemypiecefoundright@Bishop:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundright@Bishop
        
        highlightright@Bishop:
        call highlightbox
        

        
        jmp whilenopieceright@Bishop
        piecefoundright@Bishop:
    

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    popa
    ret
highlightBishop endp

checkboxcolor proc
    pusha
    mov ax,pixelcol
    mov bx,pixelrow
    add ax, 2
    add bx, 2
    GetPixelColour ax,bx
    mov boxcolor,al
    popa
checkboxcolor endp

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

    cmp movingopflag,1
    je secondq
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
    secondq:
    popa
    ret
selection endp

getmove proc
    pusha

    getKeyPress
    
    popa
    ret
getmove endp