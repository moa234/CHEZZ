;====================CLEARSCREEN=============================================================
clearscreen MACRO
    pusha
    mov ax,0700h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h
    popa
ENDM clearscreen
;============================================================================================

;====================CLEARSCREENat=============================================================
clearscreentimer MACRO
    pusha
    mov ax,0700h
    mov bh,00
    mov cx,0126h
    mov dx,0128H
    int 10h
    popa
ENDM clearscreen
;============================================================================================

;====================scrollup=============================================================
scrollup MACRO from,to
    pusha
    mov ax,0601h
    mov bh,07
    mov cx,from
    mov dx,to
    int 10h
    popa
ENDM scrollup
;============================================================================================
;====================scrolldown=============================================================
scrolldown MACRO from,to
    pusha
    mov ax,0701h
    mov bh,07
    mov cx,from
    mov dx,to
    int 10h
    popa
ENDM scrolldown
;============================================================================================

;====================select video page=============================================================
SelectVideoPage MACRO page
    pusha
    mov al,page
    mov ah,05h
    int 10h
    popa
ENDM SelectVideoPage
;============================================================================================

;=====================GetKeyPressed==========================================================
GetKeyPress MACRO
    MOV AH,01H                     ;DOESN'T WAIT FOR KEY PRESSED, JUST CHECKS THE KEYBOARD BUFFER FOR ONE
    INT 16H
ENDM GetKeyPress
;============================================================================================

GetPixelColour MACRO pcol,prow
    mov cx,pcol
    add cx,2
    mov dx,prow
    add dx,2
    mov ah,0dh
    int 10h
ENDM GetPixelColour
;=====================clearbuffer==========================================================
clearbuffer MACRO
    pusha
    mov al,00h
	mov ah,0CH
	int 21h
    POPa
endm clearbuffer
;============================================================================================

;==============================Getsystemtime================================================
getsystemtime macro
    mov ah,2ch
    int 21h
endm getsystemtime

;===============================ENTERTEXTMODE===============================================
TEXTMODE MACRO 
    pusha
    MOV AH,0
    MOV AL,3
	INT 10H
    popa
ENDM TEXTMODE
;===========================================================================================

;===============================GRAPHICSMODE================================================
GraphicsMode MACRO 
    pusha
    MOV AH,0
    MOV AL,13h
	INT 10H
    popa
ENDM GraphicsMode
;===========================================================================================

;================================MOVECURSORPOSITION=========================================
MOVECURSOR MACRO   X,Y
    pusha
    MOV AH,2
	MOV BH,0
	MOV DL,X
	MOV DH,Y
	INT 10H
    popa
ENDM MOVECURSOR
;============================================================================================

;================================getCURSORPOSITION=========================================
GETCURSORPOSINCHAT MACRO
    MOV AH,3
	MOV BH,2
	INT 10H
ENDM GETCURSORPOSINCHAT

GETCURSOR MACRO 
    mov ah,3h 
    mov bh,0h 
    int 10h    
ENDM
;============================================================================================

;================================MOVECURSORPOSITION=========================================
MOVECURSORINCHAT MACRO   pos
    pusha
    MOV AH,2
	MOV BH,2
	MOV DX,pos
	INT 10H
    popa
ENDM MOVECURSORINCHAT
;============================================================================================

;=======================================DisplayString========================================

DisplayString macro str    ;this macro displays a string when given its memory variable name
    pusha
	mov dx, offset str
	mov ah, 9h
	int 21h
    popa
endm DisplayString
;============================================================================================

;=======================================ReadString===========================================
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
;============================================================================================

;=====================DisplayASingleCharacter================================================
DisplayChar MACRO MyChar
    pusha
    MOV AH, 2
    MOV DL, MyChar
    INT 21H
    popa
ENDM PrintChar
;============================================================================================

;=====================DisplayASingleCharacter================================================
DisplayCharDX MACRO
    MOV AH, 2
    INT 21H
ENDM PrintChar
;============================================================================================

;=====================================DisplayNumber==========================================
DisplayNumber macro number    
local label1
local print1
local exit
local donotzero
;displays the number saved in memory variable x max size : 65535
    pusha
    mov al,number
    mov ah,0

    cmp ax,9
    ja donotzero
    mov dx,'0'
    DisplayCharDX
    mov al,number
    mov ah,0

    cmp ax,0
    jne donotzero
    mov dx,'0'
    DisplayCharDX
    mov al,number
    mov ah,0

    donotzero:
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
    popa
endm DisplayNumber
;============================================================================================