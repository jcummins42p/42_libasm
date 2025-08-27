section .data
	list DB 1,2,3,4,0

section .text

global _start

_start:
	MOV bl,[list]
	MOV eax,1
	INT 80h
