section .text
global _start

_start:
	MOV eax,2
	SHR eax,1	; shifts all bits 1 to the right (divides by 2)
	SHL eax,3	; multiplies by 2 three times (x8) = x2^3
	MOV ebx,-2
	SAR	ebx,1	; arithmetic shift right - preserves the signed bit
	SAL	ebx,3	; arithmetic shift left
	MOV eax,-2
	INT 0x80
