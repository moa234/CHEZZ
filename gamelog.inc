.code
Displaytime proc   
    pusha
    MOVECURSOR 40-6,24      ;move to location of time to diplay
    DisplayNumber currmin   ;display the minutes
    DisplayChar ':'         ;display the colon
    DisplayNumber currsec   ;display the seconds
    popa
    ret
Displaytime endp

GeneratePowerUp proc 
    ;this proc generates a powerup in a random empty box during the game, 
    ;if a piece moves to that box it will have less time restriction 2sec instead of 3sec

    ;so, first we need to generate a random row and col and check that it is empty (doesn't contain any piece)
    pusha

    checkifemptybox:
    rand1:
    MOV AH, 00h       ; interrupts to get system time        
    INT 1AH           ; CX:DX now hold number of clock ticks since midnight      
    mov  ax, dx
    xor  dx, dx
    mov  cx, 10    
    div  cx           ; here dx contains the remainder of the division - from 0 to 9
    cmp dl,7
    ja rand1
    mov dh,0
    mov bx,dx 
    
    rand2:
    MOV AH, 00h       ; interrupts to get system time        
    INT 1AH           ; CX:DX now hold number of clock ticks since midnight      
    mov  ax, dx
    xor  dx, dx
    mov  cx, 10    
    div  cx           ; here dx contains the remainder of the division - from 0 to 9
    cmp dl,7
    ja rand2
    mov dh,0
    mov si,dx 

    mov ax,bx
    mov cx,8
    mul cx
    mov bx,ax
    cmp board[bx][si],0   ;here we must check that the random generated position on the board is empty to add the powerup at this position
    jne checkifemptybox
    mov bx,40;;;;;;;;;;remove
    mov si,1;;;;;;;;;;remove
    mov board[bx][si], 44  ;we are going to define that powerupvalue is = 44, to recognize its place on the board
    mov cl,3
    shr bx,cl              ;here we divide the row by 8 to get the row in the board
    
    mov poweruprow,bx      ;store the row of the powerup in the poweruprow variable
    mov powerupcol,si      ;store the col of the powerup in the powerupcol variable
    call sendPowerup

    ;mov ax,bx
    ;mov bx,25
    ;mul bx
    ;mov bx,ax
    ;add bx,7                ;to centralize the cursor in box

    ;mov ax,si
    ;mov bx,25
    ;mul bx
    ;mov si,ax
    ;add si,7                ;to centralize the cursor in box
    
    ;Todo: display the powerup in the box
   
    popa
    ret
GeneratePowerUp endp 

displayopdeadpieces proc
    pusha
    MOVECURSOR 42-6,3    ;move to location of opponent dead pieces to diplay
    DisplayNumber oponentdeadpieces   ;display opponent dead pieces
    popa
    ret
displayopdeadpieces endp

displaymydeadpieces proc
    pusha
    MOVECURSOR 33-6,3    ;move to location of opponent dead pieces to diplay
    DisplayNumber mydeadpieces   ;display opponent dead pieces
    popa
    ret
displaymydeadpieces endp

displaygamenotifbar proc
pusha  

MOVECURSOR 40-6,1
DisplayString Score     ;TODO score will be replaced by myplayername and remove the var score from .data

MOVECURSOR 32-6,1
DisplayString score     ;TODO score will be replaced by oponentname and remove the var score from .data

call displayopdeadpieces
call displaymydeadpieces
popa
ret
displaygamenotifbar endp

updatetime proc
    pusha

    getsystemtime       ;get the current time
    cmp dh, startsec    ;compare the current seconds with the start seconds
    jb currsecas8ar     ;if the current seconds are less than the start seconds, then we need to add 60 to current second

    cmp cl, startmin    ;compare the current minutes with the start minutes
    jb currminas8ar     ;if the current minutes are less than the start minutes, then we need to add 60 to current minutes
    jmp incmin          ;else, increment the minutes

    currminas8ar:       
    add cl,60           ;add 60 to smaller current time to handle a special case
    
    incmin:
    sub cl,startmin     ;subtract the start time from the current time
    mov currmin,cl      ;store the current time in the currmin variable
    jmp incsec          ;increment the seconds

    currsecas8ar:
    add dh,60           ;add 60 to smaller current time to handle a special case

    incsec:
    sub dh,startsec     ;subtract the start time from the current time
    mov currsec,dh      ;store the current time in the currsec variable

    popa
    ret
updatetime endp

updatepiecestime proc
    pusha
    ;get position of piece in timer board which is 8*8 word array
    mov bx,row
    mov ax,16
    mul bx
    mov bx,ax
    mov si,col
    mov ax,2
    mul si
    mov si,ax

    ;store the current time in the timer board
    mov al,currsec
    mov ah,currmin  
    mov timerboard[bx][si],ax

    popa
    ret
updatepiecestime endp

sendmove proc             
    pusha
    sendserial row
    sendserial col
    sendserial selectedrow
    sendserial selectedcol
    POPa
    ret
sendmove endp

; recievemove proc
;     pusha
;     recieveserial enemyrow
;     cmp enemyrow,-1
;     je notamove
;     recieveserialwait enemycol
;     recieveserialwait enemyselectedrow
;     recieveserialwait enemyselectedcol
;     mov ax,enemyselectedcol
;     mov waitingtime,ax
;     notamove:
;     mov enemyrow,-1
;     POPa
;     ret
; recievemove endp

sendPowerup proc
    pusha
    sendserial 200
    sendserial powerupcol
    sendserial poweruprow
    popa
    ret
sendPowerup endp

recievedata proc
    
    recieveserial recieveddata
    cmp recieveddata,-1
    jne smthrecieved
    jmp nothingrecieved
    smthrecieved:
    cmp recieveddata,8
    jb enemymove
    cmp recieveddata,200
    jne nopoweruprecieved
    jmp poweruprecieved
    nopoweruprecieved:
    jmp chatrecieved

    enemymove:
        mov ax,recieveddata
        mov row,ax
        recieveserialwait col
        recieveserialwait selectedrow
        recieveserialwait selectedcol
        mov ax,7
        sub ax,row
        mov row,ax
        mov ax,7
        sub ax,col
        mov col,ax
        mov ax,7
        sub ax,selectedrow
        mov selectedrow,ax
        mov ax,7
        sub ax,selectedcol
        mov selectedcol,ax

        mov ax,currpos
        mov enemytemppos,ax

        call updatecurrpos
        call updateselectedpos
        call moveenemypiece
        call updatepiecestime

        mov ax,enemytemppos
        mov currpos,ax
        mov recieveddata,-1

    ret

    poweruprecieved:
        recieveserialwait powerupcol 
        recieveserialwait poweruprow
        mov ax,7
        sub ax,poweruprow
        mov poweruprow,ax

        mov ax,7
        sub ax,powerupcol
        mov powerupcol,ax

        mov bx,poweruprow
        mov cl,3
        shl bx,cl                ;we need to multiply the poweruprow by 8 to get the actual row on the board
        mov si,powerupcol
        mov board[bx][si],44
        mov recieveddata,-1
    ret


    chatrecieved:

        mov recieveddata,-1
    ret

    nothingrecieved:
        mov recieveddata,-1
    ret
recievedata endp

moveenemypiece proc
    mov bx,selectedrow
    mov ax,8
    mul bx
    mov bx,ax                 
    mov si,selectedcol

    mov cl,board[bx][si]
    mov board[bx][si],0
    call deleteselctedpiece
    
    mov bx,row
    mov ax,8
    mul bx
    mov bx,ax                 
    mov si,col
    cmp board[bx][si],0
    je mypiecenotdead
    cmp board[bx][si],44
    je mypiecenotdead
    mov ax,1
    add mydeadpieces,1
    call displaymydeadpieces
    cmp board[bx][si],3
    jne mypiecenotdead
    mov al,1
    mov mykingdead,al
    mypiecenotdead:
    mov board[bx][si],cl
    mov al,cl
    call delnewposhighlight
    call drawSelectedPiece

    ret
moveenemypiece endp

updatecurrpos proc
    pusha
    mov ax, row
    mov bx,25
    mul bx
    mov pixelrow, ax
    
    mov ax, col
    mov bx,25
    mul bx
    mov pixelcol, ax

    mov ax,pixelrow
    mov bx,320
    mul bx
    mov dx,pixelcol
    add ax,dx
    mov currpos,ax

    popa
    ret
updatecurrpos endp

updateselectedpos proc
    pusha
    mov ax, selectedrow
    mov bx,25
    mul bx
    mov selectedpixelrow, ax
    
    mov ax, selectedcol
    mov bx,25
    mul bx
    mov selectedpixelcol, ax

    mov ax,selectedpixelrow
    mov bx,320
    mul bx
    mov dx,selectedpixelcol
    add ax,dx
    mov selectedpos,ax

    popa
    ret
updateselectedpos endp

updaterowandcol proc
    pusha
    ;here we store the pixelrow and pixelcol according to currpos as they are easier to draw with rather than normal row and col
    mov ax, currpos
    mov bx,320
    mov dx,0
    div bx
    mov pixelrow, ax
    mov pixelcol, dx
    push dx

    ;here we use pixelrow and pixelcol to get normal row and col to be used in addressing the board, (row is not multiplied with 8, when row will be used to access the board it will be multiplied by 8 first)
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

delnewposhighlight proc        ;this procedure removes only the highlight of the desination box before the piece moves to it
   pusha
   GetPixelColour pixelcol, pixelrow        ;we get the main pixel color the destination box   
   cmp al,07h                               ;check if box color is grey 
   jne boxiswhitee
   call drawboxgrey
   jmp drawingfinished
   boxiswhitee:
   call drawboxwhite
   drawingfinished:
   popa
   ret
delnewposhighlight endp

traversecell proc                           ;this proc allows us to move between board cells, it is call after a keypress
    pusha                                   ;the scancode of the keypressed is stored in the register ah
    cmp ah, 48h                             ;if keypressed is uparrow
    je upkey
    cmp ah, 4dh                             ;if keypressed is rightarrow
    je rightkey
    cmp ah, 4bh                             ;if keypressed is leftarrow
    je leftkey
    cmp ah, 50h                             ;if keypressed is down arrow
    je downkey

    jmp notarrow
    upkey:
        cmp row, 0                          ;check if we are at the top of the board, if yes do nothing
        je notarrow
        call deleteborder                   ;delete border from old cell
        sub currpos,320*25                  ;update currpos
        call drawborder                     ;draw the border at the new cell
        jmp notarrow
    rightkey:
        cmp col, 7                          ;check if we are at the most right of the board, if yes do nothing
        je notarrow
        call deleteborder                   ;delete border from old cell
        add currpos,25                      ;update currpos
        call drawborder                     ;draw the border at the new cell
        jmp notarrow
    leftkey:
        cmp col, 0                          ;check if we are at the most left of the board, if yes do nothing
        je notarrow
        call deleteborder                   ;delete border from old cell
        sub currpos,25                      ;update currpos
        call drawborder                     ;draw the border at the new cell
        jmp notarrow
    downkey:
        cmp row, 7                          ;check if we are at the bottom of the board, if yes do nothing
        je notarrow
        call deleteborder                   ;delete border from old cell
        add currpos,320*25                  ;update currpos
        call drawborder                     ;draw the border at the new cell
        jmp notarrow
        
    notarrow:
    popa
    ret
traversecell endp

deleteselctedpiece proc            ;this proc deletes the piece from an old cell position to be able to move to a new cell
    pusha
    GetPixelColour selectedpixelcol, selectedpixelrow           ;we need to kmow the box color(grey or white) of the old (selected) cell
    mov di,currpos
    mov tempcurrpos,di             ;here a temp var is used as proc drawbox uses var currpos and it changes it, while we need to keep the currpos as it is after ret 
    mov di,selectedpos             
    mov currpos,di                 ;mov the selected position to the currpos 
    cmp al,07h                     ;check if the box color is grey
    jne boxiswhite                 
    call drawboxgrey
    jmp drawisfinished
    boxiswhite:
    call drawboxwhite
    drawisfinished:
    mov di,tempcurrpos             ;change back the currpos to the same currpos that was entering this proc
    mov currpos,di
    popa
    ret
deleteselctedpiece endp

movefromcelltocell proc            ;this proc is responsible for moving a piece from a cell to another
    pusha
    mov bx,row                     
    mov ax,8
    mul bx
    mov bx,ax                      ;bx store row*8 -> to  allow addressing in the board array
    mov si,col                     ;SI store  col
    
    cmp movingopflag,1             ;moving flag indicates whether the piece is selected and is ready to move or not 1->selected-ready to move
    je movingflagon

    cmp board[bx][si],0           
    jne skipnomovneededrelerror
    jmp nomovingneeded              ;moving flag = 0 and no piece in this box so do nothing
    skipnomovneededrelerror:        ;moving flag = 0 and there is a piece in this box -> we will set moving flag in the upcoming instructions
    call checktimeofpiece
    cmp selectflag,0                ;select flag is already set in selection proc, so if no piece selected no moving will be needed
    jne nomovingneeded_rev
    jmp nomovingneeded
    nomovingneeded_rev:

    mov di,1
    mov movingopflag,di
    jmp nomovingneeded        ;we will set moving flag (=1) as moving flag was 0 and there is a piece in this cell

    movingflagon:
    mov bx,row
    mov ax,8
    mul bx
    mov bx,ax                 ;bx store row*8
    mov si,col                ;SI store  col
    cmp board[bx][si], 44     ;here we check that if the destination box conatain a powerup or not
    jne nopowerup
    mov ax,2                  
    mov waitingtime,ax        ;if powerup is found in destination cell and taken by piece, set the waiting time of this piece's team to be 2sec instead of 3sec
    nopowerup:
    cmp board[bx][si], 12     ;check if the king is in the destination cell
    jne kingnotdead
    ;mov ax,1
    ;add oponentdeadpieces,ax   ;if king is killed, add 1 to the oponent dead pieces counter
    ;call displayopdeadpieces
    mov al,1
    mov opkingdead,al           ;if king is found and move the piece and set kingdead flag to 1
    kingnotdead:
    cmp board[bx][si],6       ;red team pieces values are all above 6, so here we check if destination box has a red piece or blue piece 
    ja killingapiece          ;if destination box has an enemy piece, then we will kill it and add 1 to the oponent dead pieces counter
    cmp board[bx][si],0       ;check if the destination cell is empty
    je movingneeded
    jmp nomovingneeded
    killingapiece:
    cmp board[bx][si],44      ;check if the destination cell has a powerup
    je movingneeded
    mov ax,1
    add oponentdeadpieces,ax 
    call displayopdeadpieces
    movingneeded: 
    call upgradepawn              ;check if there is a pawn that reached the top of the board and needs to be promoted

    call sendmove

    mov al,selectedpiece
    mov board[bx][si],al          ;add the value of the selected piece to it's neew location in the 2d array board
    mov dl,01h
    mov bordercolor,dl            ;change border color to blue
    call delnewposhighlight       ;delete highlight of destination cell
    call drawborder               ;we need to call drawborder proc to draw the border at the destination box
    call drawSelectedPiece    ;draw the moving piece at the destination cell

    mov bx,selectedrow
    mov ax,8
    mul bx
    mov bx,ax                ;bx store selectedrow*8
    mov si,selectedcol       ;si store selected col

    mov dl,0
    mov board[bx][si],dl
    call deleteselctedpiece      ;delete piece from old cell

    mov dx,0
    mov movingopflag,dx          ;reset the movingflag
    mov selectedpiece,dl         ;empty the value of the moved piece from its old location in the 2d array board

    call updatepiecestime

    nomovingneeded:
    popa
    ret
movefromcelltocell endp

checktimeofpiece proc
    
    ;get index of piece in timerboard by multyping row by 8*2 as it is stored as word then adding column
    mov bx,row
    mov ax,16
    mul bx
    mov bx,ax
    mov si,col
    mov ax,2
    mul si
    mov si,ax

    mov bx, timerboard[bx][si]  ;bx store the value of the piece in the timerboard

    cmp bx,-3
    je canmove                 ;if the value of the piece in the timerboard is -3, it means that the piece did not move before

    add bx,waitingtime          ;add the waiting time of the piece's team to the value of the piece in the timerboard

    cmp bl,60                   ;check if the value of the piece in the timerboard is more than 60 sec
    jb NotInNextMinute          ;if not, jump to the next instruction
    sub bl,60                   ;if yes, subtract 60 from the value of the piece in the timerboard and move to next minute
    inc bh                      ;increment minute
    NotInNextMinute:

    cmp currmin,bh              ;compare the current minute with the last move of piece + waitingtime
    jb cantmove                 ;if current minute is less than the last move of piece + waitingtime, the piece can't move
    ja canmove                  ;if current minute is more than the last move of piece + waitingtime, the piece can move

    cmp currsec,bl              ;else if minutes are equal, compare the current second with the last move of piece + waitingtime
    jae canmove                 ;piece can move if it is equal or greater
    jmp cantmove                ;else it cannot move
    canmove:
        mov selectflag,1        ;sets selection flag to true as the piece can move so it can be selected
        jmp endselectmove       
    cantmove:
        mov selectflag,0        ;sets selection flag to false as the piece can't move so it can't be selected
    endselectmove:
    ret
checktimeofpiece endp

highlightforselectedpiece proc     ;this proc see the value of the selected piece to know the type of the piece to be able to call the appropriate highlight procedure
    cmp selectflag,0               ;if select flag = 0, no piece is selected so do nothing
    jne selecthighlight
    jmp checkhighlight
    selecthighlight:               ;jmp to an appropriate higghlight proc according to the selectedpiece value
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
        
    jmp checkhighlight             ;if piece type is none of the prev, do nothing
    highpawn:
        mov dl, 04h
        mov bordercolor,dl         ;set border color to red
        call drawborder            ;drawborder
        mov bordercolor,dl         ;border color changes inside drawborder proc and we need to change it to red again
        call highlightpawn         ;draw highlight suitaable for the pawn moves
        jmp checkhighlight
    highRook:
        mov dl, 04h
        mov bordercolor,dl         ;set border color to red
        call drawborder            ;drawborder
        mov bordercolor,dl         ;border color changes inside drawborder proc and we need to change it to red again
        call highlightrook         ;draw highlight suitaable for the hook moves
        jmp checkhighlight
    highbishop:
        mov dl, 04h
        mov bordercolor,dl        ;set border color to red
        call drawborder           ;drawborder 
        mov bordercolor,dl        ;border color changes inside drawborder proc and we need to change it to red again
        call highlightbishop      ;draw highlight suitaable for the bishop moves
        jmp checkhighlight
    highknight:
        mov dl, 04h
        mov bordercolor,dl       ;set border color to red
        call drawborder          ;drawborder
        mov bordercolor,dl       ;border color changes inside drawborder proc and we need to change it to red again
        call highlightknight     ;draw highlight suitaable for the knight moves
        jmp checkhighlight
    highking:
        mov dl, 04h
        mov bordercolor,dl       ;set border color to red
        call drawborder          ;drawborder
        mov bordercolor,dl       ;border color changes inside drawborder proc and we need to change it to red again
        call highlightKing       ;draw highlight suitaable for the king moves
        jmp checkhighlight
    highqueen:
        mov dl, 04h              ;set border color to red
        mov bordercolor,dl       ;drawborder
        call drawborder          ;border color changes inside drawborder proc and we need to change it to red again
        mov bordercolor,dl       ;draw highlight suitaable for the queen moves
        call highlightqueen
        
    checkhighlight:
    ;cmp highlightflag,1
    ;je gotowhiletrue
    ;mov bl,0
    ;mov movingopflag,0
    ;gotowhiletrue:

    ret
highlightforselectedpiece endp

upgradepawn proc
    pusha

    cmp selectedpiece,1
    jne notpawn

    cmp row,0
    jne notpawn

    mov al,2
    mov selectedpiece,al

    notpawn:
    popa
    ret
upgradepawn endp

drawpiecestimer proc
    pusha
    mov di,currpos
    mov tempcurrpos,di
    mov currpos,11*320+3
    

    checkrow:
        call updaterowandcol
        call checktimeofpiece

        cmp currmin,bh
        jb sixtysubcurrsec
        sub bl,currsec
        jmp no60sub
        sixtysubcurrsec:
        mov cl,60
        sub cl,currsec
        add bl,cl
        no60sub:

        cmp waitingtime,2
        je powerupdrawtimer
        cmp bl,0
        jne not0
        call deletetimer
        not0:
        cmp selectflag,1
        je not1powerup
        cmp bl,3
        jne not3
        call draw3
        jmp not1powerup
        not3:
        cmp bl,2
        jne not2
        call draw2
        jmp not1powerup
        not2:
        cmp bl,1
        jne not1
        call draw1
        not1:
        jmp not1powerup
        

        powerupdrawtimer:
        cmp bl,0
        jne not0powerup
        call deletetimer
        not0powerup:
        cmp selectflag,1
        je not1powerup
        cmp bl,2
        jne not2powerup
        call draw2
        jmp not1powerup
        not2powerup:
        cmp bl,1
        jne not1powerup
        call draw1
        not1powerup:

        cmp col,7
        jne samerow@timerdraw
        add currpos,320*25-8*25
        cmp row,7
        je lastcell
        samerow@timerdraw:
        add currpos,25
        
    jmp checkrow

    lastcell:

    mov di,tempcurrpos
    mov currpos,di
    call updaterowandcol

    popa
    ret
drawpiecestimer endp

deletehighlight proc      ;this proc removes the highlight of each piece after moving or cancling moving
    pusha
    mov di,currpos        ;storing the currpos in a temp var to save it, to return it back before ret
    mov tempcurrpos,di
    mov currpos,0
    call updaterowandcol       ;get the current row and col using the currpos

    rows22:                    ;here we pass on the cells on the board and check it is green to make it white or grey, it depends on the default sequence of the white and grey cells on the board
        mov cx,4
        row123:
            call checkboxcolor           ;check if box color is green
            cmp boxcolor,0ah
            jne noneedtodeletegreen
            call drawboxwhite            ;draw whitebox
            call checkpiece              
            cmp al,0                     ;check if there is no piece in the cell
            je noneedtodeletegreen
            cmp al,44
            jne notapowerup
            ;TODO draw poweruphere
            notapowerup:
            call drawSelectedPiece    ;if there is piece in the box we need to redraw it after drawing the white/grey box
            noneedtodeletegreen:
            add currpos,25               ;update the currpos to goto the next box
            call updaterowandcol         ;update teh row and col for the new currpos 

 
            call checkboxcolor           ;check if box color is green
            cmp boxcolor,0ah
            jne noneedtodeletegreen2
            call drawboxgrey             ;draw greybox
            call checkpiece
            cmp al,0                     ;check if there is no piece in the cell
            je noneedtodeletegreen2
            call drawSelectedPiece    ;if there is piece in the box we need to redraw it after drawing the white/grey box
            noneedtodeletegreen2:
            add currpos,25               ;update the currpos to goto the next box
            call updaterowandcol         ;update the row and col for the new currpos 
            
        loop row123

        mov cx,4
        add currpos,320*25-25*8          ;move to the next row
        call updaterowandcol             ;update the row and col for the new currpos 
        row221:
            call checkboxcolor           ;check if box color is green
            cmp boxcolor,0ah
            jne noneedtodeletegreen3
            call drawboxgrey             ;draw greybox
            call checkpiece
            cmp al,0                     ;check if there is no piece in the cell
            je noneedtodeletegreen3
            call drawSelectedPiece    ;if there is piece in the box we need to redraw it after drawing the white/grey box
            noneedtodeletegreen3:
            add currpos,25               ;update the currpos to goto the next box
            call updaterowandcol         ;update the row and col for the new currpos 

            call checkboxcolor           ;check if box color is green
            cmp boxcolor,0ah    
            jne noneedtodeletegreen4
            call drawboxwhite            ;draw whitebox
            call checkpiece
            cmp al,0                     ;check if there is no piece in the cell
            je noneedtodeletegreen4
            call drawSelectedPiece    ;if there is piece in the box we need to redraw it after drawing the white/grey box
            noneedtodeletegreen4:
            add currpos,25               ;update the currpos to goto the next box
            call updaterowandcol         ;update the row and col for the new currpos
        loop row221

        add currpos,320*25-25*8          ;move to the next row
        call updaterowandcol             ;update the row and col for the new currpos
        cmp currpos,320*25*8             ;check if we finished the cells or not
    jz notrows22
    jmp rows22
    notrows22:

    mov di,tempcurrpos                   ;return back the entering currpos
    mov currpos,di
    call updaterowandcol                 ;update the row and col for the new currpos
    popa
    ret
deletehighlight endp


highlightpawn proc
    pusha
    
    ;sets the highlight position to the cell just above the pawn
    mov bx,currpos          
    sub bx,320*25
    mov highlightpos,bx
    mov currpos,bx
    call updaterowandcol

    ;then checks for a piece in that cell
    ;if there is a piece, it will not highlight the cell
    ;if there is no piece, it will highlight the cell
    call checkpiece
    cmp al,0
    je nopiece
    cmp al,44
    je nopiece
    jmp pawnstart
    nopiece:
    call highlightbox

    ;then it will check if the pawn is in the starting position
    cmp selectedrow,6
    jne pawnstart

    ;if it is in the starting position, it will check the cell 2 cells above it to highlight
    mov bx,currpos
    sub bx,320*25
    mov currpos,bx
    call updaterowandcol
    mov highlightpos,bx

    ;then checks for a piece in that cell
    ;if there is a piece, it will not highlight the cell
    ;if there is no piece, it will highlight the cell
    call checkpiece
    cmp al,0
    je nopiece2
    cmp al,44
    je nopiece2
    jmp pawnstart
    nopiece2:
    call highlightbox
    pawnstart:
    
    ;return the currpos to the original position
    mov ax,selectedpos
    mov currpos,ax
    call updaterowandcol

    ;sets highlight position in the cell to the top right of the pawn
    sub ax,320*25-25
    mov currpos,ax
    call updaterowandcol
    ;checks if the pawn is in the rightmost column to not highlight the cell
    cmp col,7
    ja notrightpawn
    mov highlightpos,ax

    ;then checks for a piece in that cell
    ;if there is a piece, it will not highlight the cell
    ;if there is no piece, it will highlight the cell
    call checkpiece
    cmp al,44
    je notrightpawn
    cmp al,6
    ja enemypiece
    jmp notrightpawn
    enemypiece:
    call highlightbox
    ;if the piece is an enemy piece, it will draw the piece in red
    call drawSelectedPiece
    notrightpawn:

    ;sets highlight position in the cell to the top left of the pawn
    mov ax,currpos
    sub ax,50
    mov currpos,ax
    call updaterowandcol
    ;checks if the pawn is in the leftmost column to not highlight the cell
    cmp col,7
    ja endhighpawn
    mov highlightpos,ax

    ;then checks for a piece in that cell
    ;if there is a piece, it will not highlight the cell
    ;if there is no piece, it will highlight the cell
    call checkpiece
    cmp al,44
    je endhighpawn
    cmp al,6
    ja enemypiece2
    jmp endhighpawn
    enemypiece2:
    call highlightbox
    ;if the piece is an enemy piece, it will draw the piece in red
    call drawSelectedPiece
    endhighpawn:

    ;return the currpos to the original position
    mov ax,selectedpos
    mov currpos,ax
    call updaterowandcol

    popa
    ret
highlightpawn endp

highlightRook proc
    pusha
    ;a loop to check the cells above the rook
    whilenopieceup@Rook:
        ;check if the rook is in the top row
        ;if it is, it will not highlight the cells above it
        cmp row,0
        je piecefoundup@rook
        ;sets the highlight position to the cell above the rook and then the one above it and so on
        mov bx,currpos
        sub bx,320*25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        ;then checks for a piece in that cell
        ;if there is friend a piece, it will not highlight the cell
        ;if there is an enemy piece, it will highlight the cell and draw the piece in red
        call checkpiece
        cmp al,0
        je highlightup@rook
        cmp al,44
        je highlightup@rook
        cmp al,6
        ja enemypiecefoundup@rook
        jmp piecefoundup@rook
        enemypiecefoundup@rook:
        call highlightbox
        call drawSelectedPiece
        jmp piecefoundup@rook
        
        highlightup@rook:
        call highlightbox
        

        
        jmp whilenopieceup@Rook
        piecefoundup@rook:
    
        ;return the currpos to the original position
        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopieceleft@rook:
        ;check if the rook is in the leftmost column
        cmp col,0
        je piecefoundleft@rook
        ;sets the highlight position to the cell to the left of the rook and then the one to the left of it and so on
        mov bx,currpos
        sub bx,25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        ;then checks for a piece in that cell
        ;if there is friend a piece, it will not highlight the cell
        ;if there is an enemy piece, it will highlight the cell and draw the piece in red
        call checkpiece
        cmp al,0
        je highlightleft@rook
        cmp al,44
        je highlightleft@rook
        cmp al,6
        ja enemypiecefoundleft@rook
        jmp piecefoundleft@rook
        enemypiecefoundleft@rook:
        call highlightbox
        call drawSelectedPiece
        jmp piecefoundleft@rook
        
        highlightleft@rook:
        call highlightbox
        

        
        jmp whilenopieceleft@rook
        piecefoundleft@rook:
    
        ;return the currpos to the original position
        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopiecedown@rook:
        ;check if the rook is in the bottom row
        cmp row,7
        je piecefounddown@rook

        ;sets the highlight position to the cell below the rook and then the one below it and so on
        mov bx,currpos
        add bx,320*25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol

        ;then checks for a piece in that cell
        ;if there is friend a piece, it will not highlight the cell
        ;if there is an enemy piece, it will highlight the cell and draw the piece in red
        call checkpiece
        cmp al,0
        je highlightdown@rook
        cmp al,44
        je highlightdown@rook
        cmp al,6
        ja enemypiecefounddown@rook
        jmp piecefounddown@rook
        enemypiecefounddown@rook:
        call highlightbox
        call drawSelectedPiece
        jmp piecefounddown@rook
        
        highlightdown@rook:
        call highlightbox
        

        
        jmp whilenopiecedown@rook
        piecefounddown@rook:
    
        ;return the currpos to the original position
        mov ax,selectedpos
        mov currpos,ax
        call updaterowandcol
    
    whilenopieceright@rook:
        ;check if the rook is in the rightmost column
        ;if it is, it will not highlight the cells to the right of it
        cmp col,7
        je piecefoundright@rook

        ;sets the highlight position to the cell to the right of the rook and then the one to the right of it and so on
        mov bx,currpos
        add bx,25
        mov highlightpos,bx
        mov currpos,bx
        call updaterowandcol
        
        ;then checks for a piece in that cell
        ;if there is friend a piece, it will not highlight the cell
        ;if there is an enemy piece, it will highlight the cell and draw the piece in red
        call checkpiece
        cmp al,0
        je highlightright@rook
        cmp al,44
        je highlightright@rook
        cmp al,6
        ja enemypiecefoundright@rook
        jmp piecefoundright@rook
        enemypiecefoundright@rook:
        call highlightbox
        call drawSelectedPiece
        jmp piecefoundright@rook
        
        highlightright@rook:
        call highlightbox
        

        
        jmp whilenopieceright@rook
        piecefoundright@rook:
    
        ;return the currpos to the original position
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
        cmp al,44
        je highlightup@Bishop
        cmp al,6
        ja enemypiecefoundup@Bishop
        jmp piecefoundup@Bishop
        enemypiecefoundup@Bishop:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightleft@Bishop
        cmp al,6
        ja enemypiecefoundleft@Bishop
        jmp piecefoundleft@Bishop
        enemypiecefoundleft@Bishop:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightdown@Bishop
        cmp al,6
        ja enemypiecefounddown@Bishop
        jmp piecefounddown@Bishop
        enemypiecefounddown@Bishop:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightright@Bishop
        cmp al,6
        ja enemypiecefoundright@Bishop
        jmp piecefoundright@Bishop
        enemypiecefoundright@Bishop:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight1@king
        cmp al,6
        ja enemypiecefound1@king
        jmp piecefound1@king
        
        enemypiecefound1@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight2@king
        cmp al,6
        ja enemypiecefound2@king
        jmp piecefound2@king
        
        enemypiecefound2@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight3@king
        cmp al,6
        ja enemypiecefound3@king
        jmp piecefound3@king
        
        enemypiecefound3@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight4@king
        cmp al,6
        ja enemypiecefound4@king
        jmp piecefound4@king
        
        enemypiecefound4@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight5@king
        cmp al,6
        ja enemypiecefound5@king
        jmp piecefound5@king
        
        enemypiecefound5@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight6@king
        cmp al,6
        ja enemypiecefound6@king
        jmp piecefound6@king
        
        enemypiecefound6@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight7@king
        cmp al,6
        ja enemypiecefound7@king
        jmp piecefound7@king
        
        enemypiecefound7@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight8@king
        cmp al,6
        ja enemypiecefound8@king
        jmp piecefound8@king
        
        enemypiecefound8@king:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight2xy1@Knight

        cmp al,6
        ja enemypiecefound2xy1@Knight
        jmp piecefound2xy1@Knight
        
        enemypiecefound2xy1@Knight:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightneg2xy@Knight
        cmp al,6
        ja enemypiecefoundneg2xy@Knight
        jmp piecefoundneg2xy@Knight
        
        enemypiecefoundneg2xy@Knight:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightneg2xnegy@Knight

        cmp al,6
        ja enemypiecefoundneg2xnegy@Knight
        jmp piecefoundneg2xnegy@Knight
        
        enemypiecefoundneg2xnegy@Knight:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlight2xnegy@Knight
        cmp al,6
        ja enemypiecefound2xnegy@Knight
        jmp piecefound2xnegy@Knight
        
        enemypiecefound2xnegy@Knight:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightnegx2y@Knight

        cmp al,6
        ja enemypiecefoundnegx2y@Knight
        jmp piecefoundnegx2y@Knight
        
        enemypiecefoundnegx2y@Knight:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightx2y@Knight

        cmp al,6
        ja enemypiecefoundx2y@Knight
        jmp piecefoundx2y@Knight
        
        enemypiecefoundx2y@Knight:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightxneg2y@Knight

        cmp al,6
        ja enemypiecefoundxneg2y@Knight
        jmp piecefoundxneg2y@Knight
        
        enemypiecefoundxneg2y@Knight:
        call highlightbox
        call drawSelectedPiece
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
        cmp al,44
        je highlightnegxneg2y@Knight

        cmp al,6
        ja enemypiecefoundnegxneg2y@Knight
        jmp piecefoundnegxneg2y@Knight
        
        enemypiecefoundnegxneg2y@Knight:
        call highlightbox
        call drawSelectedPiece
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
    ;checks if selected position have a piece that can be moved
    cmp movingopflag,1
    je secondq
    ;if yes, then it will initialise the variables of selection
    ;selectedpos, selectedcol, selectedrow, selectedpixelcol, selectedpixelrow, selectedpiece
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

    ;get the piece from the 2d board array and store it in selectedpiece
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