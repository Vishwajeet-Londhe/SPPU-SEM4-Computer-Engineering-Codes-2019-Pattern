code segment
              
     assume cs:code,ds:code
start: mov ax,cs
     mov ds,ax
       mov cl,0
       mov ch,0

task1: inc cl
     cmp cl,09
       je exit
     mov ax,0b800h
       mov es,axz.asm
       mov si,1830

       mov al,'*'
     mov ah,93h
     mov es:[si],ax
     inc bl
     mov al,bl
     add al,30h
     mov ah,93h
     inc si
      inc si

       mov es:[si],ax
       call delay

     jmp task2



task2: inc ch
     cmp ch,09
     je exit
     mov ax,0b800h
     mov es,ax
     mov si,840
     mov al,'$'
      mov ah,0A1h
     mov es:[si],ax
     inc bh
     mov al,bh
     add al,30h
     mov ah,0A1h
     inc si
     inc si

     mov es:[si],ax
       call delay

    jmp task1


    delay proc near
    mov ax,0fffh
    d2:mov dx,0fffh
   d1:nop
     nop
     nop
     nop
     dec dx
    jnz d1
    dec ax
    jnz d2
    ret
    endp



exit:
    mov ah,4ch
    int 21h

code ends
end start
