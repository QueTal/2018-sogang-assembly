INCLUDE irvine32.inc

.data
INCLUDE hw5_2.inc
msg1 BYTE "Before sort : ", 0
msg2 BYTE "After sort : ", 0
eIndex DWORD 0											;¦����° ���ڸ� �����ϴ� ����
oIndex DWORD 0											;Ȧ����° ���ڸ� �����ϴ� ����

.code
main PROC
	mov edx, OFFSET msg1								;sort�� �޼����� ���ڵ� ���.
	call WriteString
	mov esi, 0
	mov ecx, lenData
	L1:
		mov eax, ArrData[esi]
		call WriteHex									;sort �Ǳ� �� �־��� ���ڵ��� ���.
		cmp ecx, 1										;��ǥ�� ���⸦ �����ϴ� cmp.
		je back
		mov eax, ','
		call WriteChar
		mov eax, ' '
		call WriteChar
		back:	
			add esi, 4
	loop L1
	call Crlf
	call sort
	Invoke ExitProcess, 0
main ENDP 

sort PROC
	mov esi, 0
	mov ecx, lenData
	push ecx											;������ lenData �� ����
	shr lenData, 1										;lenData / 2
	sub ecx, lenData
	mov ebx, 0
	L1:													;ArrData�� ���� Ȧ����° ���ڵ��� oIndex�� ������.
		mov eax, ArrData[esi]
		mov oIndex[ebx], eax
		add ebx, 4
		add esi, 8
	loop L1									

	pop ecx
	push ecx
	sub ecx, lenData									;eIndex�� ���Ұ���.
	dec ecx												;sort�� ���� ������ ���Ұ������� 1 ���� ���ƾ���.
	L2:
		push ecx
		mov esi, 0
		L3:	
			mov ax, WORD PTR [oIndex[esi] + 2]
			mov bx, WORD PTR [oIndex[esi + 4] + 2]
			cmp ax, bx									;x���� ��.
			ja chg1										;���� x�� ũ�� chg1�� ���� swap��
			jmp chg2									;���ų� ������ chg2�� ���� y�� ���ϰų� �׳� ����.
			back1:
				add esi, 4								;���� ���ҵ� �񱳸� ���� index ����.
		loop L3
	
		pop ecx
	loop L2
	jmp fin1											;sort�� ��ġ�� fin1���� ��.

	chg1:												;���� ���� ũ�� ���� ���̶� �ٲ���.
		mov eax, oIndex[esi]
		mov ebx, oIndex[esi + 4]
		mov oIndex[esi], ebx
		mov oIndex[esi + 4], eax						
	jmp back1
		
	chg2:												;���� �ڶ� ���ų� ���� ���.
		cmp ax, bx	
		jb back1										;���� ������ �׳� �״��.
		mov ax, WORD PTR [OIndex[esi]]					;x���� ���� ���.
		mov bx, WORD PTR [oIndex[esi + 4]]				;y�� ��.
		cmp ax, bx			
		jb chg1											;���� y�� ������ chg1�� ���� sawp.						
		jmp back1										;�ƴϸ� back1���� ���� index ����.

	fin1:	
		pop ecx
		push ecx
		mov esi, 0
		sub ecx, lenData
		mov ebx, 0
	save1:							
		mov eax, oIndex[esi]
		mov ArrData[ebx], eax							;sort�� ���� ���� ������ index ���缭 ����.
		add esi, 4
		add ebx, 8
	loop save1								
;-------------Ȧ�� ���ı��� �Ϸ�-----------------
	mov esi, 4
	mov ecx, lenData									;�̹� ���� ���� ���� �Ǿ�����.
	mov ebx, 0
	L4:										
		mov eax, ArrData[esi]
		mov eIndex[ebx], eax							;ArrData�� ¦����° ���ڵ��� eIndex�� ����.
		add ebx, 4
		add esi, 8
	loop L4									
	
	mov ecx, lenData									;ecx�� eIndex�� ���� ������ ����.
	dec ecx												;sort�� ���� ������ ���Ұ������� 1 ���� ���ƾ���.
	L5:
		push ecx
		mov esi, 0
		L6:	
			mov ax, WORD PTR [eIndex[esi] + 2]
			mov bx, WORD PTR [eIndex[esi + 4] + 2]
			cmp ax, bx									
			jb chg3										;x���� ������ chg3�� ���� swap ��.
			jmp chg4									;�ƴϸ� chg4�� ��.
			back2:
				add esi, 4								;���� ���� �񱳸� ���� index ����.
		loop L6
		pop ecx
	loop L5
	jmp fin2											;sort�� ��ġ�� fin2�� ��.

	chg3:												;���� ���� ������ swap��.
		mov eax, eIndex[esi]
		mov ebx, eIndex[esi + 4]
		mov eIndex[esi], ebx
		mov eIndex[esi + 4], eax					
	jmp back2

	chg4:												;���� �ڶ� ���ų� ū ���.
		cmp ax, bx	
		ja back2										;���� ũ�� back2�� ���ư��� index ����.
		mov ax, WORD PTR [eIndex[esi]]					
		mov bx, WORD PTR [eIndex[esi + 4]]				
		cmp ax, bx										;x���� ���� ��� y�� ����.
		ja chg3											;���� ���� ũ�� chg3���� ���� swap.
		jmp back2										;�ƴϸ� back2�� ���ư��� index ����.			

	fin2:			
		mov esi, 0
		mov ecx, lenData								;eIndex�� ���� ������ŭ�� ecx�� ����.
		mov ebx, 4
	save2:					
		mov eax, eIndex[esi]						
		mov ArrData[ebx], eax							;sort�� ¦����° ���ڵ��� ArrData�� ¦����°�� ������.
		add esi, 4
		add ebx, 8
	loop save2	
;-------------¦�� ���ı��� �Ϸ�-----------------	
	mov edx, OFFSET msg2								;sort ���� �޼��� ���.
	call WriteString
	mov esi, 0
	pop ecx
	L7:
		mov eax, ArrData[esi]
		call WriteHex									;sort �� ������ ���.
		cmp ecx, 1										;��ǥ�� ���⸦ �����ϴ� cmp.
		je last
		mov eax, ','
		call WriteChar
		mov eax, ' '
		call WriteChar
		last:
			add esi, 4
	loop L7
	call crlf	
	ret
sort ENDP
END main