TITLE Caesar Cipher		       (s151610HW03.asm)

; Program Description: This program decipher ciphert texts to origin texts
; Author: 20151610 Yoohwa Cho
; Creation Date : 2021. 05. 09

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW03.inc  ; Includes Number of Cipher text and Cipher texts

.data
filename BYTE "0s151610_out.txt"	; name of output file
filehandle HANDLE ?
bytesWritten DWORD ?
L BYTE "QRSTUVWXYZABCDEFGHIJKLMNOP" ; contains deciphered alphabet lists
changeLine BYTE 0Dh, 0Ah

.code
main PROC
	mov edx, OFFSET filename		; contains the offset of a filenmae
	call CreateOutputFile
	mov filehandle, eax				; eax contains a valid file handle, save to filehandle
	
	mov ecx, Num_Str				
	mov esi, 0						; Index of alphabet in text
L1:									; LOOP 1 start : 변형해야할 텍스트 개수만큼 돈다
	push ecx
	mov ecx, 10
L2:									; LOOP 2 start : 텍스트 1개에 대해서 convert 한 후 줄바꿈 문자를 넣어준다.
	mov	al, Cipher_Str[esi]
	movzx ebx, al
	sub ebx, 'A'					; convert할 알파벳의 인덱스를 'A'를 빼서 구해준다.
	mov al, L[ebx]
	mov Cipher_Str[esi], al			; 원본 text의 내용을 변형된 text로 바꿔준다.
	inc esi
	loop L2

	mov al, changeLine				
	mov Cipher_Str[esi], al			; 텍스트 1개 뒤에 줄바꿈 문자를 넣어준다
	inc esi
	pop ecx
	loop L1
	
	mov eax, filehandle				; open file handle
	mov edx, OFFSET Cipher_Str		; offset of Data to write
	mov ecx, esi					; number of bytes to write
	call WriteToFile
	mov bytesWritten, eax			; eax contains the number of bytes written
	
	mov eax, filehandle
	call CloseFile					; closes a dis file that was previously opened

	exit
main ENDP
END main