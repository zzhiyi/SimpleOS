[bits 16]
	; prints a null - terminated string pointed to by BX
print_string:
	pusha
	mov ah,0x0e 			; int 10/ah = 0x0e -> scrolling teletype BIOS routine
print_string_loop :
	mov al,[bx] 			; Store the char at BX in AL
	cmp al,0 				; if (al == 0), at end of string, so
	je print_string_done 	; jump to print_string_done
	int 0x10				; issue interrupt to print a character
	inc bx 					; Increment BX to the next char in string.
	jmp print_string_loop 	; loop around to print the next char.
print_string_done :
	popa
	ret 					; Return from the function