INCLUDE irvine32.inc

.data
var1 BYTE "65",0

.code
main PROC
	mov ecx, LENGTHOF var1		;ecx에 전체 길이를 저장.
	sub ecx, 2					;ecx에서 2를 빼서 마지막 수는 한번만 더하게 함.
	mov esi, offset var1		;esi에 첫번째 수의 주소를 저장.
	mov dl, [esi]				;dl에 esi가 가리키는 수의 아스키코드 값을 저장.
	sub dl, 30h					;아스키코드값을 원래 수로 바꾸기 위해 30h를 뺌.
	movzx edx, dl				;edx에 dl 값을 넣어줌.
	movzx eax, dl				;eax에 dl 값을 넣어줌.
L1:
	add eax, eax				;eax를 2배 함.
	add eax, eax				;eax를 4배 함.
	add eax, eax				;eax를 8배 함.
	sub eax, edx				;eax를 7배로 만듬.
	inc esi						;다음 자리 수를 가리키게 함.
	mov dl, [esi]				;dl에 esi가 가리키는 수의 아스키코드 값을 저장.
	sub dl, 30h					;아스키코드값을 원래 수로 바꾸기 위해 30h를 뺌.
	movzx edx, dl				;edx에 dl 값을 넣어줌.
	add eax, edx				;eax에 edx를 더함.
	mov edx, eax				;eax를 edx로 옮김.
	loop L1						
	call DumpRegs
	INVOKE ExitProcess, 0
main ENDP
END main