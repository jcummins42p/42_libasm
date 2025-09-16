global ft_strcmp

section .text

; argument order: rdi, rsi
ft_strcmp:
	cmp byte [rdi], 0x00	; only checking if rdi is null
		; logically, if rsi is null and rdi isn't, that will be caught in cmp
	je	end
	mov dl,[rdi]
	cmp dl,[rsi]
	jne end

loop:
	inc rdi	; increment both pointers
	inc rsi
	cmp byte [rdi], 0x00
	je	end
	mov dl,[rdi]
	cmp dl,[rsi]
	je	loop

end:
	movsx rax,byte [rdi] ; need to promote bytes to 32-bit int for return value
	movsx rcx,byte [rsi]
	sub rax,rcx
	ret
