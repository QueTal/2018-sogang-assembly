INCLUDE irvine32.inc

.data
INCLUDE hw5_2.inc
msg1 BYTE "Before sort : ", 0
msg2 BYTE "After sort : ", 0
eIndex DWORD 0											;짝수번째 숫자를 저장하는 변수
oIndex DWORD 0											;홀수번째 숫자를 저장하는 변수

.code
main PROC
	mov edx, OFFSET msg1								;sort전 메세지와 숫자들 출력.
	call WriteString
	mov esi, 0
	mov ecx, lenData
	L1:
		mov eax, ArrData[esi]
		call WriteHex									;sort 되기 전 주어진 숫자들을 출력.
		cmp ecx, 1										;쉼표와 띄어쓰기를 조절하는 cmp.
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
	push ecx											;원래의 lenData 값 저장
	shr lenData, 1										;lenData / 2
	sub ecx, lenData
	mov ebx, 0
	L1:													;ArrData로 부터 홀수번째 숫자들을 oIndex로 가져옴.
		mov eax, ArrData[esi]
		mov oIndex[ebx], eax
		add ebx, 4
		add esi, 8
	loop L1									

	pop ecx
	push ecx
	sub ecx, lenData									;eIndex의 원소개수.
	dec ecx												;sort를 위한 루프는 원소개수보다 1 적게 돌아야함.
	L2:
		push ecx
		mov esi, 0
		L3:	
			mov ax, WORD PTR [oIndex[esi] + 2]
			mov bx, WORD PTR [oIndex[esi + 4] + 2]
			cmp ax, bx									;x값을 비교.
			ja chg1										;앞의 x가 크면 chg1로 가서 swap함
			jmp chg2									;같거나 작으면 chg2로 가서 y를 비교하거나 그냥 저장.
			back1:
				add esi, 4								;다음 원소들 비교를 위해 index 증가.
		loop L3
	
		pop ecx
	loop L2
	jmp fin1											;sort를 마치면 fin1으로 감.

	chg1:												;앞의 값이 크면 뒤의 값이랑 바꿔줌.
		mov eax, oIndex[esi]
		mov ebx, oIndex[esi + 4]
		mov oIndex[esi], ebx
		mov oIndex[esi + 4], eax						
	jmp back1
		
	chg2:												;앞이 뒤랑 같거나 작은 경우.
		cmp ax, bx	
		jb back1										;앞이 작으면 그냥 그대로.
		mov ax, WORD PTR [OIndex[esi]]					;x끼리 같은 경우.
		mov bx, WORD PTR [oIndex[esi + 4]]				;y를 비교.
		cmp ax, bx			
		jb chg1											;앞의 y가 작으면 chg1로 가서 sawp.						
		jmp back1										;아니면 back1으로 가서 index 증가.

	fin1:	
		pop ecx
		push ecx
		mov esi, 0
		sub ecx, lenData
		mov ebx, 0
	save1:							
		mov eax, oIndex[esi]
		mov ArrData[ebx], eax							;sort한 값을 원래 변수에 index 맞춰서 저장.
		add esi, 4
		add ebx, 8
	loop save1								
;-------------홀수 정렬까지 완료-----------------
	mov esi, 4
	mov ecx, lenData									;이미 원래 값의 반이 되어있음.
	mov ebx, 0
	L4:										
		mov eax, ArrData[esi]
		mov eIndex[ebx], eax							;ArrData의 짝수번째 숫자들을 eIndex에 저장.
		add ebx, 4
		add esi, 8
	loop L4									
	
	mov ecx, lenData									;ecx에 eIndex의 원소 개수를 저장.
	dec ecx												;sort를 위한 루프는 원소개수보다 1 적게 돌아야함.
	L5:
		push ecx
		mov esi, 0
		L6:	
			mov ax, WORD PTR [eIndex[esi] + 2]
			mov bx, WORD PTR [eIndex[esi + 4] + 2]
			cmp ax, bx									
			jb chg3										;x값이 작으면 chg3로 가서 swap 함.
			jmp chg4									;아니면 chg4로 감.
			back2:
				add esi, 4								;다음 숫자 비교를 위해 index 증가.
		loop L6
		pop ecx
	loop L5
	jmp fin2											;sort를 마치면 fin2로 감.

	chg3:												;앞의 값이 작으면 swap함.
		mov eax, eIndex[esi]
		mov ebx, eIndex[esi + 4]
		mov eIndex[esi], ebx
		mov eIndex[esi + 4], eax					
	jmp back2

	chg4:												;앞이 뒤랑 같거나 큰 경우.
		cmp ax, bx	
		ja back2										;앞이 크면 back2로 돌아가서 index 증가.
		mov ax, WORD PTR [eIndex[esi]]					
		mov bx, WORD PTR [eIndex[esi + 4]]				
		cmp ax, bx										;x끼리 같은 경우 y를 비교함.
		ja chg3											;앞의 값이 크면 chg3으로 가서 swap.
		jmp back2										;아니면 back2로 돌아가서 index 증가.			

	fin2:			
		mov esi, 0
		mov ecx, lenData								;eIndex의 원소 개수만큼을 ecx에 저장.
		mov ebx, 4
	save2:					
		mov eax, eIndex[esi]						
		mov ArrData[ebx], eax							;sort한 짝수번째 숫자들을 ArrData의 짝수번째에 저장함.
		add esi, 4
		add ebx, 8
	loop save2	
;-------------짝수 정렬까지 완료-----------------	
	mov edx, OFFSET msg2								;sort 후의 메세지 출력.
	call WriteString
	mov esi, 0
	pop ecx
	L7:
		mov eax, ArrData[esi]
		call WriteHex									;sort 된 값들을 출력.
		cmp ecx, 1										;쉼표와 띄어쓰기를 조절하는 cmp.
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