;**************************************************************
section .data
	nummsg db "***Program to find Factorial of a number*** ",10
		db "Enter the number : ",
	nummsg_len equ $-nummsg

	resmsg db "Factorial is : "
	resmsg_len equ $-resmsg

	thankmsg db 10,"Thank you ",10
	thankmsg_len equ $-thankmsg

	zerofact db " 00000001 "
	zerofactlen equ $-zerofact

;************************************************************
section .bss

	dispbuff resb 16
	result resb 4
	num resb 1
	num1 resb 1
	numascii resb 3

	%macro display 2
		mov rax,01
		mov rdi,01
		mov rsi,%1
		mov rdx,%2
		syscall
	%endmacro

	%macro accept 2
		mov rax,0
		mov rdi,0
		mov rsi,%1
		mov rdx,%2
		syscall
	%endmacro

;************************************************************
section .text

global _start

_start:

	display nummsg,nummsg_len
	accept numascii,3		;accept number from user
	call packnum8_proc		;convert number from ascii to hex
	mov [num],bl



	display resmsg,resmsg_len

	mov al,[num]			;store number in accumulator
	cmp al,01h
	jbe endfact

	mov bl,[num]
	call proc_fact
	mov rbx,rax
	call disp64_proc
	jmp exit

endfact:
	display zerofact,zerofactlen

exit:
	display thankmsg,thankmsg_len

	mov rax,60
	mov rdi,0
	syscall
	ret

;************************************************************
disp64_proc:
	
	mov rdi,dispbuff	;point esi to buffer
	mov rcx,16		;load number of digits to display

dispup1:
	rol rbx,4		;rotate number left by four bits
	mov dl,bl		;move lower byte in dl
	and dl,0fh		;mask upper digit of byte in dl
	add dl,30h		;add 30h to calculate ASCII code
	cmp dl,39h		;compare with 39h
	jbe dispskip1		;if less than 39h akip adding 07 more
	add dl,07h		;else add 07

dispskip1:
	mov [rdi],dl		;store ASCII code in buffer
	inc rdi			;point to next byte
	loop dispup1		;decrement the count of digits to display
				;if not zero jump to repeat

	display dispbuff,16
	ret
;************************************************************
packnum8_proc:

	mov bx,0
	mov ecx,02
	mov esi,numascii
up1:
	rol bl,04
	mov al,[esi]
	cmp al,39h
	jbe skip1
	sub al,07h
skip1:
	sub al,30h
	add bl,al
	inc esi
	loop up1
	ret
;***********************Recursion*************************************
;There are two kinds of recursion: direct and indirect.
;In direct recursion, the procedure calls itself and
;in indirect recursion, the first procedure calls a second
;procedure,which in turn, calls the first procedure.

proc_fact:
	cmp bl, 1
	jne do_calculation
	mov ax, 1
	ret
do_calculation:
	push rbx
	dec bl
	call proc_fact
	pop rbx
	mul bl
	ret
;****************************************
