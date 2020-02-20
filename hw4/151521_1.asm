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

;L1���� �Է¹��� ���ڸ� �Է¹����鼭 �� ������ ���̰� 40�� �Ѿ������ 
;�Է¹��� ���ڰ� �������� Ȯ���ϰ� �����̸� bye�� ���� ������ ����ϰ� �����Ŵ.
;�� �̿��� �Է��� ��� convert ���ν������� ��ҹ��� ��ȯ�� �Ųٷ� ����� ��.

bye:
	mov edx, OFFSET msg3
	call WriteString
	call Crlf
	INVOKE EXITPROCESS, 0
main ENDP

convert PROC				;convert���� �Է¹��� ������ ��ҹ��ڸ� ��ȯ�ϰ� �Ųٷ� �����.
	mov esi, 0
	mov ecx, count			;������ ���� ���̸�ŭ ���� ecx�� �Է¹����� ������ count�� �ʱ�ȭ��.
L1:
	movzx eax, input[esi]
	cmp eax,  65			;�ƽ�Ű �ڵ� ���� "A"���� ū�� ��.
	jae L2					;ũ�ų� ���ٸ� L2�� 
	jmp last				;�ƴ϶�� last��
L2:							
	cmp eax, 90				;"Z"�� ���ؼ� �빮������ Ȯ���� ��.
	jbe cal1				;���ĺ� �빮�ڰ� �´ٸ� cal1����
	jmp L3					;�ƴ϶�� L3��
cal1:			
	add eax, 32				;�빮�ڸ� �ҹ��ڷ� ��ȯ.
	jmp last				
L3:
	cmp eax, 97				;"a"���� ū�� ��.
	jae L4					;ũ�ų� ���ٸ� L4��
	jmp last				;�ƴϸ� last��	
L4:
	cmp eax, 122			;"z"�� ���� ���ĺ� �ҹ��ڶ� �´��� Ȯ���Ϸ���.
	jbe cal2				;�ҹ��ڰ� �´ٸ� cal2��
	jmp last				;�ƴ϶�� last��
cal2:
	sub eax, 32				;�ҹ��ڸ� �빮�ڷ� ��ȯ.
	jmp last
last:						;�Ųٷ� ����ϱ����� stack���� push ��.
	push eax
	inc esi
	loop L1

	mov esi, 0
	mov ecx, count	
L5:							;stack�� �־�� ��ȯ�� ���ڸ� pop ������.
	pop eax
	mov input[esi], al		;���� ���� �ִ� �޸𸮿� �Ųٷ� ������.
	inc esi
	loop L5

	mov edx, OFFSET msg2
	call WriteString
	mov edx, OFFSET input	;��ȯ�� �Ųٷ� ������ ���ڸ� ���.
	call WriteString
	call Crlf

	ret
convert ENDP
END main