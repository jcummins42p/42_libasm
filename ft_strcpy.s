; C function declaration ft_strcpy(char *dst, char *src);

global ft_strcpy
section .text

; argument order: rdi, rsi, rdx, rcx, r8, r9
; argument 2 is src, copy depends on its length only
ft_strcpy:
	xor rax,rax	; zero the count

.loop:
	cmp byte [rsi + rax], 0 ; check there is more source to write
	je .done
	mov rbx,[rsi + rax]		; put current src byte in temp register
	mov [rdi + rax],rbx 	; copy the byte from src to dst
	inc rax
	jmp .loop

.done:
	mov [rdi + rax], byte 0x00
	mov rax,rdi			; return a pointer to dst
	ret

; intermediate register is necessary, memory to memory copies are not suported
; need to be explicit about number sizes when MOV into a memory location,
; it can deduce register size but not memory location size
