section .data
	pathname DD "/home/jcummins/asmtest.txt"

section .bss
	buffer: resb 1024	; reserve bytes to read file into

section .text
global main

main:
	MOV eax,5	; 5 is sys_open
	MOV ebx,pathname
	MOV ecx,0	; 0 is O_RDONLY
	INT 0x80	; execute open call, putting fd into eax

	MOV ebx,eax	; store fd in ebx
	MOV eax,3	; 3 is sys_read
	MOV ecx,buffer	; read requires buffer in ecx
	MOV edx,1024	; size to read
	INT	0x80	; returns number of bytes read from file
				; returns 0 if we reached EOF
	MOV eax,1
	MOV ebx,0
	INT 0x80
