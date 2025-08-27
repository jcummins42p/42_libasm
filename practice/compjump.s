section .data

section .text
global _start

_start:
	MOV eax,3
	MOV ebx,2
	CMP eax,ebx	; cmp subtracts the registers and discards the result but flags
				; whether it's positive, negative, or 0
	JL	lesser	; jl = jump lesser, jump if eax is less than ebc
	JLE lequals	; jle = jump if lessor or equals to
	JE	equals	; je = jump equals
	JNE nequals	; jne = jump if not equals
	JG	greater	; jg = jump if greater
	JGE gequals	; jge = greater than or equals
	JZ	iszero	; jz = if result is zero
	JNZ isnzero	; jnz = jump if results isn't zero
	JMP	end		; jmp always runs if execution reaches this point
lesser:			; would always fall through to this command if JMP wasn't used
	MOV ecx,1
	JMP end
lequals:
	MOV ecx,2
	JMP end
equals:
	MOV ecx,3
	JMP end
nequals:
	MOV ecx,4
	JMP end
greater:
	MOV ecx,5
	JMP end
gequals:
	MOV ecx,6
	JMP end
iszero:
	MOV ecx,7
	JMP end
isnzero:
	MOV ecx,8
	JMP end
end:
	INT 0x80

;	notice that the instrutions JZ and JE are equivalent because CMP subracts
;	and evaluates equality based on the result being zero
