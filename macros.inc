;====================CLEARSCREEN=============================================================
clearscreen MACRO
    mov ax,0700h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h
ENDM
;============================================================================================

;=====================GetKeyPressed==========================================================
GetKeyPress MACRO
    MOV AH,01H                     ;DOESN'T WAIT FOR KEY PRESSED, JUST CHECKS THE KEYBOARD BUFFER FOR ONE
    INT 16H
ENDM GetKeyPress
;============================================================================================

;===============================ENTERTEXTMODE===============================================
TEXTMODE MACRO 
    MOV AH,0
    MOV AL,3
	INT 10H
ENDM TEXTMODE
;===========================================================================================

;===============================GRAPHICSMODE================================================
GraphicsMode MACRO 
    MOV AH,0
    MOV AL,13h
	INT 10H
ENDM GraphicsMode
;===========================================================================================

;================================MOVECURSORPOSITION=========================================
MOVECURSOR MACRO   X,Y
    MOV AH,2
	MOV BH,0
	MOV DL,X
	MOV DH,Y
	INT 10H
ENDM MOVECURSOR
;============================================================================================

;=======================================DisplayString========================================

DisplayString macro str    ;this macro displays a string when given its memory variable name
	mov dx, offset str
	mov ah, 9h
	int 21h
endm DisplayString
;============================================================================================

;=======================================ReadString===========================================
ReadString macro buffer
    ;this macro reads a string from the keyboard and stores it in the buffer
	mov ah, 0ah
	mov dx, offset buffer
	int 21h

    ;set last charachter in input buffer to null
    mov bl,buffer+1
    mov bh,0
    mov byte ptr bx[buffer+2],'$'
endm ReadString
;============================================================================================

;=====================DisplayASingleCharacter================================================
DisplayChar MACRO MyChar
    MOV AH, 2
    MOV DL, MyChar
    INT 21H
ENDM PrintChar
;============================================================================================

;=====================DisplayASingleCharacter================================================
DisplayCharDX MACRO MyChar
    PUSH AX
    MOV AH, 2
    INT 21H
    POP AX
ENDM PrintChar
;============================================================================================

;=====================================DisplayNumber==========================================
DisplayNumber macro number    
;displays the number saved in memory variable x max size : 65535
    mov ax,number
	mov cx,0
    mov dx,0
    label1:
        ;exit when number reaches 0
        cmp ax,0
        je print1     
        
        ;get unit digit
        mov bx,10       
        div bx     

        push dx
        inc cx

        ;set dx to 0
        mov dx,0
        jmp label1
    print1:
        ;check if count
        ;is greater than zero
        cmp cx,0
        je exit
         
        pop dx 
        add dx,'0'
        DisplayCharDX
         
        dec cx
        jmp print1
    exit:
endm DisplayNumber
;============================================================================================