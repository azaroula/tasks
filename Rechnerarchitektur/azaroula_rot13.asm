section .bss
	inbuf: resb 1

section .text
	global _start

_start:
	nop
	
	mov	eax, 3
	mov 	ebx, 0
	mov 	ecx, inbuf
	mov 	edx, 1
	int 	80h

	cmp 	eax, 0x00
	je 	_close

	call 	_rot13

	call 	_print

	jmp 	_start


_rot13:

	cmp 	[inbuf], byte 0x41
	jb 	_do_nothing

	cmp	[inbuf], byte 0x5b
	je	_do_nothing
	cmp	[inbuf], byte 0x5c
	je	_do_nothing
	cmp	[inbuf], byte 0x5d
	je	_do_nothing
	cmp	[inbuf], byte 0x5e
	je	_do_nothing
	cmp	[inbuf], byte 0x5f
	je	_do_nothing
	cmp	[inbuf], byte 0x60
	je	_do_nothing

	cmp	[inbuf], byte 0x7a
	jg	_do_nothing

	cmp	[inbuf], byte 0x6d ;;m
	jg	_sub

	cmp	[inbuf], byte 0x61 ;;a
	jge	_add	

	cmp	[inbuf], byte 0x4d ;;M
	jg	_sub

	jmp	_add		

_add:	

	add [inbuf],	byte 0x0d
	ret

_sub:	

	sub [inbuf],	byte 0x0d
	ret

_do_nothing:
	ret

_print:
	mov eax, 4
	mov ebx, 1
	mov ecx, inbuf
	mov edx, 1
	int 80h

	ret
_close:
	mov [inbuf], dword 0x0000000a
	mov eax, 4
	mov ebx, 1
	mov ecx, inbuf
	mov edx, 1
	int 80h	

	mov eax, 1
	mov ebx, 0
	int 80h	

