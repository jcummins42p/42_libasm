section .data
	num DD 5 ; 32 bits/4 bytes memory containing value '5' on the stack with name num

section .text
global _start

_start:
	MOV eax,1
;	MOV ebx,num ; this actually puts the ADDRESS of num into the register
				; you can print the value at a stack address in DGB with
				; x/x $ebx
	MOV ebx,[num]	; this gets the value at num
	INT 80h
