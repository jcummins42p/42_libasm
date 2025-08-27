section .data ; stores variables

section .text ; code to run
global _start ; _start is a label for a section of code
			; exporting _start with global which tells the computer where to start the program.
_start:
	MOV eax,1	; MOV moves data from one location to another
	MOV ebx,1
	INT 80h		; interrupt makes system call based on the value in EAX.
				; 1 indicates EXIT system call.
				; The status code is whatever is in EBX
