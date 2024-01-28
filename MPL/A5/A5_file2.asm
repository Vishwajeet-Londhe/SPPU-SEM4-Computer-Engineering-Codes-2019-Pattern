;---------------------------------------------------------------------
section .data
	nline		db	10,10
	nline_len:	equ	$-nline

	smsg		db	10,"No. of spaces are	: "
	smsg_len:	equ	$-smsg
	
	nmsg		db	10,"No. of lines are	: "
	nmsg_len:	equ	$-nmsg

	cmsg		db	10,"No. of character occurances are	: "
	cmsg_len:	equ	$-cmsg

;---------------------------------------------------------------------
section .bss

	scount	resq	1
	ncount	resq	1
	ccount	resq	1

	char_ans	resb	16

;---------------------------------------------------------------------
global	far_proc		

extern	filehandle, char, buf, abuf_len

%include	"macro.asm"
;---------------------------------------------------------------------
section .text
	global	_main
_main:

far_proc:          		;FAR Procedure
	
		xor	rax,rax
		xor	rbx,rbx
		xor	rcx,rcx
		xor	rsi,rsi	

		mov	bl,[char]
		mov	rsi,buf
		mov	rcx,[abuf_len]

again:	mov	al,[rsi]

case_s:	cmp	al,20h		;space : 32 (20H)
		jne	case_n
		inc	qword[scount]
		jmp	next

case_n:	cmp	al,0Ah		;newline : 10(0AH)
		jne	case_c
		inc	qword[ncount]
		jmp	next

case_c:	cmp	al,bl			;character
		jne	next
		inc	qword[ccount]

next:		inc	rsi
		dec	rcx			;
		jnz	again			;loop again

		print smsg,smsg_len
		mov	rax,[scount]
		call	display
	
		print nmsg,nmsg_len
		mov	rax,[ncount]
		call	display

		print cmsg,cmsg_len
		mov	rax,[ccount]
		call	display

	fclose	[filehandle]
	ret

;------------------------------------------------------------------
display:
	mov 	rsi,char_ans+3	; load last byte address of char_ans in rsi
	mov 	rcx,4			; number of digits 

cnt:	mov 	rdx,0			; make rdx=0 (as in div instruction rdx:rax/rbx)
	mov 	rbx,10		; divisor=10 for decimal and 16 for hex
	div 	rbx
;	cmp 	dl, 09h		; check for remainder in RDX
;	jbe  	add30
;	add  	dl, 07h 
;add30:
	add 	dl,30h		; calculate ASCII code
	mov 	[rsi],dl		; store it in buffer
	dec 	rsi			; point to one byte back

	dec 	rcx			; decrement count
	jnz 	cnt			; if not zero repeat
	
	print char_ans,4		; display result on screen
ret
;----------------------------------------------------------------

