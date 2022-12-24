.model small
.286
.data
num dw 3456
mes db 'This is message','$'
InDATA db 6,?,6 dup('$')
Innum db 5,?,4 dup('$')
Score db "Score$"
winingmsg db "You Won $"
losingmsg db  "You Lost $"
uquitedmsg db  "You Quited $"
opquitedmsg db  "Your Opponent Quited $"
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
mykingdead db 0
opkingdead db 0
waitingtime dw 3
powerupflag db 0
startingflag db 0
iquited db 0
opquited db 0
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
drawX dw 0
drawY dw 0
oponentdeadpieces dw 0  ;stores the number of dead pieces of the opponent, to be sent to the opponent
mydeadpieces dw 0       ;stores the number of dead pieces of the player, to be recieved from the opponent
poweruprow dw 0
powerupcol dw 0

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

        cmp startingflag,1
        jne noneedtogeneratepowerup
        
        cmp currmin,0
        jne noneedtogeneratepowerup

        cmp currsec,50
        jne noneedtogeneratepowerup

        cmp powerupflag,0
        jne noneedtogeneratepowerup

        mov cl,1
        mov powerupflag,cl
        call GeneratePowerUp

        noneedtogeneratepowerup:
        cmp mykingdead,1        ;TODO according to who won or lost display you won or you lost
        jne checkopking
        jmp endgame
        
        checkopking:
        cmp opkingdead,1
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
        je iquit
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
    

    iquit:
    mov cl,1
    mov iquited,cl

    endgame:
    cmp mykingdead,1
    jne youwon
    ;TODO display myplayer name lost for 4 seconds
    DisplayString losingmsg
    jmp gotomenu

    youwon:
    cmp opkingdead,1
    jne gamecanceled
    ;TODO display myplayer name won for 4 seconds
    DisplayString winingmsg
    jmp gotomenu


    gamecanceled:
    cmp iquited,1
    jne otheropquited 
    ;TODO display myplayer name quited the game for 4 seconds
    DisplayString uquitedmsg
    jmp gotomenu

    otheropquited:
    ;TODO display oponent name quited the game for 4 seconds
    DisplayString opquitedmsg
   

    gotomenu:
    call updatetime
    mov al,currsec
    add al,4
    call updatetime
    cmp currsec,al
    jb gotomenu
    call menu

    MOV AH, 4CH
    MOV AL, 00 ;your return code.
    INT 21H
main endp


end main