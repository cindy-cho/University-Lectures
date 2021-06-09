TITLE Redirection					       (s151610HW06.asm)

; Program Description: This program read from input text file and returns output string
; Author: 20151610 Yoohwa Cho
; Creation Date : 2021. 06. 06
; Input Types  : (1)  
;                (2) < [input.txt]
;				 (3) < [input.txt] > [output.txt]
; Output Types : (1) stdin으로 입력 받고 stdout으로 출력
;				 (2) input file을 읽은 후 stdout 으로 출력
;				 (3) input file을 읽은 후 output file 로 출력

INCLUDE Irvine32.inc
INCLUDE macros.inc

Read_a_Line PROTO						;

CreateFile PROTO,						;;create new file
	lpFIlename:PTR BYTE,
	dwDesiredAccess:DWORD,
	dwShareMode:DWORD,
	lpSecurityAttributes:DWORD,
	dwCreationDisposition:DWORD,
	dwFlagsAndAttributes:DWORD,
	hTemplateFile:DWORD

WriteFile PROTO,						;; 쓰기 함수 (이 함수는 EAX, EBX, ECX, EDX 를 보전하지 않는다.)
	fileHandle:DWORD,					; 출력 handle(stdoutHandle)
	pBuffer:PTR BYTE,					; 출력 버퍼 offest
	nBufsize:DWORD,						; 쓰고자 하는 최대 byte 수
	pBytesWritten:PTR DWORD,			; 실제로 쓰인 개수 저장을 위한 변수 offset
	pOverlapped:PTR DWORD				; 무시(0을 전달)

CloseHandle PROTO,
	hObject:HANDLE						; handle to object

.data
stdinHandle  HANDLE  ?
stdoutHandle HANDLE  ?
BUF_SIZE     EQU     256
inBuffer     BYTE    BUF_SIZE DUP(?)			; input string buffer (stdin)
inBufferN    DWORD   ?		     				; string size(excluding EOS)
inBuf        BYTE    BUF_SIZE DUP(0)			; input filename buf
bytesREAD    DWORD   ?
outBuf       BYTE    BUF_SIZE DUP(0)            ; output filename buf
bytesWRITE   DWORD   ?
contentBuf	 BYTE    BUF_SIZE DUP(?)			; read_line buf
convertedBuf BYTE    BUF_SIZE DUP(?)            ; converted_line buf
writtenSize  DWORD   ?

.code
main PROC
	mov    bytesWRITE, 0						; output file 기본 세팅
	mov    edx, OFFSET inBuffer	             	; edx에 inBuffer OFFSET 이동
	mov    ecx, BUF_SIZE
  	call   ReadString					        ; inBuffer에 입력받은 문자열 저장	
	mov    inBufferN, eax				        ; inBufferN에 문자열 길이 저장
	cmp    eax, 0								; 입력이 들어온지 여부를 확인한다
	je	   OpenInputFilewithName				; 사이즈가 0 이면 바로 입력 받는 부분으로 이동한다
	mov    ebx, 0							    ; inBuffer 문자열을 parsing 해서 input, output 파일 이름 확인
	
ParsingCommand:
	mov    al, inBuffer[ebx]					; 한 문자씩 al에 옮겨준다
	inc    ebx
	cmp    al, "<"								; input파일이 있는지 여부를 "<"로 확인한다
	je     ParseInputFileName					; <가 나온다면 input file 이름 parse하는 부분으로 간다
	cmp    al, ">"
	je     ParseOutputFileName					; >가 나온다면 output file 이름 parse하는 부분으로 간다
	cmp    ebx, inBufferN						; 문자열의 끝인지 아닌지 확인한다
	je     OpenInputFilewithName				; 문자열의 끝이면 파일 입력 받는 부분으로 이동한다
	Loop   ParsingCommand

ParseInputFileName:								; INPUT FILE 이름 PARSING 하는 부분
	mov    edx, 0
L1:
	cmp    ebx, inBufferN				        ; 문자열의 끝인지 아닌지 확인한다
	je     OpenInputFilewithName				; 문자열의 끝이면 파일 입력 받는 부분으로 이동한다
	mov    al, inBuffer[ebx]
	inc    ebx
	cmp    al, ">"								; output파일 이름이 있는지 확인한다
	je     ParseOutputFileName					; > 가 있다면 output file 이름 parsing 하는 부분으로 간다
	cmp    al, " "								; 파일 이름에 빈칸이 들어있지 않다는 가정하에, 빈칸인 경우는 무시한다
	je     L1					                ; 빈칸이면 다시 L1으로 돌아간다
	mov    inBuf[edx], al						; input파일 이름 버퍼에 옮겨준다
	inc    edx
	mov    bytesREAD, edx						; Input File 이름 글자 개수 bytesREAD저장
	Loop   L1

ParseOutputFileName:							; OUTPUT FILE 이름 PARSING 하는 부분
	mov    edx, 0
L2:
	cmp    ebx, inBufferN				        ; 문자열의 끝인지 아닌지 확인한다
	je     OpenInputFilewithName				; 문자열의 끝이면 파일 입력 받는 부분으로 이동한다
	mov    al, inBuffer[ebx]
	inc    ebx
	cmp    al, " "								; 파일 이름에 빈칸이 들어있지 않다는 가정하에, 빈칸인 경우는 무시한다
	je     L2					                ; 빈칸이면 다시 L2으로 돌아간다
	mov    outBuf[edx], al						; output파일 이름 버퍼에 옮겨준다
	mov    bytesWRITE, edx						; output파일 이름 길이 bytesWRITE에 옮겨준다
	inc    edx
	Loop   L2

