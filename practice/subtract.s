section .data

section .text
global _start

_start:
	MOV eax,3
	MOV ebx,5
	SUB eax,ebx	; takes ebx (5) from eax and stores -2 in eax
	ADD eax,2	; takes eax back up to 0
				; 0xfffffffe + 0x00000002 = 0x00000000
	INT 80h
