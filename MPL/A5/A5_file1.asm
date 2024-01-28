;Assignment Name :X86/64 Assembly language program (ALP) to find
;	a) Number of Blank spaces
;	b) Number of lines
;	c) Occurrence of a particular character. 
;Accept the data from the text file. The text file has to be accessed during Program_1 execution.
;Write FAR PROCEDURES in Program_2 for the rest of the processing.
;Use of PUBLIC/GLOBAL and EXTERN directives is mandatory.
;------------------------------------------------------------------------

extern	far_proc		; [ FAR PROCRDURE 
					;   USING EXTERN DIRECTIVE ]

global	filehandle, char, buf, abuf_len

%include	"macro.asm"

;------------------------------------------------------------------------
section .data
	nline		db	10
	nline_len	equ	$-nline

	ano		db 	10,10,10,10,"----String Operation using Far Procedure----"
			db		   10,"---------------------------------------------------",10
	ano_len	equ	$-ano

	filemsg	db	10,"Enter filename for string operation	: "
	filemsg_len	equ	$-filemsg	
  
	charmsg	db	10,"Enter character to search	: "
	charmsg_len	equ	$-charmsg

	errmsg	db	10,"ERROR in opening File...",10
	errmsg_len	equ	$-errmsg

	exitmsg	db	10,10,"Exit from program...",10,10
	exitmsg_len	equ	$-exitmsg

;---------------------------------------------------------------------------
section .bss
	buf			resb	4096
	buf_len		equ	$-buf		; buffer initial length

	filename		resb	50	
	char			resb	2	
 
	filehandle		resq	1
	abuf_len		resq	1		; actual buffer length

;--------------------------------------------------------------------------
section .text
	global _start
		
_start:
		print	ano,ano_len		;assignment no. 

		print	filemsg,filemsg_len		
		read 	filename,50
		dec	rax
		mov	byte[filename + rax],0		; blank char/null char

		print	charmsg,charmsg_len		
		read 	char,2
		
		fopen	filename			; on succes returns handle
		cmp	rax,-1H			; on failure returns -1
		jle	Error
		mov	[filehandle],rax	

		fread	[filehandle],buf, buf_len
		mov	[abuf_len],rax

		call	far_proc
		jmp	Exit

Error:	print	errmsg, errmsg_len

Exit:		print	exitmsg,exitmsg_len
		exit
;-------------------------------------------------------------------------------- 

