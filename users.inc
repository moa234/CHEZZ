;include macros.inc

.code          


username proc 
    pusha
    clearscreen
    movecursor 0,0
    mov dx,offset msg
    mov ah,9
    int 21h;to print msg 

    returnfromerror:
    mov ah,2
    mov dx,0202h
    int 10h;to move cursor line below  
   
    readstring myplayer

    mov dl,0 ;aw1                 
    mov si,2 ;aw3
                  
 Check:
    cmp myplayer[si],32
    je spaceescape
    cmp myplayer[si],13
    je Endd
    cmp myplayer[Si],64
    jle ErrorMessage2 
    spaceescape:
    cmp myplayer[Si],123
    jge ErrorMessage2 
    cmp myplayer[Si],91
    je ErrorMessage2 
    cmp myplayer[Si],92
    je ErrorMessage2
    cmp myplayer[Si],93
    je ErrorMessage2
    cmp myplayer[Si],94
    je ErrorMessage2
    cmp myplayer[Si],95
    je ErrorMessage2
    cmp myplayer[Si],96
    je ErrorMessage2 
    jmp endd                  
                        
    ErrorMessage2: 
    clearscreen
    movecursor 0,0
    mov dx,offset msg22
    mov ah,9
    int 21h 
    jmp returnfromerror

    Endd:          
    
    inc si       
    inc dl                

cmp dl,myplayer[1] 
je exit222                 
jmp check               
exit222:

call send&recusernames

popa
ret
username endp

send&recusernames proc
pusha

mov cx,15
mov si,0
userloop:
mov bh,0
mov bl,myplayer[Si]
sendserial bx
recieveserialwait bx
mov opponentplayer[si],bl
inc si
loop userloop

popa
ret
send&recusernames endp









