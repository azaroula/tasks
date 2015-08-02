section .bss
	inbuf:  	resb 1
	inbuf2: 	resb 1
	umlaut_buf:	resw 1
	buf:		resb 5000	
	
	
section .data
	space		db " "
	eingabe:	db "Eingabe: "
	ausgabe:	db "Ausgabe: "
	char_count	dd 0
	

section .text
	global _start


_start:
	mov 	eax, 4
	mov 	ebx, 1
	mov 	ecx, eingabe
	mov 	edx, 9
	int 	80h

	mov 	eax, 3
	mov 	ebx, 1
	mov 	ecx, buf
	mov 	edx, 5000
	int 	80h
	
	cmp 	eax, 0x00
	je 	_close

	mov 	[char_count], eax
	mov	esi, 0
	
	mov 	eax, 4
	mov 	ebx, 1
	mov 	ecx, ausgabe
	mov 	edx, 9
	int 	80h

	jmp 	_read
	
_umlaut:
	cmp	[inbuf], byte 0x55  ;;U
	je	_second_char_e
	cmp	[inbuf], byte 0x4F  ;;O
	je	_second_char_e
	cmp	[inbuf], byte 0x41  ;;A
	je	_second_char_e
	cmp	[inbuf], byte 0x75  ;;u
	je	_second_char_e
	cmp	[inbuf], byte 0x6F  ;;o
	je	_second_char_e
	cmp	[inbuf], byte 0x61  ;;a
	je	_second_char_e
	cmp	[inbuf], byte 0x73  ;;s
	je	_second_char_z
	

	jmp	_print		

_second_char_e:
	mov	al, [inbuf]
	mov	[inbuf2], al	
	
	mov	eax, [buf+esi]
	mov	[inbuf], al
	inc	esi		
	dec	dword[char_count]	

	cmp	[inbuf], byte 0x65 ;;e		
	je	_cmp_umlaut

	mov 	eax, 4
	mov 	ebx, 1
	mov 	ecx, inbuf2
	mov 	edx, 1
	int 	80h

	jmp 	_umlaut
	
_second_char_z:
	mov	al, [inbuf]
	mov	[inbuf2], al	
	
	mov	eax, [buf+esi]
	mov	[inbuf], al
	inc	esi			
	dec	dword[char_count]	

	
	cmp	[inbuf], byte 0x7A ;;z
	je	_set_sz 

	mov 	eax, 4
	mov 	ebx, 1
	mov 	ecx, inbuf2
	mov 	edx, 1
	int 	80h

	jmp 	_umlaut

_cmp_umlaut:
	cmp	[inbuf2], byte 0x55
	je	_set_Ue
	cmp	[inbuf2], byte 0x4F
	je	_set_Oe
	cmp	[inbuf2], byte 0x41
	je	_set_Ae
	cmp	[inbuf2], byte 0x75
	je	_set_ue
	cmp	[inbuf2], byte 0x6F
	je	_set_oe
	cmp	[inbuf2], byte 0x61
	je	_set_ae
				
_set_Ue:
	mov 	[umlaut_buf], word "Ü"
	jmp 	_print_Umlaut
_set_Oe:
	mov 	[umlaut_buf], word "Ö"
	jmp 	_print_Umlaut
_set_Ae:
	mov 	[umlaut_buf], word "Ä"
	jmp 	_print_Umlaut
_set_ue:
	mov 	[umlaut_buf], word "ü"
	jmp 	_print_Umlaut
_set_oe:
	mov 	[umlaut_buf], word "ö"
	jmp 	_print_Umlaut
_set_ae:
	mov 	[umlaut_buf], word "ä"
	jmp 	_print_Umlaut
_set_sz:
	mov 	[umlaut_buf], word "ß"
	jmp 	_print_Umlaut


_print_Umlaut:
	mov eax, 4
	mov ebx, 1
	mov ecx, umlaut_buf
	mov edx, 2
	int 80h

	dec dword[char_count]
	cmp dword[char_count],0
	je	_done
	
	jmp	_read		

_print:
	mov eax, 4
	mov ebx, 1
	mov ecx, inbuf
	mov edx, 1
	int 80h

	dec dword[char_count]
	cmp dword[char_count],0
	je	_done
	
	jmp	_read


_done:
	jmp 	_start


_read:
	mov	eax, [buf+esi]
	mov	[inbuf], al
	inc	esi

	jmp	_umlaut


_close:
	mov 	[inbuf], dword 0x0000000A
	mov 	eax, 4
	mov 	ebx, 1
	mov 	ecx, inbuf
	mov 	edx, 1
	int 	80h	

	mov eax, 1
	mov ebx, 0
	int 80h	