OpenInputFilewithName:							; INPUT FILE 여는 부분
	INVOKE CreateFile,
		ADDR inbuf, GENERIC_READ, DO_NOT_SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
	mov    stdinHandle, eax
	cmp    eax, INVALID_HANDLE_VALUE			; error opening file?
	jne    OpenOutputFilewithName				; 잘 열렸다면 output file 여는 부분으로 간다
	; 파일을 열지 못했으면 없다는 뜻이므로 std input으로 설정한다
	INVOKE GetStdHandle, STD_INPUT_HANDLE
	mov    stdinHandle, eax

OpenOutputFilewithName:							; OUTPUT FILE 여는 부분
	; open the file for output
	cmp    bytesWRITE, 0							; 아웃풋 파일 이름 길이가 0이면 기본 stdout으로 설정한다
	je     setStdOut
	INVOKE CreateFile,
		ADDR outbuf, GENERIC_WRITE, DO_NOT_SHARE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0
	mov    stdoutHandle, eax
	cmp    eax, INVALID_HANDLE_VALUE			; error opening file?
	jne    Reading								; 문제 없을 경우 스트링 변환을 수행하는 convertString으로 이동한다
	
setStdOut:										; 파일을 열지 못했으면 없다는 뜻이므로 std output으로 설정한다
	INVOKE GetStdHandle, STD_OUTPUT_HANDLE
	mov    stdoutHandle, eax

Reading:
	mov    eax, stdinHandle
	mov    edx, OFFSET contentBuf
	mov    esi, 0
	INVOKE Read_a_Line
	cmp    ecx, 0								; ecx가 0이면 더 이상 입력이 없다는 의미이므로 종료한다
	je     quit
												; 그렇지 않다면 읽어온 내용을 변환하여 출력해준다
	mov    edx, OFFSET contentBuf
	mov    ebx, [edx]
	cmp    bl, " "								; 입력 예시 중 3번 - 빈칸만 들어오는 줄을 처리한다
	je     Reading								; 빈칸이면 줄을 읽어들어오는 reading으로 돌아간다
	sub    bl, "0"								; 문자를 숫자로 바꾸기 위해 - "0"을 해준다
	add    edx, 2								; 문자열 시작 위치로 이동 (숫자, 빈칸 이기 때문에 +2)
	sub    ecx, 2								; 전체 loop을 도는 ecx개수에서 -2만큼 빼준다
	jmp    converting

writeOutput:									; converting에서 변환한 문자열을 출력해주는 부분
	mov    convertedBuf[esi], 0dh				; 제일 마지막에 CRLF 를 붙여준다
	inc    esi
	mov    convertedBuf[esi], 0ah
	inc    esi			
	push   eax			
	mov    eax, stdoutHandle
	INVOKE WriteFile,
		eax, ADDR convertedBuf, esi, ADDR writtenSize, 0
	pop    eax
	Loop   Reading								; 한 줄 출력 후 다시 읽어들이는 Reading부분으로 돌아간다
converting:					
	push   ecx									; ecx = 문자열 길이
	mov    cl, bl								; ecx = K
	push   ebx									; K 값 저장
	mov    ebx, [edx]
copying:										;k만큼 복사한다
	mov    convertedBuf[esi], bl 
	inc    esi
	Loop   copying
	pop    ebx
	pop    ecx
	inc    edx
	Loop   converting
	jmp    writeOutput

quit:
	INVOKE CloseHandle, stdinHandle
	INVOKE CloseHandle, stdoutHandle
	exit
main ENDP

Read_a_Line PROC
;; Input EAX : FILE Handle
;;       EDX : Buffer offset to store the string
;; Output ECX : # of chars read(0 if none(i.e. EOF)
;; Function
;; Read a line from a ~.txt file until CR, LF.
;; CR, LF are ignored and 0 is appended at the end.
;; ECX only counts valid chars just before CR.

.data
Single_Buf__   BYTE  ?
Byte_Read__	   DWORD ?

.code
	xor   ecx,  ecx                 ; reset counter

Read_Loop:
	;; Note : Win 32 API functions do not preserve
	;;        EAX, EBX, ECX and EDX
	push  eax
	push  ecx
	push  edx

	; read a single char
	INVOKE ReadFile, EAX, OFFSET Single_Buf__,
			         1, OFFSET Byte_Read__, 0
	pop   edx                       ; restore registers
	pop   ecx
	pop   eax
	cmp   DWORD PTR Byte_Read__, 0  ; check # of chars read
	je    Read_End                  ; if read nothing, return

	;;Each end of line consists of CR and then LF
	mov   bl, Single_Buf__          ; load the char
	cmp   bl, 0Dh
	je    Read_Loop                 ; if CR, read once more
	cmp   bl, 0Ah
	je    Read_End                  ; End of line detected, return

	mov   [edx], bl                 ; move the char to input buf
	inc   edx                       ; ++1 buf pointer
	inc   ecx                       ; ++1 char counter
	jmp   Read_Loop                 ; go to start to read the next line

Read_End:
	mov   BYTE PTR [edx], 0         ; append 0 at the end
	ret
Read_a_Line ENDP

END main