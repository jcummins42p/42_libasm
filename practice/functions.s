section .data

section .text
global main

addTwo:
	ADD eax,ebx
	RET	; returns eax to the calling location

main:
	MOV eax,4
	MOV ebx,1
	CALL addTwo
	MOV ebx,eax	; preserving that returned value
	MOV eax,1
	INT 0x80
