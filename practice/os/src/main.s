; Simple bootloader
ORG 0x7C00	; All addressing done relative to this address
			; BIOS loads everything at this address
BITS 16		; Setting bits for operating system
			; For backwards compatibility - move to 32 or 64 after setup

main:
	MOV ax,0	; Initialize ax register to 0 and use that to write to others
	MOV ds,ax	; ds tracks start address of 'data' segment
	MOV es,ax	; es tracks start address of 'extra' segment
	MOV ss,ax	; ss sets start address of the stack

	MOV sp,0x7C00	; stack pointer to start address of application
		; the stack grows downwards, so this allows it to extend away from thhe
		; application code
	MOV si,os_boot_msg	; put the address of the boot message in this register
	CALL print
	HLT		; Halt instruction pauses the CPU until a particular signal

halt:
	JMP halt	; To freeze OS

print:	; save register values on the stack
	PUSH si
	PUSH ax
	PUSH bx

print_loop: ; loads data from string into memory, print character by character
	LODSB	; load single byte (char) into the al register
	OR al,al	; checks whether current byte is null and sets zero flag if so
	JZ done_print

	MOV ah,0x0E	; printing a character to the screen
	MOV bh,0	; page number (multiple monitors, for example)
	INT 0x10	; video interrupt - value in ah dictates PRINT value in al

	JMP print_loop

done_print: ; put the previous register values back from the stack
	POP bx
	POP ax
	POP si
	RET

os_boot_msg: DB "Hello OS World!",0x0D,0x0A,0 ; carriage return, newline, null

TIMES 510-($-$$) DB 0	; TIMES repeats an instruction a set number of times
						; $-$$ is how many bytes out program currently takes up
						; So this will write enough 0 bytes to get us to 510
						; bytes after 0x7C00 in memory
DW 0xAA55	; Write the bootloader signature value in the last 2 bytes to make
			; up a full 512 byte memory block
