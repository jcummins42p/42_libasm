section .data
	num DB 1
	num2 DB 2

section .text
global _start

_start:
;	MOV ebx,[num]	; this moves 32 bits even though num is only 8 bit
;	MOV ecx,[num2]	; as does this
	MOV bl,[num]	; now we're getting the first byte in this register
	MOV cl,[num2]	; and the second
	MOV eax,1
	INT 80h
