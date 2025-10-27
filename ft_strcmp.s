; **************************************************************************** #
;                                                                              #
;                                                         :::      ::::::::    #
;    ft_strcmp.s                                        :+:      :+:    :+:    #
;                                                     +:+ +:+         +:+      #
;    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
;                                                 +#+#+#+#+#+   +#+            #
;    Created: 2025/09/19 15:08:47 by jcummins          #+#    #+#              #
;    Updated: 2025/09/19 15:08:47 by jcummins         ###   ########.fr        #
;                                                                              #
; **************************************************************************** #

global ft_strcmp

section .text

; argument order: rdi, rsi
ft_strcmp:

.loop:
	mov dl,[rdi]
	mov cl,[rsi]
	cmp byte dl, 0x00
	je	.end
	cmp dl,cl
	jne	.end
	inc rdi	; increment both pointers
	inc rsi
	jmp	.loop

.end:
	;	movzx = move with zero extension
	movzx eax,dl ; need to promote bytes to 32-bit int for return value
	movzx ecx,cl
	sub eax,ecx
	ret

;	Needing to debug this with valgrind, since it's producing different results
;	valgrind --vgdb=yes --vgdb-error=0 <prog>
;	in another shell:	gdb <prog>
;	then in gdb:		target remote vgdb
;	This ONLY happens when strings are unequal length
