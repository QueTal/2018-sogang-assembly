Include irvine32.inc

.data
include hw6_2.inc
msg BYTE "Position value : ",0
count DWORD 0

.code
main PROC
	mov eax, LENGTHOF target
	mov ebx, LENGTHOF source
	cmp eax, ebx									;source�� target���� ���� ��.
	jb L1											;������ L1���� ���� ����.
	call getPos										;�ƴϸ� getPos�� ���� Ž��.
	L1:
		Invoke ExitProcess, 0
main ENDP
getPos PROC
	mov esi, 0										;target�� index.
	mov edi, 0										;source�� index.
	mov edx, LENGTHOF source
	dec edx											;edx�� source�� null�� ������ ��������.
	mov ecx, LENGTHOF target
	dec ecx											;ecx�� target�� null�� ������ ���������Ͽ� loop ����.
	L1:
		movzx eax, target[esi]
		cmp al, source[edi]							;target�̶� source��.
		jne L2										;���� ������ L2�� ���� esi�� ����, edi�� count�� �ʱ�ȭ.
		inc esi										;������ esi, edi, count ��� ����.
		inc edi
		inc count
		cmp count, edx								;count�� edx�� ���� source�� �� ���Դ��� Ȯ��.
		je L3										;������ L3��.
		jmp last									
		L2:
			inc esi
			mov edi, 0
			mov count, 0
		last:
			loop L1
	L3:
		mov edx, OFFSET msg						
		call WriteString							;�޼��� ���
		sub esi, count								;target�� ���� index���� source�� ���̸� ����.
		mov pos, esi								;��ġ�� pos�� ����.
		mov eax, pos
		call WriteDec								;���.
		call Crlf
	ret
getPos ENDP
END main