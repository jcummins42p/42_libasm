; comments in assembly indicated by semi-colon
; ft_strlen.s (NASM, Linux x86-64 SysV calling convention)
; size_t ft_strlen(const char *s);
; RDI, as first and only argument, contains pointer to char * arg.

; to use gdb with nasm, set to use intel-style disassembly with the command
;	set disassembly-flavor intel

global ft_strlen
section .text

ft_strlen:
	xor	rax,rax	; rax = length (counter)
		; best & idiomatic way to zero a register
		; smaller and faster than MOV RAX,0
			; encodes in fewer bytes and doesn't need to fetch a 0
			; the CPU recognises it as a zeroing idiom
				; clears without depending on a prior state/dependancy chain
.loop:
	cmp	byte [rdi + rax], 0	 ; s[rax] == '\0' ?
	je	.done	; jump equal
	inc	rax		; if not, increment counter
	jmp	.loop	; repeat loop
.done:
	ret

; no need to worry about integer wraparound of the 64-bit rax register
; 1.8x10^19 byte long string would be taking exabytes of storage
