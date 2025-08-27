section .data
	x DD 3.14
	y DD 2.1

section .text
global _start

_start:
	MOVSS xmm0,[x]
	MOVSS xmm1,[y]
;	CMP	; Won't work with floats
	UCOMISS xmm0,xmm1	; comparison AND jumps are different
	JB jumpbelow 	; jump below, equivalent to 'less than'
;	JBE jbelowequal	; below or equals
;	JA jumpabove	; equivalent to 'greater than'
;	JAE jaboveequal ; etc
;	JE jumpequals	; works the same on floats and bits
	JMP end

jumpbelow:
	MOV ecx,1
	JMP end

end:
	MOV eax,1
	MOV ebx,1
	INT 0x80

