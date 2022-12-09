.model small
.286
.data
num dw 3456
mes db 'This is message','$'
InDATA db 6,?,6 dup('$')
Innum db 5,?,4 dup('$')
currpos dw 0
row dw 0
col dw 0
pixelrow dw 0
pixelcol dw 0
selectedpos dw 0
selectedcol dw 0
selectedrow dw 0
highlightpos dw 0
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
        getKeyPress
        jz whiletrue
        clearbuffer
        cmp al,'q'
        je selectcell
        call traversecell

        selectcell:
        cmp al,'q'
        jne whiletrue

        mov bx,row
        mov ax,8
        mul bx
        mov bx,ax
        mov si,col
        cmp board[bx][si],1
        je highpawn

        jmp whiletrue
        highpawn:
        call highlightpawn

    jmp whiletrue


    MOV AH, 4CH
    MOV AL, 01 ;your return code.
    INT 21H
main endp
end main