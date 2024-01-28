;macro.asm
;macros as per 64 bit conventions

%macro read 2
	mov	rax,0		;read
	mov	rdi,0		;stdin/keyboard
	mov	rsi,%1	;buf
	mov	rdx,%2	;buf_len
	syscall
%endmacro

%macro print 2
	mov	rax,1		;print
	mov	rdi,1		;stdout/screen
	mov	rsi,%1	;msg
	mov	rdx,%2	;msg_len
	syscall
%endmacro

%macro fopen 1
	mov	rax,2		;open
	mov	rdi,%1	;filename
	mov	rsi,2		;mode RW
	mov	rdx,0777o	;File permissions
	syscall
%endmacro

%macro fread 3
	mov	rax,0		;read
	mov	rdi,%1	;filehandle
	mov	rsi,%2	;buf
	mov	rdx,%3	;buf_len
	syscall
%endmacro

%macro fwrite 3
	mov	rax,1		;write/print
	mov	rdi,%1	;filehandle
	mov	rsi,%2	;buf
	mov	rdx,%3	;buf_len
	syscall
%endmacro

%macro fclose 1
	mov	rax,3		;close
	mov	rdi,%1	;file handle
	syscall
%endmacro

%macro exit 0
	print	nline,nline_len
	mov	rax,60	;exit
	mov	rdi,0
	syscall
%endmacro
