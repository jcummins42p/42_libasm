section .bss	;	block starting symbol, declared, not assigned
	num RESB 3

section .data	; initialized to a default value
	num2 DB 3 DUP(2) ; will write 2 into memory 3 times, equivalent to 2,2,2

section .text

global _start

_start:
;	MOV [num],1	; won't work - assembly has no understanding of variable size
	MOV bl,1		; put the number in a register first
	MOV [num],bl	; move register to reserved space, giving info about variable size
	MOV [num+1],bl	; access second byte
	MOV [num+2],bl	; access third byte.
;	For larger variables you must be accurate about number of bytes, unlike C pointers
;	But you can do [array + ebx*4] to explicitly scale the number with the register size
	MOV eax,1
	INT 80h
