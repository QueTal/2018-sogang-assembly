INCLUDE irvine32.inc

.data
INCLUDE hw5_1.inc
msg1 BYTE "Original Text : ", 0
msg2 BYTE "Encrypted Text : ", 0
msg3 BYTE "Decrypted Text : ", 0
tkey SBYTE  40 DUP(0)
kcount DWORD 0

.code
main PROC
	mov edx, OFFSET msg1					;해당 문자열들을 출력함.
	call WriteString
	mov edx, OFFSET PlainText
	call WriteString
	call Crlf 

	mov kcount, LENGTHOF keyRotate
	mov edx, LENGTHOF PlainText
	dec edx
	mov ebx, 0
	mov ecx, edx
	case:
		mov esi, 0
	L1:
		cmp esi, kcount
		je case								;esi가 kcount와 같으면 case로 가서 esi를 0으로 초기화.
		mov al, KeyRotate[esi]
		mov tkey[ebx], al
		inc esi
		inc ebx
	loop L1									;key값을 input개수만큼 순환하여 tkey에 저장하는 루프 L1.
	
	mov edx, OFFSET msg2					;메세지 출력.
	call WriteString
	call Encrypt							;암호화함.

	mov edx, OFFSET msg3					;메세지 출력.
	call WriteString
	call Encrypt							;해독함.

	INVOKE ExitProcess, 0
main ENDP

Encrypt PROC				
	mov esi, 0
	mov ecx, LENGTHOF PlainText
	dec ecx									;ecx에 null을 제외한 PlainText의 길이를 저장.
	push ecx
	L1:
		mov al, PlainText[esi]
		mov bl, tkey[esi]
		push ecx
		movzx ecx, tkey[esi]				;key의 수만큼 loop돌수 있게 ecx 설정.
		cmp tkey[esi], 0
		jge calP							;0이상 일떄.
		jmp change							;음수일때.
		save:
			call WriteChar
			mov PlainText[esi], al			;연산결과 PlainText[esi]에 저장.
			inc esi							;다음 문자를 가리키기 위해 esi 증가.
			pop ecx							;L1의 loop counter pop함.
	loop L1
	
	pop ecx
	mov esi, 0
	L2:										;tkey의 모든 값들을 neg하여 해독에 사용할 수 있게함.
		neg tkey[esi]
		inc esi
		loop L2
	call Crlf
	ret

	calP:									;tkey[esi]값이 양수 일때 바로 연산함.
		cmp tkey[esi], 0
		je save								;key=0이면 save로 가서 그대로 저장.
		ror al, 1
		loop calP
		jmp save
	change:
		neg tkey[esi]						;음수인 tkey[esi]를 양수로 만듬.
		mov cl, tkey[esi]
		neg tkey[esi]						;원래대로 다시 음수로 만듬.
	calN:									;tkey[esi]가 음수인 경우의 rotate 연산하는 곳.
		rol al, 1							
	loop calN
	jmp save	
Encrypt ENDP
END main