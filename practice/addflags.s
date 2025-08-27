section .data

section .text

global _start

_start:
	MOV al,0b11111111
	MOV bl,0b0001
	ADD al,bl	; adds both and stores in eax
	ADC ah,0	; adds the carry and zero into the higher register of a
	INT 80h
