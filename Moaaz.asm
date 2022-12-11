.model small
.286
.data
num dw 3456
mes db 'This is message','$'
InDATA db 6,?,6 dup('$')
Innum db 5,?,4 dup('$')
;--------------------------------------------------
currpos dw 0
row dw 0
col dw 0
pixelrow dw 0
pixelcol dw 0
;--------------------------------------------------
selectedpos dw 0
selectedcol dw 0
selectedrow dw 0
selectedpixelcol dw 0
selectedpixelrow dw 0
selectedpiece db 0
;--------------------------------------------------
highlightpos dw 0
highlightflag db 0
;--------------------------------------------------
movingopflag dw 0
tempcurrpos dw 0
boxcolor db 0


board db 8,9,10,11,12,10,9,8
      db 7,7,7,7,7,7,7,7
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 1,1,1,1,1,1,1,1
      db 6,5,4,3,2,4,5,6
     


include macros.inc
include gameui.inc;comment from aley
include gamelog.inc
.code
main proc far
    ;set ds
    mov ax,@data
    mov ds,ax
    
    GraphicsMode
    
    call initializegame
    whiletrue:
        mov bl,0
        mov highlightflag,0
        getKeyPress
        jz whiletrue
        clearbuffer
        cmp al,'q'
        je selectcell
        call traversecell

        selectcell:
        cmp al,'q'
        jne whiletrue
        call selection
        
        cmp movingopflag,1
        jne pass
        call checkboxcolor
        cmp boxcolor,0ah
        jne selectcell
        pass:
        call movefromcelltocell
        
        cmp selectedpiece,1
        je highpawn
        cmp selectedpiece,6
        je highRook
        cmp selectedpiece,4
        je highbishop

        jmp whiletrue
        highpawn:
        call highlightpawn
        jmp checkhighlight
        highRook:
        call highlightrook
        jmp checkhighlight
        highbishop:
        call highlightbishop

        checkhighlight:
        cmp highlightflag,1
        je whiletrue
        mov bl,0
        mov movingopflag,0

    jmp whiletrue
    

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main