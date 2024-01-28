;Like printf function in c's asm code

%macro myprintf 1 
mov rdi,formatpf
sub rsp,8
movsd xmm0,[%1]
mov rax,1 
call printf
add rsp,8
;syscall
%endmacro

;--- scanff function 

%macro myscanf 1
mov rdi,formatsf
mov rax,0
mov rsi,%1
call scanf
;syscall
%endmacro

;----- Normal System call macro ----

%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4 
syscall
%endmacro

;------ Data Section ------

Section .data

	ff1: db "%lf +i %lf",10,0 	;format for printf/scanf argument printing
	ff2: db "%lf -i %lf",10,0	;formatpi: db "%d",10,0
	formatpf: db "%lf",10,0
	formatsf: db "%lf",0
	four: dq 4 			; 4 for using in formula
	two: dq 2
	;ipart1: db " +i ", 10
	;ipart2: db " -i " , 10
	rmsg: db 0x0A,"Roots are  real. Roots: ",0x0A
	rmsg_len: equ $-rmsg
	imsg: db "Roots are complex. Roots ",0x0A
	imsg_len: equ $-imsg
	title: db "====== QUadratic Equations ========",0x0A
	db "Enter a ,b,c : ",0x0A
	title_len: equ $-title

;------ BSS Section -----

section .bss

	a: resq 1
	b: resq 1
	c: resq 1
	b2: resq 1 	; b square
fac: 	resq 1 		; 4ac 
delta: 	resq 1 		; delta value
rdelta: resq 1 		; root of delta
r1: 	resq 1 		;root 1
r2: 	resq 1		;root 2
ta: 	resq 1 		; 2a
realn: 	resq 1 
img1: 	resq 1
;img2 : resq 1

;----------------------

Section .text

	extern printf
	extern scanf

global main:
main:

	scall 1,1, title,title_len
;;-------- Scanning numbers

myscanf a
myscanf b
myscanf c

;;======== Printing values for checking

;myprintf a
;myprintf b
;myprintf c

;==== Calculating b square

fld qword[b]
fmul qword[b]
fstp qword[b2]

;------- Calculating 4ac

fild qword[four]
fmul qword[a]
fmul qword[c]
fstp qword[fac]

; calculating delta

fld qword[b2]
fsub qword[fac]
fstp qword[delta]

;calcualating 2a

fild qword[two]
fmul qword[a]
fstp qword[ta]

btr qword[delta],63
;bit test set carry if flag is set else reset it
jc IMAGINARY

scall 1,1,rmsg, rmsg_len
;;--------------- REAL ROOTS --------
fld qword[delta]
fsqrt
fstp qword[rdelta]

;----- (-b+squareroot(delta))/2a

fldz
fsub qword[b]
fadd qword[rdelta]
fdiv qword[ta]
fstp qword[r1]
myprintf r1

;----- (-b-squareroot(delta))/2a

fldz
fsub qword[b]
fsub qword[rdelta]
fdiv qword[ta]
fstp qword[r2]
myprintf r2

jmp EXIT

IMAGINARY:
scall 1,1, imsg,imsg_len

fld qword[delta]
fsqrt
fstp qword[rdelta]

;real part of root
fldz
fsub qword[b]
fdiv qword[ta]
fstp qword[realn]

fld qword[rdelta]
fdiv qword[ta]
fstp qword[img1]

;---- printing imag roots
mov rdi,ff1
sub rsp,8
movsd xmm0,[realn]
movsd xmm1,[img1]
mov rax,2
call printf
add rsp,8

mov rdi,ff2
sub rsp,8
movsd  xmm0, [realn]
movsd xmm1, [img1]
mov rax,2
call printf
add rsp,8

jmp EXIT

EXIT:
mov rax,60
mov rdi,0
syscall


;vivek@vivek-gouda-pc:~/Desktop/Microprocessor Lab/Assignment 10$ nasm -f elf64 quadratic.asm 
;vivek@vivek-gouda-pc:~/Desktop/Microprocessor Lab/Assignment 10$ gcc -o quadratic quadratic.o
;vivek@vivek-gouda-pc:~/Desktop/Microprocessor Lab/Assignment 10$ ./quadratic 
;====== QUadratic Equations ========
;Enter a ,b,c : 
;1
;0
;-16

;Roots are  real. Roots: 
;4.000000
;-4.000000
;vivek@vivek-gouda-pc:~/Desktop/Microprocessor Lab/Assignment 10$ 

