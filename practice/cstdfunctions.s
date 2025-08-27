extern exit
extern printf

section .data
	msg DB "Hello World!",0
	msg2 DB "This is a test!",0
	fmt DB "Output is: %s %s",10,0
section .text
global main

main:	; putting arguments on the FILO stack
	PUSH msg2
	PUSH msg	; First in, Last out
	PUSH fmt
	CALL printf
	PUSH 1		; pushing the argument to exit
	CALL exit
