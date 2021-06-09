TITLE Q2	   (s151610Q2.asm)

; Author: 20151610 Yoohwa Cho
; Creation Date : 2021. 06. 08

INCLUDE Irvine32.inc
INCLUDE macros.inc

.data
BUF_SIZE    EQU     256
inBuffer    BYTE    BUF_SIZE DUP(?)			; input string buffer (EOS is 0)
inBufferN   DWORD   ?						; string size(excluding EOS)
spaceN		DWORD   ?
printN		DWORD   ?

.code
main PROC
L1:		
	mWrite <"Enter a string : ">
	mov edx, OFFSET inBuffer		 ; edx에 inBuffer OFFSET 이동
	mov ecx, BUF_SIZE
  	call ReadString					 ; inBuffer에 입력받은 문자열 저장
	mov inBufferN, eax				 ; inBufferN에 문자열 길이 저장
	cmp inBufferN, 1				
	JL L2							 ; 문자열 길이가 1이하인 경우(= Enter만 입력 받은 경우) L2로 jump후 종료한다.
	cmp inBufferN, 3				 ; 길이 1,2인 경우
	JL JUSTPRINT
	call PRINTSTRINGS				 ; 입력받은 문자열을 숫자로 변환하는 fucntion call 한다.
	call PRINTDOWN					 ; 모래시계 아래
	call Crlf
	jmp L1
JUSTPRINT:
	mov edx, OFFSET inBuffer
	call WriteString
	call Crlf
	call Crlf
	jmp L1
L2:								     ; Enter만 입력받은 경우 Bye!를 출력하고 종료한다.
	mWrite <"Bye!">
	exit
main ENDP

PRINTSTRINGS PROC
	mov   spaceN, 0
L3:
	mov   ebx, 0
	mov   eax, inBufferN
	sub   eax, spaceN
	sub   eax, spaceN
	mov   printN, eax
	cmp   spaceN, 0
	je    L4						; 빈칸 없으면
	mov   ecx, spaceN				; 빈칸출력
L5: 
	mWrite <" ">
	inc   ebx
	Loop  L5
L4:
	cmp   printN, 0
	je    L7
	mov   ecx, printN
L6:
	mov   al, inBuffer[ebx]
	call  WriteChar
	inc   ebx
	Loop L6
	cmp   spaceN,0
	je    L8
	mov   ecx, spaceN				; 빈칸출력
L7: 
	mWrite <" ">
	inc   ebx
	Loop  L7
L8:
	call  Crlf
	cmp   printN, 2
	jle   L9
	mov   eax, spaceN
	inc   eax
	mov   spaceN, eax
	jmp   L3
L9:
	ret
PRINTSTRINGS ENDP

PRINTDOWN PROC
	mov   eax, spaceN
	dec   eax
	mov   spaceN, eax
L3:
	mov   ebx, 0
	mov   eax, inBufferN
	sub   eax, spaceN
	sub   eax, spaceN
	mov   printN, eax
	cmp   spaceN, 0
	je    L4						; 빈칸 없으면
	mov   ecx, spaceN				; 빈칸출력
L5: 
	mWrite <" ">
	inc   ebx
	Loop  L5
L4:
	cmp   printN, 0
	je    L7
	mov   ecx, printN
L6:
	mov   al, inBuffer[ebx]
	call  WriteChar
	inc   ebx
	Loop L6
	cmp   spaceN,0
	je    L8
	mov   ecx, spaceN				; 빈칸출력
L7: 
	mWrite <" ">
	inc   ebx
	Loop  L7
L8:
	call  Crlf
	cmp   spaceN, 0
	je    L9
	mov   eax, spaceN
	dec   eax
	mov   spaceN, eax
	jmp   L3
L9:
	ret
PRINTDOWN ENDP

END main


