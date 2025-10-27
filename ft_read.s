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
;.bits 64
;.default rel
global ft_read
extern __errno_location	; requires this function to access and change errno
section .text

ft_read:
	xor	rax,rax	; syscall for read is 0 - this is more efficient than mov
	syscall		; syscalls don't requirestack alignment?
	cmp rax,0
	jl .error
	ret

.error:
	mov rdi,rax
	neg rdi
	sub rsp,8			; align stack before call
	call __errno_location wrt ..plt	; puts a pointer to errno location in rax
	add rsp,8			; restore rsp
	mov [rax],edi		; put errno at the required location
	mov rax,-1
	ret
