section .bss
	inbuff:		resw 2
	inbuf2:		resw 2
	tmp_buff:	resw 2
	albuff: 	resb 1
	
section .data
	counter: 	dd 1
	counter2:	dd 0
	space:	 	db 0x20
	newline: 	db 0x0a
	o: db "o"
	O: db "O"
	s: db "s"
	S: db "S"
	z: db "z"
	Z: db "Z"
	p: db "p"
	P: db "P" 
	c: db "c"
	C: db "C"
	a: db "a"
	A: db "A"			

section .text
	
	global _start 

print_newline:
	push eax 
	push ebx
	push ecx
	push edx

	mov eax, 4 
	mov ebx, 1 
	mov ecx, newline
	mov edx, 1
	int 80h

	pop edx
	pop ecx 
	pop ebx
	pop eax
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;FLAGS;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

print_flags:

	pushf
	push eax
	push ebx 
	push ecx 
	push edx

overflow:
	mov eax, 4 
	mov ebx, 1
	mov edx, 1
	jo overflowset
	mov ecx, o
	int 80h
	jmp sign

overflowset:
	mov ecx, O
	int 80h
	
sign:
	mov eax, 4 
	mov ebx, 1
	mov edx, 1
	js signset
	mov ecx, s
	int 80h
	jmp zero
signset:
	mov ecx, S
	int 80h
	

zero:
	mov eax, 4 
	mov ebx, 1
	mov edx, 1
	jz zeroset
	mov ecx, z
	int 80h
	jmp auxiliary

zeroset:
	mov ecx, Z
	int 80h

	

auxiliary:
	lahf			
	bt ax, 12
	push eax			
	mov eax, 4
	mov ebx, 1
	mov edx, 1
	jc  auxiliaryset
	mov ecx, a
	int 80h
	pop eax
	sahf
	jmp parity

auxiliaryset:	
	mov ecx, A
	int 80h
	pop eax 
	sahf

parity:
	mov eax, 4 
	mov ebx, 1
	mov edx, 1
	jpe parityset
	mov ecx, p
	int 80h
	jmp carry
	
parityset:
	mov ecx, P
	int 80h



carry:
	mov eax, 4 
	mov ebx, 1
	mov edx, 1
	jc carryset
	mov ecx, c
	int 80h
	jmp ende 
	
carryset:
	mov ecx, C
	int 80h
	
ende: 
	pop edx 
	pop ecx
	pop ebx
	pop eax
	popf
	call print_newline
	ret	



	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;REGISTER;;;;;;;;;;;;;;;;;;;;;;;;;;

	
print_register:
	pushf
	
register_auswahl:
	push eax
	push ebx
	push ecx
	push edx
	mov [inbuff], eax    	
	cmp [counter], dword 1
	je vorbereitung
	mov [inbuff], ebx
	cmp dword[counter], 2
	je vorbereitung
	mov [inbuff], ecx	
	cmp dword[counter], 3
	je vorbereitung
	mov [inbuff], edx
	cmp dword[counter], 4
	je vorbereitung
	pop edx 
	pop ecx
	pop ebx
	pop eax
	popf
	mov dword[counter],1
	call print_newline
	ret				
	
vorbereitung: 
	mov dword[counter2],8
	mov eax, [inbuff]
	rol eax, 8

register_stelle:
	mov [tmp_buff], eax
	shr al, 4

	cmp al, byte 0x0A
	je hex_a	  

	cmp al, byte 0x0B
	je hex_b	  

	cmp al, byte 0x0C
	je hex_c	  

	cmp al, byte 0x0D
	je hex_d	  

	cmp al, byte 0x0E
	je hex_e	  

	cmp al, byte 0x0F
	je hex_f	  

	add al, byte 0x30

print_ziffer:
	mov [albuff],al
	mov eax, 4
	mov ebx, 1
	mov ecx, albuff
	mov edx, 1
	int 80h
	dec dword[counter2]
	cmp dword[counter2], 0 
	je next_register
	mov eax, [tmp_buff]
	rol eax, 4
	jmp register_stelle

hex_a:
	mov al, 0x41	
	jmp print_ziffer
	
hex_b:
	mov al, 0x42	
	jmp print_ziffer
	
hex_c:
	mov al, 0x43	
	jmp print_ziffer
	
hex_d:
	mov al, 0x44	
	jmp print_ziffer

hex_e:
	mov al, 0x45	
	jmp print_ziffer

hex_f:
	mov al, 0x46	
	jmp print_ziffer
 
		
next_register:
	mov eax, 4
	mov ebx, 1
	mov ecx, space
	mov edx, 1
	int 80h
	inc dword[counter]
	pop edx 
	pop ecx
	pop ebx
	pop eax
	jmp register_auswahl
	
	
_start:
	
	mov eax, 0x11111111
	mov ebx, 0x22222222
	mov ecx, 0x33333333 
	mov edx, 0xffffffff
	call print_register
	call print_flags
	add ebx, edx
	call print_register
	call print_flags
	adc eax, ecx
	call print_register
	call print_flags   
	mov eax, 1
	mov ebx, 0
	int 80h

;-----------------------------------------------------
;------------resultate von add64.asm------------------
;
;11111111 22222222 EEEEEEEE EEEEEEEE 
;oszpac
;11111111 11111110 EEEEEEEE EEEEEEEE 
;oszpAC
;00000000 11111110 EEEEEEEE EEEEEEEE 
;osZPAC
;
;11111111 22222222 33333333 EEEEEEEE 
;oszpac
;11111111 11111110 33333333 EEEEEEEE 
;oszpAC
;44444445 11111110 33333333 EEEEEEEE 
;oszpac
;
;11111111 22222222 33333333 DDDDDDDE 
;oszpac
;11111111 00000000 33333333 DDDDDDDE 
;osZPAC
;44444445 00000000 33333333 DDDDDDDE 
;oszpac
;
;11111111 22222222 33333333 DDDDDDDD 
;oszpac
;11111111 FFFFFFFF 33333333 DDDDDDDD 
;oSzPac
;44444444 FFFFFFFF 33333333 DDDDDDDD 
;oszPac
;
;11111111 22222222 33333333 44444444 
;oszpac
;11111111 66666666 33333333 44444444 
;oszPac
;44444444 66666666 33333333 44444444 
;oszPac
