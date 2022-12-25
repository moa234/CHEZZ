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
uquitedmsg db  "You  Quited $"
opquitedmsg db  "Opponent Quited $"
;--------------------------------------------------
MSG1 db "To start chatting press F1 $"
MSG2 db "To start the game press F2 $" 
MSG3 db "To end the program press ESC $"     
NotifLine db   "________________________________________________________________________________$"
F1notif db "You sent a chat invitation to Ahmed $"
F2notif db "You sent a game invitation to Ahmed $"
F1rec db "You recieved a chat invitation from Ahmed $"
F2rec db "You recieved a game invitation from Ahmed $"
chatinviteflag db 0
gameinviteflag db 0
invitationflag db 0
recievechatresponse dw 0
recievegameresponse dw 0
repetetionflag1 db 0
repetetionflag2 db 0
frommenutogame db 0
frommenutochat db 0
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
opquited dw 0
kingrow dw 0
kingcol dw 0
kingpixelrow dw 0
kingpixelcol dw 0
kingpos dw 0
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



include macros.inc
include gameui.inc
include gamelog.inc
include menu.inc

.code

main proc far
    mov ax,@data
    mov ds,ax
    
    ;call menu

    ;cmp frommenutogame,1
    ;jne donotrungame
    clearscreen
    call game
    ;after ret from game goto menu directly

    ;donotrungame:
    ;cmp frommenutochat,1
    ;jne donotrunchat
    ;call chat
    ;after ret from chat goto menu directly
    ;donotrunchat:

    MOV AH, 4CH
    MOV AL, 00 ;your return code.
    INT 21H
       

main endp
end main
