.model small
.stack 64
.286
.data
msg    db  'Please enter your name: $ ' 
msg1    db  'Error, More than 15 characters are used$'   
msg2    db  'Error, Unauthorized characters are used$'
MyBuffer Label Byte
maxsize db 15
actsize db 0
inputdata db 15 dup('$')   
thiscurs dw 0
flag dw 0
include macros.inc
.code          


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




main proc far
    mov ax,@data
    mov ds,ax 
   

    mov ax,0700h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h
   
    movecursorinchat 0000
    mov bl,maxsize
    mov dx,offset msg
    mov ah,9
    int 21h;to print msg 
    
  
    mov ax,0202h
    mov thiscurs,ax
    movecursorinchat thiscurs
    
    
    mov si,offset inputdata
    L:
    getKeyPress
    jmp Check
    X:
    mov [si],al
    inc si
    inc actsize 
    cmp bl,actsize
    JNG ErrorMessage1 
    loop L 
    
    
    ;to validate the input character
    ;only small and cap letters are allowed 
    ;space is allowed also and if enter is pressed then the string has ended
    Check:
    cmp al,8 
    je backspace 
    cmp al,32;space
    je X 
    cmp al,13
    jne passend
    jmp End
    passend:
    cmp al,64
    jle ErrorMessage2 
    cmp al,123
    jge ErrorMessage2 
    cmp al,91
    je ErrorMessage2 
    cmp al,92
    je ErrorMessage2
    cmp al,93
    je ErrorMessage2
    cmp al,94
    je ErrorMessage2
    cmp al,95
    je ErrorMessage2
    cmp al,96
    je ErrorMessage2 
    jmp X
                        
                        
      
       backspace:  
        
    
        dec thiscurs
        MOVECURSORINCHAT thiscurs
        DisplayChar 0
    
     
        jmp x 
        
        
                        
                        
     
    ErrorMessage1: 
  
    mov ax,0402h
    mov thiscurs,ax
    movecursorinchat thiscurs
    mov dx,offset msg1
    mov ah,9
    int 21h 
    jmp End
    
    ErrorMessage2: 

    mov ax,0402h
     mov thiscurs,ax
    movecursorinchat thiscurs
    mov dx,offset msg2
    mov ah,9
    int 21h 
    jmp End
    
    End:                             
                                 
                                    
                                      
        
        
    main endp
end main