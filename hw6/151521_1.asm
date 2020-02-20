Include irvine32.inc

.data
include hw6_1.inc
msg BYTE "Copied string : ", 0

.code
main PROC
	mov eax, LENGTHOF strSrc				;�־��� ���ڿ��� ���� ����.
	dec eax									;null���� ������ ���̷� ����.
	cmp  eax, 40							;40�� �ʰ��ϸ� L1���ΰ��� ����.
	ja L1
	call stringCopy							;�ƴϸ� stringCopy��.
L1: Invoke ExitProcess, 0
main ENDP
stringCopy PROC								;copyNum��ŭ copy�ϰ� �����.
	mov esi, OFFSET strSrc
	mov edi, OFFSET strDest
	mov edx, OFFSET msg
	call WriteString						;��¸޽��� ���.
	movzx ecx, copyNum						;copyNum��ŭ �ݺ�.
	L1:	
		mov eax, [esi]
		mov [edi], eax						;srcDest�� ������.
		call WriteChar						;�ű� ���� ���.
		inc esi
		inc edi
		loop L1
		call Crlf
	ret
stringCopy ENDP
END main