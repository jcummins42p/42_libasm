section .data
	list DB 1,2,3,4

section .text
global _start

_start:
	MOV eax,0	;	use this as an index
	MOV cl,0	;	becaue the list is bytes, use a single byte register

loop:
	MOV bl,[list + eax]	;	indexing through the list
	ADD cl,bl	;	adding the number retreived from the list to the accumulation
;	ADD eax,1	;	increment index
	INC eax		;	alternative increment instruction
	CMP eax,4	;	check to see if we are at the end of the array
;	JE	end		;	if so, jump to end
;	JMP loop	;	return to start of loop
	JNE loop	;	this sums both above commands in a more efficient way
end:
	MOV eax,1	;	need to give eax and ebx numbers that interrupt expects
	MOV ebx,1
	INT 0x80
