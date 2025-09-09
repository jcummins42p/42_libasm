section .data
	pathname DB "newfile.txt",0x0
	toWrite DB "Hello World!",0x0A,"Writing from assembly",0x0A
	len equ $ - toWrite	; calculate assemble-time string length

section .text
global main

main:
	MOV eax,5
	MOV ebx,pathname
	MOV ecx,101o	; 0 after number denotes OCTAL value: CREATE and WRITE
	MOV edx,700o	; UNIX file permissions for rwx
	INT 0x80

	MOV ebx,eax	; save the file descriptor in eax
	MOV eax,4	; 'write' syscall
	MOV ecx,toWrite ; buffer to write
	MOV edx,len
	INT 0x80

	MOV eax,1
	MOV ebx,0
	INT 0x80
