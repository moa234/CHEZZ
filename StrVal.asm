.model small
.stack 64
.286
.data
msg    db  'Please enter your name: $ ' 
msg1   db  'Error, More than 15 characters are used$'   
msg2   db  'Error, unauthorized characters are used, please enter a valid username:$'
buffer db 15,?,15 dup('$') ;First byte is the size, second byte is the number of characters from the keyboard

.code          

DisplayString macro str    ;this macro displays a string when given its memory variable name
    pusha
	mov dx, offset str
	mov ah, 9h
	int 21h
    popa
endm DisplayString


MOVECURSORINCHAT MACRO pos
    pusha
    MOV AH,2
	MOV BH,0
	MOV DX,pos
	INT 10H
    popa
ENDM MOVECURSORINCHAT

DisplayChar MACRO MyChar
    pusha
    MOV AH, 2
    MOV DL, MyChar
    INT 21H
    popa
ENDM DisplayChar                   
                    
GETCURSOR MACRO 
    mov ah,3h 
    mov bh,0h 
    int 10h    
ENDM  GETCURSOR  

ReadString macro buffer
    ;this macro reads a string from the keyboard and stores it in the buffer
    pusha
	mov ah, 0ah
	mov dx, offset buffer
	int 21h

    ;set last charachter in input buffer to null
   mov bl,buffer+1
   mov bh,0
   mov byte ptr bx[buffer+2],'$'
    popa
endm ReadString
clearscreen MACRO
    pusha
    mov ax,0700h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h
    popa
ENDM clearscreen









main proc far
    mov ax,@data
    mov ds,ax    
    
    clearscreen
    movecursorinchat 0000

    
    mov dx,offset msg
    mov ah,9
    int 21h;to print msg 

    returnfromerror:
    mov ah,2
    mov dx,0202h
    int 10h;to move cursor line below  
   
    readstring buffer

    mov dl,1 ;aw1                 
    mov si,2 ;aw3
                  
 Check:
    cmp buffer[si],32
    je spaceescape
    cmp buffer[si],13
    je Endd
    cmp buffer[Si],64
    jle ErrorMessage2 
    spaceescape:
    cmp buffer[Si],123
    jge ErrorMessage2 
    cmp buffer[Si],91
    je ErrorMessage2 
    cmp buffer[Si],92
    je ErrorMessage2
    cmp buffer[Si],93
    je ErrorMessage2
    cmp buffer[Si],94
    je ErrorMessage2
    cmp buffer[Si],95
    je ErrorMessage2
    cmp buffer[Si],96
    je ErrorMessage2 
    jmp endd                  
                        
    ErrorMessage2: 
    clearscreen
    movecursorinchat 0000
    mov dx,offset msg2
    mov ah,9
    int 21h 
    jmp returnfromerror

    Endd:          
    
    inc si       
    inc dl                

cmp dl,buffer[1] 
je exit222                 
jmp check               
exit222:
   
        
    main endp
end main






