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
	mov ecx, TN						; For문을 돌리기 위해 TN에 있는 testcase값을 ecx에 넣어준다.
	mov ebx, 0
L1: 
	push ecx
	mov ecx, CASE[ebx]				; 리스트 원소의 개수를 ecx에 넣어준다
	mov ANSWER, 0					; 현재 테스트케이스의 Answer값을 0으로 초기화 한다
	cmp ecx, 2						; 원소의 개수가 2개이상인 경우에만 Loop를 수행한다
	JL L6							; 그렇지 않은 경우에는 정답을 출력하는 L2로 바로 이동한다
	dec ecx							; 원소의 개수 - 1 만큼만 L3을 돌기 때문에 ecx-1을 해준다
	add ebx, 4
	mov eax, CASE[ebx]
	mov MINHEIGHT, eax				; 첫번째 고도의 값을 MINHEIGHT에 넣어준다
L3:
	mov eax, CASE[ebx]
	add ebx, 4
	cmp eax, CASE[ebx]				; 1번째 고도의 값부터, 현재 값과 다음 값의 크기를 비교한다
	JL  L5							; 현재 값이 작으면 계속 돈다
	sub eax, MINHEIGHT				; 현재 값이 다음 값보다 크다는 것은 uphill이 끝나기 때문에 고도의 차를 계산한다
	cmp eax, ANSWER					
	mov edx, CASE[ebx]
	mov MINHEIGHT, edx				; 가장 작은 새로운 고도의 값을 MINHEIGHT에 넣어준다
	JL  L5							; 새로 구한 차이가 작으면 다시 L3으로 돌아간다.
	mov ANSWER, eax					; 그렇지 않으면 ANSWER값을 갱신한다
L5:	
	Loop L3
	Jmp  L2
L7:
	Loop L1							; L1 JMP길이가 길어 중간에 L7을 추가하였다
	exit
L2:
	mov eax, CASE[ebx]				; 제일 마지막 원소는 따로 계산해준다
	sub eax, MINHEIGHT				; 현재 값이 다음 값보다 크다는 것은 uphill이 끝나기 때문에 고도의 차를 계산한다
	cmp eax, ANSWER					;
	JL  L6							; 새로 구한 차이가 작으면 eax값을 그대로 출력한다
	mov ANSWER, eax					; 그렇지 않으면 ANSWER값을 eax에 넣어준다
L6:
	mov eax, ANSWER
	call WriteDec
	call Crlf
	pop ecx
	add ebx, 4
	Jmp L7

main ENDP
END main

