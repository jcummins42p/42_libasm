section .data
	x DD 3.14
	y DD 2.1

section .text
global _start

_start:
	MOVSS xmm0,[x]	; SS = Scalar Singleprecision
				; registers xmm0 to xmm15 are designed to hold decimal values
				; Scalar is a single decimal value
				; registers can work with packed data, multiple values together
				; recall that [x] means the value held at address x in .data
	MOVSS xmm1,[y]
	ADDSS xmm0,xmm1	; specific instruction name for decimal values
	MOV ebx,1
	INT 0x80
