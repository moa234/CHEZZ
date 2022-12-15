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

delnewposhighlight proc
   pusha
   GetPixelColour pixelcol, pixelrow
   cmp al,07h
   jne boxiswhitee
   call drawboxgrey
   jmp drawingfinished
   boxiswhitee:
   call drawboxwhite
   drawingfinished:
   call drawborder
   popa
   ret
delnewposhighlight endp

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
    mov dl,01h
    mov bordercolor,dl
    call delnewposhighlight
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


highlightforselectedpiece proc
    cmp selectedpiece,1
    je highpawn
    cmp selectedpiece,6
    je highRook
    cmp selectedpiece,4
    je highbishop
    cmp selectedpiece,5
    je highknight
    cmp selectedpiece,3
    je highking
    cmp selectedpiece,2
    je highqueen
        
    jmp checkhighlight
    highpawn:
        mov dl, 04h
        mov bordercolor,dl
        call drawborder
        mov bordercolor,dl
        call highlightpawn
        jmp checkhighlight
    highRook:
        mov dl, 04h
        mov bordercolor,dl
        call drawborder
        mov bordercolor,dl
        call highlightrook
        jmp checkhighlight
    highbishop:
        mov dl, 04h
        mov bordercolor,dl
        call drawborder
        mov bordercolor,dl
        call highlightbishop
        jmp checkhighlight
    highknight:
        mov dl, 04h
        mov bordercolor,dl
        call drawborder
        mov bordercolor,dl
        call highlightknight
        jmp checkhighlight
    highking:
        mov dl, 04h
        mov bordercolor,dl
        call drawborder
        mov bordercolor,dl
        call highlightKing
        jmp checkhighlight
    highqueen:
        mov dl, 04h
        mov bordercolor,dl
        call drawborder
        mov bordercolor,dl
        call highlightqueen
        
    checkhighlight:
    cmp highlightflag,1
    ;je gotowhiletrue
    ;mov bl,0
    ;mov movingopflag,0
    ;gotowhiletrue:

    ret
highlightforselectedpiece endp


deletehighlight proc
    pusha
    mov di,currpos
    mov tempcurrpos,di
    mov currpos,0
    call updaterowandcol

    rows22:
        mov cx,4
        row123:
            call checkboxcolor
            cmp boxcolor,0ah
            jne noneedtodeletegreen
            call drawboxwhite
            call checkpiece
            cmp al,0
            je noneedtodeletegreen
            call drawSelectedRedPiece
            noneedtodeletegreen:
            add currpos,25
            call updaterowandcol


            call checkboxcolor
            cmp boxcolor,0ah
            jne noneedtodeletegreen2
            call drawboxgrey
            call checkpiece
            cmp al,0
            je noneedtodeletegreen2
            call drawSelectedRedPiece
            noneedtodeletegreen2:
            add currpos,25
            call updaterowandcol
            
        loop row123

        mov cx,4
        add currpos,320*25-25*8
        call updaterowandcol
        row221:
            call checkboxcolor
            cmp boxcolor,0ah
            jne noneedtodeletegreen3
            call drawboxgrey
            call checkpiece
            cmp al,0
            je noneedtodeletegreen3
            call drawSelectedRedPiece
            noneedtodeletegreen3:
            add currpos,25
            call updaterowandcol

            call checkboxcolor
            cmp boxcolor,0ah
            jne noneedtodeletegreen4
            call drawboxwhite
            call checkpiece
            cmp al,0
            je noneedtodeletegreen4
            call drawSelectedRedPiece
            noneedtodeletegreen4:
            add currpos,25
            call updaterowandcol
        loop row221

        add currpos,320*25-25*8
        call updaterowandcol
        cmp currpos,320*25*8
    jz notrows22
    jmp rows22
    notrows22:

    mov di,tempcurrpos
    mov currpos,di
    call updaterowandcol
     popa
     ret
deletehighlight endp


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
    cmp col,7
    ja notrightpawn
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
    cmp col,7
    ja endhighpawn
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


