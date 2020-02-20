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
;L1�� main ���ν������� ����Ͽ� �Է��� �ް� ���Ͱ� ���ö� ����Ǵ� ������.
L1:
	call begin		
	mov edx, OFFSET msg3
	call WriteString
	mov edx, OFFSET input	;�Է¹��� ���ڿ� ���
	call WriteString
	call Crlf
	call Encrypt			;��ȣȭ�� ���ڿ� ���	
	call Decrypt			;�ص��� ���ڿ� ���
	call Crlf
	call Crlf
	loop L1
	INVOKE ExitProcess, 0
main ENDP

begin PROC					;�� ó�� plain text�� key ���� �Է¹޴� ���ν���.
	mov edx, OFFSET msg1
	call WriteString
	mov edx, OFFSET input
	mov ecx, SIZEOF input
	call ReadString
	mov count, eax			;�Է¹��� ���ڱ��̸� count�� ����.	
	cmp eax, 0				;���Ͱ� �ԷµǾ����� Ȯ����.
	jnz next				;���Ͱ� �ƴϸ� next��.
	call bye				;���Ͱ� ������ bye ���ν�����.
next:
	mov edx, OFFSET msg2
	call WriteString
	mov edx, OFFSET key
	mov ecx, SIZEOF key
	call ReadString
	mov kcount, eax			;�Է¹��� key�� ���̸� kcount�� ����.
	call Crlf
	call Crlf
	ret
begin ENDP

bye PROC					;���� �Է½� ������ ����ϰ� �����ϴ� ���ν���.
	mov edx, OFFSET msg6
	call WriteString
	call Crlf
	INVOKE ExitProcess, 0
bye ENDP

Encrypt PROC				;�Է¹��� ���ڿ��� �Է¹��� key ������ ��ȣȭ�ϴ� ���ν���.
	mov ebx, 0
	mov ecx, count
case:
	mov esi, 0
L1:
	cmp esi, kcount
	je case					;esi�� kcount�� ������ case��
	mov al, key[esi]
	mov tkey[ebx], al
	inc esi
	inc ebx
	loop L1					;key���� input������ŭ ��ȯ�Ͽ� tkey�� ������.
	
	mov edx, OFFSET msg4
	call WriteString
	mov esi, 0
	mov ecx, count
L2:							;key���� �Է¹��� ���ڿ� input���� XOR �����ϰ� tinput�� �����ϴ� ����.
	mov al, tkey[esi]
	mov bl, input[esi]
	XOR bl, al
	mov tinput[esi], bl
	mov temp, bl
	mov edx, OFFSET temp	;����� null�� ����� �� �ְ� temp�� �����Ͽ� �ϳ��� ���.
	call WriteString
	inc esi
	loop L2

	call Crlf
	ret
Encrypt ENDP

Decrypt PROC				;��ȣȭ�� ���ڿ��� key���� �̿��� �ٽ� ���� ���ڷ� �ص��ϴ� ���ν���.
	mov ebx, 0
	mov ecx, count
	mov edx, OFFSET msg5
	call WriteString
	mov esi, 0
	mov ecx, count
L2:							;tkey�� ��ȯ�� tinput���� XOR�Ͽ� input�� �ٽ� ������.
	mov al, tkey[esi]
	mov bl, tinput[esi]
	XOR bl, al
	mov input[esi], bl
	mov temp, bl
	mov edx, OFFSET temp	;XOR���� ���� temp�� �����Ͽ� �����.
	call WriteString
	inc esi
	loop L2
	ret
Decrypt ENDP
END main