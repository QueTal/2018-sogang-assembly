TITLE Assignment 2 code: 20151521 Kibeom's code

INCLUDE irvine32.inc

.data
INCLUDE hw2.inc

.code
main PROC
	mov eax, val3	;eax = val3
	sub eax, val4	;eax = val3 - val4
	mov ebx, eax	;ebx = val3 - val4
	add eax, eax	;eax = 2(val3 - val4)
	add eax, eax	;eax = 4(val3 - val4)
	add eax, ebx	;eax = 5(val3 - val4)
	mov val3, eax	;val3 = 5(val3 - val4)

	mov ecx, val1	;ecx = val1
	add ecx, val2	;ecx = val1 + val2
	add ecx, ecx	;ecx = 2(val1 + val2)
	add ecx, ecx	;ecx = 4(val1 + val2)
	mov val4, ecx	;val4 = 4(val1 + val2)
	add ecx, ecx	;ecx = 8(val1 + val2)
	add val4, ecx	;val4 = 12(val1 + val2)

	mov ebx, val1	;ebx = val1
	add ebx, ebx	;ebx = 2val1
	add ebx, val2	;ebx = 2val1 + val2

	mov eax, val2	;eax = val2
	add eax, eax	;eax = 2val2
	add eax, eax	;eax = 4val2
	add eax, eax	;eax = 8val2
	mov val1, eax	;val1 = 8val2
	add eax, eax	;eax = 16val2
	add eax, eax	;eax = 32val2
	add eax, val1	;eax = 40val2
	sub eax, val2	;eax = 39val2

	add eax, val4	;eax = 39val2 + 12(val1 + val2)
	add eax, val3	;eax = 39val2 + 12(val1 + val2) + 5(val3 - val4)

	add ebx, val4	;ebx = 2val1 + val2 + 12(val1 + val2)
	mov ecx, val3	;ecx = 5(val3 - val4)
	add ecx, val3	;ecx = 10(val3 - val4)
	add ecx, val3	;ecx = 15(val3 - val4)
	sub ebx, ecx	;ebx = 2val1 + val2 + 12(val1 + val2) - 15(val3 - val4)
	call DumpRegs
	INVOKE ExitProcess, 0
main ENDP
END main