highlightKing proc
    pusha
    
        mov bx,currpos
        sub bx,320*25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedrow,0
        je piecefound1@king
        call checkpiece
        cmp al,0
        je highlight1@king

        cmp al,6
        ja enemypiecefound1@king
        jmp piecefound1@king
        
        enemypiecefound1@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound1@king
        
        highlight1@king:
        call highlightbox

        piecefound1@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol

        

        mov bx,currpos
        add bx,320*25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedrow,7
        je piecefound2@king
        call checkpiece
        cmp al,0
        je highlight2@king

        cmp al,6
        ja enemypiecefound2@king
        jmp piecefound2@king
        
        enemypiecefound2@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound2@king
        
        highlight2@king:
        call highlightbox

        piecefound2@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol



        mov bx,currpos
        sub bx,320*25+25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedrow,0
        je piecefound3@king
        cmp selectedcol,0
        je piecefound3@king
        call checkpiece
        cmp al,0
        je highlight3@king

        cmp al,6
        ja enemypiecefound3@king
        jmp piecefound3@king
        
        enemypiecefound3@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound3@king
        
        highlight3@king:
        call highlightbox

        piecefound3@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol



        mov bx,currpos
        sub bx,320*25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedrow,0
        je piecefound4@king
        cmp selectedcol,7
        je piecefound4@king
        call checkpiece
        cmp al,0
        je highlight4@king

        cmp al,6
        ja enemypiecefound4@king
        jmp piecefound4@king
        
        enemypiecefound4@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound4@king
        
        highlight4@king:
        call highlightbox

        piecefound4@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol



        mov bx,currpos
        add bx,320*25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedrow,7
        je piecefound5@king
        cmp selectedcol,0
        je piecefound5@king
        call checkpiece
        cmp al,0
        je highlight5@king

        cmp al,6
        ja enemypiecefound5@king
        jmp piecefound5@king
        
        enemypiecefound5@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound5@king
        
        highlight5@king:
        call highlightbox

        piecefound5@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol



        
        mov bx,currpos
        add bx,320*25+25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedrow,7
        je piecefound6@king
        cmp selectedcol,7
        je piecefound6@king
        call checkpiece
        cmp al,0
        je highlight6@king

        cmp al,6
        ja enemypiecefound6@king
        jmp piecefound6@king
        
        enemypiecefound6@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound6@king
        
        highlight6@king:
        call highlightbox

        piecefound6@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol


        mov bx,currpos
        add bx,25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,7
        je piecefound7@king
        call checkpiece
        cmp al,0
        je highlight7@king

        cmp al,6
        ja enemypiecefound7@king
        jmp piecefound7@king
        
        enemypiecefound7@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound7@king
        
        highlight7@king:
        call highlightbox

        piecefound7@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol




        mov bx,currpos
        sub bx,25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,0
        je piecefound8@king
        call checkpiece
        cmp al,0
        je highlight8@king
        cmp al,6
        ja enemypiecefound8@king
        jmp piecefound8@king
        
        enemypiecefound8@king:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound8@king
        
        highlight8@king:
        call highlightbox

        piecefound8@king:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol



    popa
    ret
highlightKing endp


