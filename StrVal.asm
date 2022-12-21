org 100h
.model small
.stack 64
.data
msg    db  'Please enter your name: $ ' 
msg1    db  'Error, More than 15 characters are used$'   
msg2    db  'Error, Unauthorized characters are used$'
MyBuffer Label Byte
maxsize db 15
actsize db 0
inputdata db 15 dup('$')
.code
main proc far
    mov ax,@data
    mov ds,ax 
    mov bl,maxsize
    mov dx,offset msg
    mov ah,9
    int 21h;to print msg 
    
    mov ah,2
    mov dx,0202h
    int 10h;to move cursor line below  
    
    mov si,offset inputdata
    L:
    mov ah,1
    int 21h  
    jmp Check
    X:
    mov [si],al
    inc si
    inc actsize 
    cmp bl,actsize
    JNG ErrorMessage1 
    loop L 
    
    Check: 
    cmp al,32;space
    je X
    cmp al,13
    je Endd
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
    
     
    ErrorMessage1: 
    mov ah,2
    mov dx,0402h
    int 10h;to move cursor line below
    mov dx,offset msg1
    mov ah,9
    int 21h 
    jmp Endd
    
    ErrorMessage2: 
    mov ah,2
    mov dx,0402h
    int 10h;to move cursor line below
    mov dx,offset msg2
    mov ah,9
    int 21h 
    jmp Endd
    
    Endd:                             
                                 
                                    
                                      
        
        
    main endp
end main