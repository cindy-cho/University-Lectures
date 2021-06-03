TITLE Uphills					       (s151610HW04.asm)

; Program Description: This program measure the biggest uphill size of mountains
; Author: 20151610 Yoohwa Cho
; Creation Date : 2021. 05. 21

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW04.inc  ; Includes testcase number, list size and heights of mountains

.data
ANSWER     DWORD 0
MINHEIGHT  DWORD 0

.code
main PROC
	mov ecx, TN						; For���� ������ ���� TN�� �ִ� testcase���� ecx�� �־��ش�.
	mov ebx, 0
L1: 
	push ecx
	mov ecx, CASE[ebx]				; ����Ʈ ������ ������ ecx�� �־��ش�
	mov ANSWER, 0					; ���� �׽�Ʈ���̽��� Answer���� 0���� �ʱ�ȭ �Ѵ�
	cmp ecx, 2						; ������ ������ 2���̻��� ��쿡�� Loop�� �����Ѵ�
	JL L6							; �׷��� ���� ��쿡�� ������ ����ϴ� L2�� �ٷ� �̵��Ѵ�
	dec ecx							; ������ ���� - 1 ��ŭ�� L3�� ���� ������ ecx-1�� ���ش�
	add ebx, 4
	mov eax, CASE[ebx]
	mov MINHEIGHT, eax				; ù��° ���� ���� MINHEIGHT�� �־��ش�
L3:
	mov eax, CASE[ebx]
	add ebx, 4
	cmp eax, CASE[ebx]				; 1��° ���� ������, ���� ���� ���� ���� ũ�⸦ ���Ѵ�
	JL  L5							; ���� ���� ������ ��� ����
	sub eax, MINHEIGHT				; ���� ���� ���� ������ ũ�ٴ� ���� uphill�� ������ ������ ���� ���� ����Ѵ�
	cmp eax, ANSWER					
	mov edx, CASE[ebx]
	mov MINHEIGHT, edx				; ���� ���� ���ο� ���� ���� MINHEIGHT�� �־��ش�
	JL  L5							; ���� ���� ���̰� ������ �ٽ� L3���� ���ư���.
	mov ANSWER, eax					; �׷��� ������ ANSWER���� �����Ѵ�
L5:	
	Loop L3
	Jmp  L2
L7:
	Loop L1							; L1 JMP���̰� ��� �߰��� L7�� �߰��Ͽ���
	exit
L2:
	mov eax, CASE[ebx]				; ���� ������ ���Ҵ� ���� ������ش�
	sub eax, MINHEIGHT				; ���� ���� ���� ������ ũ�ٴ� ���� uphill�� ������ ������ ���� ���� ����Ѵ�
	cmp eax, ANSWER					;
	JL  L6							; ���� ���� ���̰� ������ eax���� �״�� ����Ѵ�
	mov ANSWER, eax					; �׷��� ������ ANSWER���� eax�� �־��ش�
L6:
	mov eax, ANSWER
	call WriteDec
	call Crlf
	pop ecx
	add ebx, 4
	Jmp L7

main ENDP
END main

