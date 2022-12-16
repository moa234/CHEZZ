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
selectflag db 1
tempcurrpos dw 0
boxcolor db 0
bordercolor db 01h


board db 8,9,10,11,12,10,9,8
      db 7,7,7,7,7,7,7,7
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 0,0,0,0,0,0,0,0
      db 1,1,1,1,1,1,1,1
      db 6,5,4,2,3,4,5,6
     
timerboard dw 8*8 dup(-3)

startsec db 0
startmin db 0
currsec db 0
currmin db 0

include macros.inc
include gameui.inc
include gamelog.inc
.code
main proc far
    ;set ds
    mov ax,@data
    mov ds,ax
    
    GraphicsMode
    
    call initializegame
    whiletrue:
        call updatetime
        MOVECURSOR 25,1
        call Displaytime
        
        mov selectflag,1
        cmp highlightflag,1
        jne donotchange
        
        cmp movingopflag,0
        jne donotchange 
        call deletehighlight
        donotchange:

        getKeyPress
        jz whiletrue
        clearbuffer
        cmp al,'q'
        je selectcell
        call traversecell
        jmp selectcell

        getout:
        mov movingopflag,0
        call deletehighlight
        mov dl,01h
        mov bordercolor,dl
        call drawborder
        selectcell:
        cmp al,'q'
        jne whiletrue 

        call selection
        
        cmp movingopflag,1
        jne pass
        call checkboxcolor
        cmp boxcolor,0ah
        jne getout
        pass:
        
        call movefromcelltocell
        call highlightforselectedpiece


    jmp whiletrue
    

    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main