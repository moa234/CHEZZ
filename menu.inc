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
initializeserial
myloop:
call recievedata
cmp recievechatresponse,1
jne nochatresponse
cmp chatinviteflag,1
jne displayf1rec
mov al,1
mov frommenutochat,al
ret
displayf1rec:
cmp repetetionflag1,0
jne nochatresponse
scrolldown 1500h,3250h
MOVECURSOR 1, 15h
DisplayString F1rec                 ;i recieved a chat invitation without sending one
mov al,1
add repetetionflag1,1

nochatresponse:
cmp recievegameresponse,1
jne nogameresponse
cmp gameinviteflag,1
jne displayf2rec
mov al,1
mov frommenutogame,al
call game
displayf2rec:
cmp repetetionflag2,0
jne nogameresponse
scrolldown 1500h,3250h
MOVECURSOR 1, 15h
DisplayString F2rec                 ;i recieved a game invitation without sending one
mov al,1
add repetetionflag2,1
nogameresponse:

getKeyPress
clearbuffer
cmp al,1bh ; =ESC
jne donotexitnow
jmp exit2
donotexitnow:
mov bl,1
cmp chatinviteflag,bl
je skipnewchatinvitation  ;dont make a new invitation unless the previous one recieves a response (make flag =0, when a response is recieved)

cmp ah,3bh ; =F1
jne skipnewchatinvitation
mov bl,1
mov chatinviteflag,bl
call sendchatinvitation
jmp printF1notif

SkipNewChatInvitation:
mov bl,1
cmp gameinviteflag,bl
je skipnewinvitation  
cmp ah,3ch ; =F2
jne SkipNewInvitation
mov bl,1
mov gameinviteflag,bl

call sendgameinvitation
jmp printF2notif

SkipNewInvitation:
jmp myloop

;DISPLAY THE NOTIFACTION STRING
printF1notif:
scrolldown 1500h,3250h
MOVECURSOR 1, 15h
DisplayString F1notif
jmp myloop

printF2notif:
scrolldown 1500h,3250h
MOVECURSOR 1, 15h
DisplayString F2notif
jmp myloop
exit2:

clearscreen
MOVECURSOR 0,0
MOV AH, 4CH
MOV AL, 00    ;your return code.
INT 21H

popa
ret                     
menu ENDP
    
initializeMenu proc

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
    
    ret
initializeMenu ENDP




 