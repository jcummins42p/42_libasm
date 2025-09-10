; comments in assembly indicated by semi-colon
; ft_strlen.s (NASM, Linux x86-64 SysV calling convention)
; size_t ft_strlen(const char *s);

; to use gdb with nasm, set to use intel-style disassembly with the command
;	set disassembly-flavor intel

global ft_strlen
section .text

ft_strlen:
	xor	rax,rax				; rax = length (counter)
.loop:
	cmp	byte [rdi + rax], 0	 ; s[rax] == '\0' ?
	je	.done
	inc	rax
	jmp	.loop
.done:
	ret
