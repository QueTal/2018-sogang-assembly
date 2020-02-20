INCLUDE irvine32.inc

.data
msg1 BYTE "Type_A_String_To_Reverse: ",0
msg2 BYTE "Reversed_String: ",0
msg3 BYTE "Bye!",0
input BYTE 50 DUP(?)
count DWORD 0

.code
main PROC
L1:									
	mov edx, OFFSET msg1
	call WriteString
	mov edx, OFFSET input
	mov ecx, SIZEOF input
	call ReadString
	
	mov count, eax
	cmp count, 40
	ja L1
	cmp count, 0
	je bye
	
	call convert
loop L1

;L1에서 입력받을 문자를 입력받으면서 그 문자의 길이가 40을 넘어가는지와 
;입력받은 문자가 엔터인지 확인하고 엔터이면 bye로 보내 문구를 출력하고 종료시킴.
;그 이외의 입력의 경우 convert 프로시저에서 대소문자 변환과 거꾸로 출력을 함.

bye:
	mov edx, OFFSET msg3
	call WriteString
	call Crlf
	INVOKE EXITPROCESS, 0
main ENDP

convert PROC				;convert에서 입력받은 문자의 대소문자를 변환하고 거꾸로 출력함.
	mov esi, 0
	mov ecx, count			;루프를 문자 길이만큼 돌게 ecx를 입력문자의 길이인 count로 초기화함.
L1:
	movzx eax, input[esi]
	cmp eax,  65			;아스키 코드 값이 "A"보다 큰지 비교.
	jae L2					;크거나 같다면 L2로 
	jmp last				;아니라면 last로
L2:							
	cmp eax, 90				;"Z"와 비교해서 대문자인지 확실히 함.
	jbe cal1				;알파벳 대문자가 맞다면 cal1으로
	jmp L3					;아니라면 L3로
cal1:			
	add eax, 32				;대문자를 소문자로 변환.
	jmp last				
L3:
	cmp eax, 97				;"a"보다 큰지 비교.
	jae L4					;크거나 같다면 L4로
	jmp last				;아니면 last로	
L4:
	cmp eax, 122			;"z"와 비교해 알파벳 소문자라 맞는지 확인하려함.
	jbe cal2				;소문자가 맞다면 cal2로
	jmp last				;아니라면 last로
cal2:
	sub eax, 32				;소문자를 대문자로 변환.
	jmp last
last:						;거꾸로 출력하기위해 stack으로 push 함.
	push eax
	inc esi
	loop L1

	mov esi, 0
	mov ecx, count	
L5:							;stack에 넣어둔 변환한 문자를 pop 시켜줌.
	pop eax
	mov input[esi], al		;원래 문자 있던 메모리에 거꾸로 저장함.
	inc esi
	loop L5

	mov edx, OFFSET msg2
	call WriteString
	mov edx, OFFSET input	;변환후 거꾸로 저장한 문자를 출력.
	call WriteString
	call Crlf

	ret
convert ENDP
END main