; **************************************************************************** #
;                                                                              #
;                                                         :::      ::::::::    #
;    ft_strcpy.s                                        :+:      :+:    :+:    #
;                                                     +:+ +:+         +:+      #
;    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
;                                                 +#+#+#+#+#+   +#+            #
;    Created: 2025/09/19 15:08:26 by jcummins          #+#    #+#              #
;    Updated: 2025/09/19 15:08:26 by jcummins         ###   ########.fr        #
;                                                                              #
; **************************************************************************** #

; C function declaration ft_strcpy(char *dst, char *src);
bits 64
default rel
global ft_strcpy
section .text

; argument order: rdi, rsi, rdx, rcx, r8, r9
; argument 2 is src, copy depends on its length only
; Callee-saved registers need to be saved and reset to original values
;	these inclue: rbx, rbp, r12-15
ft_strcpy:
	xor rax,rax	; zero the count

.loop:
	cmp byte [rsi + rax], 0 ; check there is more source to write
	je .done
	;mov rbx,[rsi + rax]	; This didn't work - copied 8 bytes at a time
	;mov [rdi + rax],rbx 	; because it used the whole 64-bit register
	;mov bl,[rsi + rax]		; put current src byte in temp 8-bit register
	;mov [rdi + rax],bl 		; but b is a callee-saved register so this was
		; clobbering values in rbx that needed to be saved
	mov dl,[rsi + rax]
	mov [rdi + rax], dl
	inc rax
	jmp .loop

.done:
	mov [rdi + rax], byte 0x00
	mov rax,rdi			; return a pointer to dst
	ret

; intermediate register is necessary, memory to memory copies are not suported
; need to be explicit about number sizes when MOV into a memory location,
; it can deduce register size but not memory location size
