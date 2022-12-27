include macros.inc
.code

menu proc
    pusha
    initializeserial
    call initializeMenu
    myloop:
    call recievedata
    cmp recievechatresponse,1
    jne nochatresponse
    cmp chatinviteflag,1
    jne displayf1rec
    mov al,1
    mov frommenutochat,al
    call chat
    mov chatinviteflag,0
    mov invitationflag,0
    mov recievechatresponse,0
    mov frommenutochat,0
    call initializeMenu
    jmp myloop

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
    mov gameinviteflag,0
    mov invitationflag,0
    mov recievegameresponse,0
    mov frommenutogame,0
    call initializeMenu
    jmp myloop

    displayf2rec:
    cmp repetetionflag2,0
    jne nogameresponse
    scrolldown 1500h,3250h
    MOVECURSOR 1, 15h
    DisplayString F2rec                 ;i recieved a game invitation without sending one
    mov al,1
    add repetetionflag2,1
    nogameresponse:


    mov ah,1
    int 16h
    cmp al,1bh ; =ESC
    jne donotexitnow
    jmp exit2
    donotexitnow:
    mov bl,1
    cmp invitationflag,bl
    je SkipNewInvitation  ;dont make a new invitation unless the previous one recieves a response (make flag =0, when a response is recieved)

    cmp ah,3bh ; =F1
    jne skipnewchatinvitation
    mov bl,1
    mov chatinviteflag,bl
    mov invitationflag,bl
    call sendchatinvitation
    jmp printF1notif

    SkipNewChatInvitation:
    cmp ah,3ch ; =F2
    jne SkipNewInvitation
    mov bl,1
    mov gameinviteflag,bl
    mov invitationflag,bl
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

    ;TODO Terminate code
        
    ;SHOULD MAKE A PATH FROM MYLOOP TO THE GAME WHEN THE OTHER USER ACCEPTS THE INVITATION [SIMULATED IN PHASE 1]
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




 