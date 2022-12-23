.model small
.286
.data
num dw 3456
mes db 'This is message','$'
InDATA db 6,?,6 dup('$')
Innum db 5,?,4 dup('$')
;--------------------------------------------------
MSG1 db "To start chatting press F1 $"
MSG2 db "To start the game press F2 $" 
MSG3 db "To end the program press ESC $"     
NotifLine db   "________________________________________________________________________________$"
F1notif db "You sent a chat invitation to Ahmed $"
F2notif db "You sent a game invitation to Ahmed $"
chatinviteflag db 0
gameinviteflag db 0
;--------------------------------------------------
myplayer db 16,?,16 dup('$')
opponentplayer db 16,?,16 dup('$')
startingplayer db 1
;--------------------------------------------------
currpos dw 0
row dw 0 ;0-7
col dw 0 ;0-7
pixelrow dw 0 ;0-200
pixelcol dw 0 ;0-320
;--------------------------------------------------
enemytemppos dw 0
;--------------------------------------------------
selectedpos dw 0
selectedcol dw 0
selectedrow dw 0
selectedpixelcol dw 0
selectedpixelrow dw 0
selectedpiece db 0
kingdead db 0
waitingtime dw 3
powerupflag db 0
startingflag db 1
;--------------------------------------------------
recieveddata dw -1
;--------------------------------------------------
highlightpos dw 0
highlightflag db 0
;--------------------------------------------------
movingopflag dw 0
selectflag db 1
tempcurrpos dw 0
boxcolor db 0
bordercolor db 01h
;--------------------------------------------------
oponentdeadpieces db 0  ;stores the number of dead pieces of the opponent, to be sent to the opponent
mydeadpieces db 0      ;stores the number of dead pieces of the player, to be recieved from the opponent
poweruprow dw 0
powerupcol dw 0
data dw 0
twohun db 200

board db 8,9,10,11,12,10,9,8
      db 7,7,7,7,7,7,7,7
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 1,1,1,1,1,1,1,1
      db 6,5,4,2,3,4,5,6
     
timerboard dw 8*8 dup(-3)

startsec db 0
startmin db 0
currsec db 0
currmin db 0

include menu.inc
include macros.inc
include gameui.inc
include gamelog.inc
.code
main proc far
    mov ax,@data
    mov ds,ax
    
    
    call initializegame
    initializeserial
    whiletrue:
        call recievedata

        cmp startingplayer,1
        je gotomin
        jmp checkonplayer0torecieve

        gotomin:   
        
        cmp currmin,0
        je gotosec
        jmp noneedtogeneratepowerup

        gotosec:
        cmp currsec,10
        je gotopowerflag
        jmp noneedtogeneratepowerup
        gotopowerflag:
        cmp powerupflag,0
        jne noneedtogeneratepowerup
        mov cl,1
        mov powerupflag,cl
        call GeneratePowerUp
        call sendPowerup

        checkonplayer0torecieve:
        cmp startingplayer,0
        jne noneedtogeneratepowerup
        call recievepowerup

        noneedtogeneratepowerup:
        cmp kingdead,1
        jne notendgame
        jmp endgame

        notendgame:
        call updatetime
        call Displaytime
        call drawpiecestimer
        mov selectflag,1
        cmp highlightflag,1
        jne donotchange
        cmp movingopflag,0
        jne donotchange 
        call deletehighlight

        donotchange:
        getKeyPress
        jnz whilefalse
        jmp whiletrue
        whilefalse:
        clearbuffer
        cmp ah,3eh
        je endgame
        cmp al,'q'
        je selectcell
        call traversecell
        jmp selectcell

        getout:
        mov movingopflag,0
        call deletehighlight
        mov dl,01h
        mov bordercolor,dl
        call drawborder
        selectcell:
        cmp al,'q'
        je whileq
        jmp whiletrue
        
        whileq: 
        call selection
        cmp movingopflag,1
        jne pass
        call checkboxcolor
        cmp boxcolor,0ah
        jne getout
        pass:
        
        call movefromcelltocell
        call highlightforselectedpiece


    jmp whiletrue
    
    endgame:
    call menu

    MOV AH, 4CH
    MOV AL, 00 ;your return code.
    INT 21H
main endp

recievedata proc
    
    recieveserial recieveddata
    cmp recieveddata,-1
    jne smthrecieved
    jmp nothingrecieved
    smthrecieved:
    cmp recieveddata,8
    jb enemymove
    cmp recieveddata,200
    jb nopoweruprecieved
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

end main