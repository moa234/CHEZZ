include macros.inc
.code

menu proc
pusha
TEXTMODE
;PRINT MAIN SCREEN
clearscreen
MOVECURSOR 19h, 5h   
DisplayString MSG1 
GETCURSOR 
add dh,4
MOVECURSOR 19h, dh 
DisplayString MSG2 
GETCURSOR 
add dh,4
MOVECURSOR 19h, dh 
DisplayString MSG3      
;PRINT NOTIFICATION BAR LINE
MOVECURSOR 0, 14h 
DisplayString NotifLine
;GET NOTIFICATION FOR SENDING A CHAT OR GAME INVITATION BY CLICKING F1 OR F2
myloop:
xor ax, ax 
int 16h
cmp al,1bh ; =ESC
je exit2
mov bl,1
cmp chatinviteflag,bl
je SkipNewChatInvitation  ;dont make a new invitation unless the previous one recieves a response (make flag =0, when a response is recieved)
cmp ah,3bh ; =F1
je scroll
SkipNewChatInvitation:
mov bl,1
cmp gameinviteflag,bl
je SkipNewGameInvitation

cmp ah,3ch ; =F2
je scroll
SkipNewGameInvitation:
jmp myloop
;SCROLL WINDOW DOWN
scroll:
scrolldown 1500h,3250h
;DISPLAY THE NOTIFACTION STRING
cmp ah,3bh ; =F1
je printF1notif
cmp ah,3ch ; =F2
je printF2notif
printF1notif:
MOVECURSOR 1, 15h
DisplayString F1notif
mov bl,1
mov chatinviteflag,bl
jmp myloop
printF2notif:
MOVECURSOR 1, 15h
DisplayString F2notif
mov bl,1
mov gameinviteflag,bl
jmp myloop
exit2:
    
;SHOULD MAKE A PATH FROM MYLOOP TO THE GAME WHEN THE OTHER USER ACCEPTS THE INVITATION [SIMULATED IN PHASE 1]
popa
ret                     
menu ENDP
    




 