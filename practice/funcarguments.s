section .data

section .text
global main

addTwo:
	PUSH ebp
	MOV	ebp,esp			; storing the stack pointer in ebp
	MOV eax,[ebp+8]		; acessing addresses on the stack with offsets (esp is +4)
	MOV ebx,[ebp+12]	; +4 bytes per 32bit address obviously
	ADD eax,ebx
	POP ebp
	RET

main:
	PUSH 4
	PUSH 1
	CALL addTwo
	MOV	eax,1
	INT 0x80
