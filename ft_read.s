; **************************************************************************** #
;                                                                              #
;                                                         :::      ::::::::    #
;    ft_read.s                                          :+:      :+:    :+:    #
;                                                     +:+ +:+         +:+      #
;    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
;                                                 +#+#+#+#+#+   +#+            #
;    Created: 2025/09/23 13:52:05 by jcummins          #+#    #+#              #
;    Updated: 2025/09/23 13:52:05 by jcummins         ###   ########.fr        #
;                                                                              #
; **************************************************************************** #

; ssize_t read(int fd, void buf[count], size_t count);
bits 64
default rel
global ft_read
extern __errno_location	; requires this function to access and change errno
section .text

ft_read:
	mov	rax,0
	;sub rsp,8	; aligning stack before call
	syscall
	cmp rax,0x00
	jl .error
	ret

.error:
	mov rdi,rax
	neg rdi
	call __errno_location wrt ..plt	; puts a pointer to errno location in rax
	mov [rax],edi		; returning -1 to show error
	mov rax,-1
	ret
