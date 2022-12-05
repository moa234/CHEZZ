.model small 
.data   

MSG1 db "To start chatting press F1 $"
MSG2 db "To start the game press F2 $" 
MSG3 db "To end the program press ESC $"     
NotifLine db   "________________________________________________________________________________$"
F1notif db "You sent a chat invitation to Ahmed $"
F2notif db "You sent a game invitation to Ahmed $"
chatinviteflag db 0
gameinviteflag db 0



.code

MAIN PROC FAR
 mov Ax, @Data
 mov DS, Ax    
 

MOVECURSOR MACRO   X,Y
    MOV AH,2
	MOV BH,0
	MOV DL,X
	MOV DH,Y
	INT 10H
ENDM MOVECURSOR 

     
     
DisplayString MACRO STR
    mov ah, 9H
    mov dx, offset STR
    int 21h
ENDM   

              
GETCURSOR MACRO 
    
    mov ah,3h 
    mov bh,0h 
    int 10h    
   
ENDM

clearscreen MACRO
    mov ax,0700h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h
ENDM

ReadString macro buffer
	mov ah, 0ah
	mov dx, offset buffer
	int 21h

    mov bl,buffer+1
    mov bh,0
    mov byte ptr bx[buffer+2],'$'
endm ReadString


;[ PRINT MAIN SCREEN

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

;]
  
;PRINT NOTIFICATION BAR LINE
MOVECURSOR 0, 14h 
DisplayString NotifLine



 ; GET NOTIFICATION FOR SENDING A CHAT OR GAME INVITATION BY CLICKING F1 OR F2
myloop:xor ax, ax

     
     int 16h

     cmp al,1bh ; =ESC
     je exit

     
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

 ; SCROLL WINDOW DOWN

 scroll:
     push Ax

     mov ah, 07h

     mov al, 1

     mov bh, 07 

     mov cl, 0 

     mov ch, 21    

     mov dl, 80 

     mov dh, 50   

     int 10h    

     pop AX


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

    exit:
    

   
;SHOULD MAKE A PATH FROM MYLOOP TO THE GAME WHEN THE OTHER USER ACCEPTS THE INVITATION [SIMULATED IN PHASE 1]
;SHOULD I PREVENT THE USER FROM SPAMMING INVITATIONS?

                     
MAIN ENDP
End MAIN     




 