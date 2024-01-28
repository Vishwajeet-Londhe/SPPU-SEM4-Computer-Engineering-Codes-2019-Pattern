;Write 387 program to print mean, variance, standard deviation.

;--------------------------------------------------------------------------
%macro print 2
    mov rax,01
    mov rdi,01
    mov rsi,%1
    mov rdx,%2
    syscall
%endmacro

;--------------------------------------------------------------------------
section .data
    m0 db 10,"Program to calculate mean, variance, standard deviation:"
    l0:equ $-m0
    
    m1 db 10,"Mean is"
    l1:equ $-m1
    
    m2 db 10,"Variance is"
    l2:equ $-m2
     
    m3 db 10,"Standard Deviation is"
    l3:equ $-m3
    
    m4 db 10,"Values are: 102.59, 198.21, 100.67"
    l4:equ $-m4
    
    dpoint db "."
    
    hdec dq 100
    
    num1 dd 102.59
    num2 dd 198.21
    num3 dd 100.67
    num4 dd 3.00
    
    newline db 0xa

;--------------------------------------------------------------------------
section .bss

    dispbuff resb 1
    resbuff resb 10              ;or we can also write resbuff rest 1
    mean resd 1
    variance resd 1
    
;--------------------------------------------------------------------------
section .text

    global _start
    _start:
        print m0,l0
        print m4,l4
        
        finit                   ;initialize coprocessor
        fldz                    ;load stack top 0
        
    ;logic to calculate mean
    
    fld dword[num1]             ;first number on x387
    fld dword[num2]  
               
    fadd st0,st1
    
    fld dword[num3]
    fadd st0,st1
    
    fdiv dword[num4]            ;st0=add/3=mean
    fst dword[mean]
    
    print m1,l1
    
    call disp_result
    
    print newline,01                 ;newline
    
    
    
    ;logic to calculate variance
    
    mov rsi,num1
    call cal_diff_sqr
    
    mov rsi,num2
    call cal_diff_sqr
    
    fadd st0,st1
    
    mov rsi,num3
    call cal_diff_sqr
    
    fadd st0,st1 
     
    fdiv dword[num4]         ;divide by cardinality
    
    fst dword[variance]
    
    print m2,l2
    
    call disp_result
    
    print newline,01                 ;newline
    
    ;logic to calculate standard deviation
    
    fld dword[variance]
    fsqrt
    
    print m3,l3
    call disp_result
    
    print newline,01                 ;newline
    
    mov rax,60
    mov rdi,0
    syscall
   
;--------------------------------------------------------------------------  
 disp_result:
    fimul dword[hdec]
    fbstp [resbuff]                ;store bcd and pop from top of the stack
    
    xor rcx,rcx                    ;clear rcx register
    mov rcx,09h                    
    mov rsi,resbuff+9              ;rsi pointing to msb of resultant
    
    up1:
    push rcx
    push rsi
    
    mov bl,[rsi]
    call disp8_proc
    
    print dispbuff,02  
    pop rsi
    dec rsi
    pop rcx
    loop up1
    
    print dpoint,01
    
    mov bl,[resbuff]
    call disp8_proc
    
    print dispbuff,02
    
    ret
    
;--------------------------------------------------------------------------
disp8_proc:
   mov rdi,dispbuff
   mov rcx,02
   
 back:
   rol bl,04
   mov dl,bl
   and dl,0Fh
   cmp dl,09h
   jbe skip
   add dl,07h
   
skip:
   add dl,30h
   mov [rdi],dl
   inc rdi
   loop back
   ret
     
cal_diff_sqr:
   fld dword[rsi]
   fsub dword[mean]
   fmul st0,st0        
 ret  
;-------------------------------------------------------------------------- 
