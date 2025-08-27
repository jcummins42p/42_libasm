extern test	; the function we defined as extern in test.c
extern exit	; standard c function

section .data

section .text
global main

main:
	PUSH 1	; putting 1 as the second argument onto the stack
	PUSH 2	; putting 2 as the first argument onto the stack
	CALL test ; return value automaticall stored in eax
	PUSH eax
	CALL exit
