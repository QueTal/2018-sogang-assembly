Include irvine32.inc

.data
include hw6_2.inc
msg BYTE "Position value : ",0
count DWORD 0

.code
main PROC
	mov eax, LENGTHOF target
	mov ebx, LENGTHOF source
	cmp eax, ebx									;source가 target보다 긴지 비교.
	jb L1											;작으면 L1으로 가서 종료.
	call getPos										;아니면 getPos로 가서 탐색.
	L1:
		Invoke ExitProcess, 0
main ENDP
getPos PROC
	mov esi, 0										;target의 index.
	mov edi, 0										;source의 index.
	mov edx, LENGTHOF source
	dec edx											;edx에 source의 null을 제외한 길이저장.
	mov ecx, LENGTHOF target
	dec ecx											;ecx에 target의 null을 제외한 길이저장하여 loop 돌림.
	L1:
		movzx eax, target[esi]
		cmp al, source[edi]							;target이랑 source비교.
		jne L2										;같지 않으면 L2로 가서 esi는 증가, edi와 count는 초기화.
		inc esi										;같으면 esi, edi, count 모두 증가.
		inc edi
		inc count
		cmp count, edx								;count랑 edx를 비교해 source가 다 나왔는지 확인.
		je L3										;같으면 L3로.
		jmp last									
		L2:
			inc esi
			mov edi, 0
			mov count, 0
		last:
			loop L1
	L3:
		mov edx, OFFSET msg						
		call WriteString							;메세지 출력
		sub esi, count								;target의 현재 index에서 source의 길이를 빼줌.
		mov pos, esi								;위치를 pos에 저장.
		mov eax, pos
		call WriteDec								;출력.
		call Crlf
	ret
getPos ENDP
END main