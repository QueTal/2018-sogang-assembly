Include irvine32.inc

.data
include hw6_1.inc
msg BYTE "Copied string : ", 0

.code
main PROC
	mov eax, LENGTHOF strSrc				;주어진 문자열의 길이 저장.
	dec eax									;null값을 제외한 길이로 수정.
	cmp  eax, 40							;40자 초과하면 L1으로가서 종료.
	ja L1
	call stringCopy							;아니면 stringCopy로.
L1: Invoke ExitProcess, 0
main ENDP
stringCopy PROC								;copyNum만큼 copy하고 출력함.
	mov esi, OFFSET strSrc
	mov edi, OFFSET strDest
	mov edx, OFFSET msg
	call WriteString						;출력메시지 출력.
	movzx ecx, copyNum						;copyNum만큼 반복.
	L1:	
		mov eax, [esi]
		mov [edi], eax						;srcDest로 복사함.
		call WriteChar						;옮긴 값을 출력.
		inc esi
		inc edi
		loop L1
		call Crlf
	ret
stringCopy ENDP
END main