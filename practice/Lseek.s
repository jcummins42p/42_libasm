section .data
	pathname DD "seektest.txt"
section .bss
	buffer: resb 10
section .text
global main

main:
	MOV eax,5 ; preparing 'open' syscall
	MOV ebx,pathname
	MOV ecx,0
	INT 0x80

	MOV ebx,eax	; save file descriptor in ebx for lseek
	MOV eax,19	; preparing 'lseek' syscall
	MOV ecx,20	; off_t is the number of bytes to offset from current position
	MOV edx,0	; whence offsetting from:
				;	0 SEEK_SET from the front of the file plus offset bytes
				;	1 SEEK_CUR from the current location plus offset bytes
				;	2 SEEK_END from the end of the file plus offset bytes
				;	unistd.h for these definitions
	INT 0x80	; making lseek call

	MOV eax,3	; preparing 'read' syscall
	MOV ecx,buffer	; location to read into
	MOV edx,10	; amount of bytes to read
	INT 0x80

	MOV ebx,0
	MOV eax,1
	INT 0x80
