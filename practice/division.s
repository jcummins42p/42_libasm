section .text
global _start

_start:
	MOV eax,11	; accumulator register to be divided
	MOV ecx,2
	DIV ecx		; eax gets the result 5, edx gets the remainder 1
	INT 0x80	; 0x like h denotes hex value
