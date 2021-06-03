TITLE List Sum					       (s151610HW05.asm)

; Program Description: This program convert string input into int numbers and caculate sum of lists.
; Author: 20151610 Yoohwa Cho
; Creation Date : 2021. 05. 28

INCLUDE Irvine32.inc

.data
BUF_SIZE    EQU     256
inBuffer    BYTE    BUF_SIZE DUP(?)			; input string buffer (EOS is 0)
inBufferN   DWORD   ?						; string size(excluding EOS)
intArray    SDWORD  BUF_SIZE/2 DUP(?)		; integer array
intArrayN   DWORD   ?						; number of integers stroed in intArray
commandStr	BYTE    "Enter numbers(<ent> to exit) : ", 0
byeStr		BYTE	"Bye!", 0

.code
main PROC
; Main program control procedure.
; Calls : convertToInt
L1:		
	mov edx, OFFSET commandStr		 ; Enter numbers 문장 출력
	call WriteString
	call Crlf
	mov edx, OFFSET inBuffer		 ; edx에 inBuffer OFFSET 이동
	mov ecx, BUF_SIZE
  	call ReadString					 ; inBuffer에 입력받은 문자열 저장
	mov inBufferN, eax				 ; inBufferN에 문자열 길이 저장
	cmp inBufferN, 1				
	JL L2							 ; 문자열 길이가 1이하인 경우(= Enter만 입력 받은 경우) L2로 jump후 종료한다.
	call convertToInt				 ; 입력받은 문자열을 숫자로 변환하는 fucntion call 한다.
	cmp intArrayN, 0				 ; 저장된 숫자가 있는지 없는지 판단
	je  L1							 ; 저장된 숫자가 없다면 L1으로 다시 돌아간다
	mov ecx, intArrayN				 ; 저장된 숫자의 개수를 ecx에 저장
	mov eax, 0						 ; eax에 sum을 저장한다
	mov esi, OFFSET intArray
L8:
	add eax, [esi]				
	add esi, 4						
	Loop L8
	cmp eax, 0						; 계산한 sum이 양수인지 음수인지 판단
	JG  L10							; 0보다 크면 양수이므로 L10으로 간다.
	call WriteInt					; 음수인 경우에는 WriteInt로 출력
	call Crlf
	jmp L1
L10:	
	call WriteDec					; 양수인 경우 WriteDec로 출력
	call Crlf
	jmp L1
L2:								     ; Enter만 입력받은 경우 Bye!를 출력하고 종료한다.
	mov edx, OFFSET byeStr
	call WriteString
	exit
main ENDP

convertToInt PROC
;
; Convert input char to integers
; ---------------------------------------------------------------------------------
	mov   ebx, 0					; 인덱스
	mov   eax, 0					; 시작 위치
	mov   intArrayN, ebx			; 숫자 list 개수 0으로 초기화
	mov   esi, OFFSET intArray		; 숫자 배열 OFFSET값 esi에 저장
L3:
	cmp   ebx, inBufferN			; 배열의 끝에 도달했는지 아닌지 판단해준다.
	JAE   L5
	mov   cl, inBuffer[ebx]
	cmp   cl, " "					; 빈칸인지 아닌지 확인
	JE    L4						; 빈칸이면 L4로 점프
	inc   ebx
	jmp   L3
	
L4:		
	cmp   ebx, eax	     		    ; ebx, eax가 같으면 빈칸의 연속. 
	JNE   L6						; ebx, eax가 같지 않으면 정수가 있다는 얘기임으로 처리하기 위해 L6으로 간다.
L7:
	inc   ebx						; ebx값을 증가 시킨다. (인덱스 증가)
	mov   eax, ebx					; 새로 시작하는 문자열의 시작 위치를 업데이트 한다.
	jmp   L3
L5:
	cmp   ebx, eax
	JNE   L6
L9:
	ret
L6:									  ; 스트링을 숫자로 변환한다
	mov   edx, OFFSET inBuffer   	  ; 시작위치를 edx에 옮긴다
	add   edx, eax
	mov   ecx, ebx
	sub   ecx, eax					  ; ecx에 이동할 byte개수를 넣어준다
	call  ParseInteger32			  ; eax에 int로 변환된 값이 저장된다
	mov   [esi], eax
	add   esi, 4
	inc   intArrayN					  ; 원소 개수 증가
	inc   ebx
	mov   eax, ebx
	
	cmp   ebx, inBufferN			  ; 문자열의 끝에 도달했으면 L9로 가서 return 한다.
	JAE   L9
	jmp   L3
convertToInt ENDP
END main


