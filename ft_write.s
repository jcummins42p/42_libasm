; **************************************************************************** #
;                                                                              #
;                                                         :::      ::::::::    #
;    ft_write.s                                         :+:      :+:    :+:    #
;                                                     +:+ +:+         +:+      #
;    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
;                                                 +#+#+#+#+#+   +#+            #
;    Created: 2025/09/23 13:27:10 by jcummins          #+#    #+#              #
;    Updated: 2025/09/23 13:27:10 by jcummins         ###   ########.fr        #
;                                                                              #
; **************************************************************************** #

; creating write(int fd, const void buf[count], size_t count) from unistd.h
; just need to map this to sys_write:
	; rax = 1
	; rdi = unsigned int fd
	; rsi = const char *buf
	; rdx = size_t count
; so actually, all the argument registers should be correct.

;.bits 64
;.default rel
global ft_write
extern __errno_location
section .text

ft_write:
	mov	rax,1
	;sub rsp,8
	syscall
	cmp eax,0x00
	jl .error
	ret

.error:
	mov rdi,rax
	neg rdi
	call __errno_location wrt ..plt
	mov [rax],edi		; returning -1 to show error
	mov rax,-1		; returning -1 to show error
	ret