highlightknight proc
    pusha
       
        mov bx,currpos
        sub bx,320*25-25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,5
        ja piecefound2xy1@Knight
        cmp selectedrow,0
        je piecefound2xy1@Knight
        call checkpiece
        cmp al,0
        je highlight2xy1@Knight

        cmp al,6
        ja enemypiecefound2xy1@Knight
        jmp piecefound2xy1@Knight
        
        enemypiecefound2xy1@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound2xy1@Knight
        
        highlight2xy1@Knight:
        call highlightbox

        piecefound2xy1@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
        


        mov bx,currpos
        sub bx,320*25+25+25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        cmp selectedrow,0
        je piecefoundneg2xy@Knight
        cmp selectedcol,2
        jb piecefoundneg2xy@Knight
        
        call checkpiece
        cmp al,0
        je highlightneg2xy@Knight

        cmp al,6
        ja enemypiecefoundneg2xy@Knight
        jmp piecefoundneg2xy@Knight
        
        enemypiecefoundneg2xy@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundneg2xy@Knight
        
        highlightneg2xy@Knight:
        call highlightbox

        piecefoundneg2xy@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol

        
        mov bx,currpos
        add bx,320*25-25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,2
        jb piecefoundneg2xnegy@Knight
        cmp selectedrow,7
        je piecefoundneg2xnegy@Knight
        call checkpiece
        cmp al,0
        je highlightneg2xnegy@Knight

        cmp al,6
        ja enemypiecefoundneg2xnegy@Knight
        jmp piecefoundneg2xnegy@Knight
        
        enemypiecefoundneg2xnegy@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundneg2xnegy@Knight
        
        highlightneg2xnegy@Knight:
        call highlightbox

        piecefoundneg2xnegy@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol


        mov bx,currpos
        add bx,320*25+25+25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,5
        ja piecefound2xnegy@Knight
        cmp selectedrow,7
        je piecefound2xnegy@Knight
        call checkpiece
        cmp al,0
        je highlight2xnegy@Knight

        cmp al,6
        ja enemypiecefound2xnegy@Knight
        jmp piecefound2xnegy@Knight
        
        enemypiecefound2xnegy@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefound2xnegy@Knight
        
        highlight2xnegy@Knight:
        call highlightbox

        piecefound2xnegy@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol

        
        mov bx,currpos
        sub bx,2*320*25+25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,0
        je piecefoundnegx2y@Knight
        cmp selectedrow,2
        jb piecefoundnegx2y@Knight
        call checkpiece
        cmp al,0
        je highlightnegx2y@Knight

        cmp al,6
        ja enemypiecefoundnegx2y@Knight
        jmp piecefoundnegx2y@Knight
        
        enemypiecefoundnegx2y@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundnegx2y@Knight
        
        highlightnegx2y@Knight:
        call highlightbox

        piecefoundnegx2y@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol


        mov bx,currpos
        sub bx,2*320*25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,7
        je piecefoundx2y@Knight
        cmp selectedrow,2
        jb piecefoundx2y@Knight
        call checkpiece
        cmp al,0
        je highlightx2y@Knight

        cmp al,6
        ja enemypiecefoundx2y@Knight
        jmp piecefoundx2y@Knight
        
        enemypiecefoundx2y@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundx2y@Knight
        
        highlightx2y@Knight:
        call highlightbox

        piecefoundx2y@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
        
        
        mov bx,currpos
        add bx,2*320*25+25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,7
        je piecefoundxneg2y@Knight
        cmp selectedrow,5
        ja piecefoundxneg2y@Knight
        call checkpiece
        cmp al,0
        je highlightxneg2y@Knight

        cmp al,6
        ja enemypiecefoundxneg2y@Knight
        jmp piecefoundxneg2y@Knight
        
        enemypiecefoundxneg2y@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundxneg2y@Knight
        
        highlightxneg2y@Knight:
        call highlightbox

        piecefoundxneg2y@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
        

        mov bx,currpos
        add bx,2*320*25-25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        cmp selectedcol,0
        je piecefoundnegxneg2y@Knight
        cmp selectedrow,5
        ja piecefoundnegxneg2y@Knight
        call checkpiece
        cmp al,0
        je highlightnegxneg2y@Knight

        cmp al,6
        ja enemypiecefoundnegxneg2y@Knight
        jmp piecefoundnegxneg2y@Knight
        
        enemypiecefoundnegxneg2y@Knight:
        call highlightbox
        call drawSelectedRedPiece
        jmp piecefoundnegxneg2y@Knight
        
        highlightnegxneg2y@Knight:
        call highlightbox

        piecefoundnegxneg2y@Knight:

        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
        
       
    popa
    ret
highlightKnight endp

highlightqueen proc
    pusha

    call highlightrook
    call highlightbishop

    popa
highlightqueen endp

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