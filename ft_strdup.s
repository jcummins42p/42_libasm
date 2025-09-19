; **************************************************************************** #
;                                                                              #
;                                                         :::      ::::::::    #
;    ft_strdup.s                                        :+:      :+:    :+:    #
;                                                     +:+ +:+         +:+      #
;    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
;                                                 +#+#+#+#+#+   +#+            #
;    Created: 2025/09/19 15:08:59 by jcummins          #+#    #+#              #
;    Updated: 2025/09/19 15:08:59 by jcummins         ###   ########.fr        #
;                                                                              #
; **************************************************************************** #

; char *strdup(const char *s)
; rdi, rsi, rdx
bits 64
default rel

global ft_strdup
extern malloc
extern ft_strcpy
extern ft_strlen

section .text

;	check alignment in GDB
;	printf "%s" (long)$rsp % 16 ? "MISALIGNED" : "ALIGNED"
;	to break at a GDB address in assembly:
;		break *0x4016e9
ft_strdup:
	sub	rsp,8	; since we are calling immediately, align the stack
	; need to get strlen, which will return into rax and call with rdi
	; rdi already pointing to the string, so just call?
	call ft_strlen ; we should now have strlen in rax
	; need to save rdi and call malloc with rax + 1
	add rsp,8	; prepare alignment
	push rdi	; save rdi to stack now rsp % 16 = 8.
	inc rax		; extra byte for null
	mov rdi,rax; extra byte for null
	; doesn't work, defaults to R_X86_64_PC32 relocation flavour, instead of plt
	call malloc	WRT ..plt ; procedure linkage table.

	cmp rax,0x00	; null return check
	je	err_malloc

	pop rsi			; put src string back into rsi
	mov rdi,rax		; storing malloc'd pointer in rdi (dst)
					; overwriting strlen + 1, which is not needed
	sub	rsp,8		; align stack again
	call ft_strcpy	; copy from src rsi into dest rax.
					; rax now contains a pointer to return string
	add rsp, 8
	ret

err_malloc:
	xor rax,rax
	ret
