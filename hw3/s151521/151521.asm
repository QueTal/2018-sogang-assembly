INCLUDE irvine32.inc

.data
var1 BYTE "65",0

.code
main PROC
	mov ecx, LENGTHOF var1		;ecx�� ��ü ���̸� ����.
	sub ecx, 2					;ecx���� 2�� ���� ������ ���� �ѹ��� ���ϰ� ��.
	mov esi, offset var1		;esi�� ù��° ���� �ּҸ� ����.
	mov dl, [esi]				;dl�� esi�� ����Ű�� ���� �ƽ�Ű�ڵ� ���� ����.
	sub dl, 30h					;�ƽ�Ű�ڵ尪�� ���� ���� �ٲٱ� ���� 30h�� ��.
	movzx edx, dl				;edx�� dl ���� �־���.
	movzx eax, dl				;eax�� dl ���� �־���.
L1:
	add eax, eax				;eax�� 2�� ��.
	add eax, eax				;eax�� 4�� ��.
	add eax, eax				;eax�� 8�� ��.
	sub eax, edx				;eax�� 7��� ����.
	inc esi						;���� �ڸ� ���� ����Ű�� ��.
	mov dl, [esi]				;dl�� esi�� ����Ű�� ���� �ƽ�Ű�ڵ� ���� ����.
	sub dl, 30h					;�ƽ�Ű�ڵ尪�� ���� ���� �ٲٱ� ���� 30h�� ��.
	movzx edx, dl				;edx�� dl ���� �־���.
	add eax, edx				;eax�� edx�� ����.
	mov edx, eax				;eax�� edx�� �ű�.
	loop L1						
	call DumpRegs
	INVOKE ExitProcess, 0
main ENDP
END main