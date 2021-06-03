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
	mov edx, OFFSET commandStr		 ; Enter numbers ���� ���
	call WriteString
	call Crlf
	mov edx, OFFSET inBuffer		 ; edx�� inBuffer OFFSET �̵�
	mov ecx, BUF_SIZE
  	call ReadString					 ; inBuffer�� �Է¹��� ���ڿ� ����
	mov inBufferN, eax				 ; inBufferN�� ���ڿ� ���� ����
	cmp inBufferN, 1				
	JL L2							 ; ���ڿ� ���̰� 1������ ���(= Enter�� �Է� ���� ���) L2�� jump�� �����Ѵ�.
	call convertToInt				 ; �Է¹��� ���ڿ��� ���ڷ� ��ȯ�ϴ� fucntion call �Ѵ�.
	cmp intArrayN, 0				 ; ����� ���ڰ� �ִ��� ������ �Ǵ�
	je  L1							 ; ����� ���ڰ� ���ٸ� L1���� �ٽ� ���ư���
	mov ecx, intArrayN				 ; ����� ������ ������ ecx�� ����
	mov eax, 0						 ; eax�� sum�� �����Ѵ�
	mov esi, OFFSET intArray
L8:
	add eax, [esi]				
	add esi, 4						
	Loop L8
	cmp eax, 0						; ����� sum�� ������� �������� �Ǵ�
	JG  L10							; 0���� ũ�� ����̹Ƿ� L10���� ����.
	call WriteInt					; ������ ��쿡�� WriteInt�� ���
	call Crlf
	jmp L1
L10:	
	call WriteDec					; ����� ��� WriteDec�� ���
	call Crlf
	jmp L1
L2:								     ; Enter�� �Է¹��� ��� Bye!�� ����ϰ� �����Ѵ�.
	mov edx, OFFSET byeStr
	call WriteString
	exit
main ENDP

convertToInt PROC
;
; Convert input char to integers
; ---------------------------------------------------------------------------------
	mov   ebx, 0					; �ε���
	mov   eax, 0					; ���� ��ġ
	mov   intArrayN, ebx			; ���� list ���� 0���� �ʱ�ȭ
	mov   esi, OFFSET intArray		; ���� �迭 OFFSET�� esi�� ����
L3:
	cmp   ebx, inBufferN			; �迭�� ���� �����ߴ��� �ƴ��� �Ǵ����ش�.
	JAE   L5
	mov   cl, inBuffer[ebx]
	cmp   cl, " "					; ��ĭ���� �ƴ��� Ȯ��
	JE    L4						; ��ĭ�̸� L4�� ����
	inc   ebx
	jmp   L3
	
L4:		
	cmp   ebx, eax	     		    ; ebx, eax�� ������ ��ĭ�� ����. 
	JNE   L6						; ebx, eax�� ���� ������ ������ �ִٴ� ��������� ó���ϱ� ���� L6���� ����.
L7:
	inc   ebx						; ebx���� ���� ��Ų��. (�ε��� ����)
	mov   eax, ebx					; ���� �����ϴ� ���ڿ��� ���� ��ġ�� ������Ʈ �Ѵ�.
	jmp   L3
L5:
	cmp   ebx, eax
	JNE   L6
L9:
	ret
L6:									  ; ��Ʈ���� ���ڷ� ��ȯ�Ѵ�
	mov   edx, OFFSET inBuffer   	  ; ������ġ�� edx�� �ű��
	add   edx, eax
	mov   ecx, ebx
	sub   ecx, eax					  ; ecx�� �̵��� byte������ �־��ش�
	call  ParseInteger32			  ; eax�� int�� ��ȯ�� ���� ����ȴ�
	mov   [esi], eax
	add   esi, 4
	inc   intArrayN					  ; ���� ���� ����
	inc   ebx
	mov   eax, ebx
	
	cmp   ebx, inBufferN			  ; ���ڿ��� ���� ���������� L9�� ���� return �Ѵ�.
	JAE   L9
	jmp   L3
convertToInt ENDP
END main


