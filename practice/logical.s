section .text
global _start

_start:
	MOV eax,0b1010
	MOV ebx,0b1100
	AND eax,ebx		; logical &
	MOV eax,0b1010
	MOV ebx,0b1100
	OR eax,ebx		; logical |
	MOV eax,0b1010
	NOT eax			; flips bits
		; BUT negating eax negates ALL of eax, including the unused 0 bits,
		; resulting in 0xfffffff5 (-11) instead of the expected 0b0101 (5)
	AND eax,0b1111	; so we then bit mask the result to clear everything but the last 4 bits
		; could also use 0xF instead of the literal binary
	MOV eax,0b1010
	MOV ebx,0b1100
	XOR eax,ebx		; Only 1 if one of the bits is on. Not both or 0
					; So this results in 0b0110 (6)
	INT 0x80
