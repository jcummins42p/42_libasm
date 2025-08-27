section .text
global _start

_start:
	MOV al,255
	MOV bl,2
	MUL bl	; MUL instruction automatically applies using the a register
			; a is a special purpose register 'accumulator' where multiplication results go
	MOV al,0xFF
	IMUL bl
	INT 80h
