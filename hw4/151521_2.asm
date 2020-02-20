INCLUDE irvine32.inc

.data
msg1 BYTE "Enter a plain text : ", 0
msg2 BYTE "Enter a key : ", 0
msg3 BYTE "Original Text : ", 0
msg4 BYTE "Encrypted Text : ", 0
msg5 BYTE "Decrypted Text : ", 0
msg6 BYTE "Bye!", 0
key BYTE  10 DUP(0)
tkey BYTE  40 DUP(0)
input BYTE 40 DUP(0)
tinput BYTE 40 DUP(0)
kcount DWORD 0
count DWORD 0
temp BYTE 0

.code
main PROC
;L1은 main 프로시저에서 계속하여 입력을 받고 엔터가 나올때 종료되는 루프임.
L1:
	call begin		
	mov edx, OFFSET msg3
	call WriteString
	mov edx, OFFSET input	;입력받은 문자열 출력
	call WriteString
	call Crlf
	call Encrypt			;암호화한 문자열 출력	
	call Decrypt			;해독한 문자열 출력
	call Crlf
	call Crlf
	loop L1
	INVOKE ExitProcess, 0
main ENDP

begin PROC					;맨 처음 plain text와 key 값을 입력받는 프로시저.
	mov edx, OFFSET msg1
	call WriteString
	mov edx, OFFSET input
	mov ecx, SIZEOF input
	call ReadString
	mov count, eax			;입력받은 문자길이를 count에 저장.	
	cmp eax, 0				;엔터가 입력되었는지 확인함.
	jnz next				;엔터가 아니면 next로.
	call bye				;엔터가 맞으면 bye 프로시저로.
next:
	mov edx, OFFSET msg2
	call WriteString
	mov edx, OFFSET key
	mov ecx, SIZEOF key
	call ReadString
	mov kcount, eax			;입력받은 key의 길이를 kcount에 저장.
	call Crlf
	call Crlf
	ret
begin ENDP

bye PROC					;엔터 입력시 문구를 출력하고 종료하는 프로시저.
	mov edx, OFFSET msg6
	call WriteString
	call Crlf
	INVOKE ExitProcess, 0
bye ENDP

Encrypt PROC				;입력받은 문자열을 입력받은 key 값으로 암호화하는 프로시저.
	mov ebx, 0
	mov ecx, count
case:
	mov esi, 0
L1:
	cmp esi, kcount
	je case					;esi가 kcount와 같으면 case로
	mov al, key[esi]
	mov tkey[ebx], al
	inc esi
	inc ebx
	loop L1					;key값을 input개수만큼 순환하여 tkey에 저장함.
	
	mov edx, OFFSET msg4
	call WriteString
	mov esi, 0
	mov ecx, count
L2:							;key값과 입력받은 문자열 input값을 XOR 연산하고 tinput에 저장하는 루프.
	mov al, tkey[esi]
	mov bl, input[esi]
	XOR bl, al
	mov tinput[esi], bl
	mov temp, bl
	mov edx, OFFSET temp	;출력은 null도 출력할 수 있게 temp에 저장하여 하나씩 출력.
	call WriteString
	inc esi
	loop L2

	call Crlf
	ret
Encrypt ENDP

Decrypt PROC				;암호화된 문자열을 key값을 이용해 다시 원래 문자로 해독하는 프로시저.
	mov ebx, 0
	mov ecx, count
	mov edx, OFFSET msg5
	call WriteString
	mov esi, 0
	mov ecx, count
L2:							;tkey와 변환된 tinput값을 XOR하여 input에 다시 저장함.
	mov al, tkey[esi]
	mov bl, tinput[esi]
	XOR bl, al
	mov input[esi], bl
	mov temp, bl
	mov edx, OFFSET temp	;XOR연산 값을 temp에 저장하여 출력함.
	call WriteString
	inc esi
	loop L2
	ret
Decrypt ENDP
END main