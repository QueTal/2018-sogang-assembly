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
	mov edx, OFFSET msg1					;�ش� ���ڿ����� �����.
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
		je case								;esi�� kcount�� ������ case�� ���� esi�� 0���� �ʱ�ȭ.
		mov al, KeyRotate[esi]
		mov tkey[ebx], al
		inc esi
		inc ebx
	loop L1									;key���� input������ŭ ��ȯ�Ͽ� tkey�� �����ϴ� ���� L1.
	
	mov edx, OFFSET msg2					;�޼��� ���.
	call WriteString
	call Encrypt							;��ȣȭ��.

	mov edx, OFFSET msg3					;�޼��� ���.
	call WriteString
	call Encrypt							;�ص���.

	INVOKE ExitProcess, 0
main ENDP

Encrypt PROC				
	mov esi, 0
	mov ecx, LENGTHOF PlainText
	dec ecx									;ecx�� null�� ������ PlainText�� ���̸� ����.
	push ecx
	L1:
		mov al, PlainText[esi]
		mov bl, tkey[esi]
		push ecx
		movzx ecx, tkey[esi]				;key�� ����ŭ loop���� �ְ� ecx ����.
		cmp tkey[esi], 0
		jge calP							;0�̻� �ϋ�.
		jmp change							;�����϶�.
		save:
			call WriteChar
			mov PlainText[esi], al			;������ PlainText[esi]�� ����.
			inc esi							;���� ���ڸ� ����Ű�� ���� esi ����.
			pop ecx							;L1�� loop counter pop��.
	loop L1
	
	pop ecx
	mov esi, 0
	L2:										;tkey�� ��� ������ neg�Ͽ� �ص��� ����� �� �ְ���.
		neg tkey[esi]
		inc esi
		loop L2
	call Crlf
	ret

	calP:									;tkey[esi]���� ��� �϶� �ٷ� ������.
		cmp tkey[esi], 0
		je save								;key=0�̸� save�� ���� �״�� ����.
		ror al, 1
		loop calP
		jmp save
	change:
		neg tkey[esi]						;������ tkey[esi]�� ����� ����.
		mov cl, tkey[esi]
		neg tkey[esi]						;������� �ٽ� ������ ����.
	calN:									;tkey[esi]�� ������ ����� rotate �����ϴ� ��.
		rol al, 1							
	loop calN
	jmp save	
Encrypt ENDP
END main