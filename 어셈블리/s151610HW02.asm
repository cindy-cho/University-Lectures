TITLE Polynomial Caculation		       (s20151610HW02.asm)

; Program Description: This program caculate polynomial F = 90x1 - 30x2 + 19x3
; Author: 20151610 Yoohwa Cho
; Creation Date : 2021. 04. 14

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW02.inc  ; Includes data x1, x2, x3

.code
main PROC
	mov   eax,  x1        ; eax <= x1
	add   eax,  x1        ; eax = x1+x1 = 2*x1
	add   eax,  x1        ; eax = 2*x1 + x1 = 3*x1
	sub   eax,  x2        ; eax = 3*x1 - x2
	add   eax,  x3        ; eax = 3*x1 - x2  + x3
	add   eax, eax        ; eax = 6*x1 - 2*x2 + 2*x3
	mov   x1,  eax        ; x1 <= eax = 6*x1 - 2*x2 + 2*x3
	add   eax, eax        ; eax = 12*x1 - 4*x2 + 4*x3
	add   eax, eax        ; eax = 24*x1 - 8*x2 + 8*x3
	add   eax, eax        ; eax = 48*x1 - 16*x2 + 16*x3
	add   eax, eax        ; eax = 96*x1 - 32*x2 + 32*x3
	sub   eax, x1         ; eax = eax - x1 = (96*x1 - 32*x2 + 32*x3) - (6*x1 -2*x2 + 2*X3)= 90*x1 - 30*x2 + 30x3
	mov   x1,  eax        ; x1 <= 90*x1 - 30*x2 + 30x3
	mov   eax, x3         ; eax <= x3
	add   eax, eax        ; eax = 2*x3
	add   eax, eax        ; eax = 4*x3
	mov   x2,  eax        ; x2 <= eax = 4*x3
	add   eax, eax        ; eax = 8*x3
	add   eax, x2         ; eax = 8*x3 + 4*x3 = 12*x3
	sub   eax, x3         ; eax = 12*x3 - x3 = 11*x3
	mov   x3,  eax        ; x3 <= eax = 11*x3
	mov   eax, x1         ; eax <= 90*x1 - 30*x2 + 30x3
	sub   eax, x3         ; eax = 90*x1 - 30*x2 + 30x3 - 11*x3 = 90*x1 - 30*x2 + 19x3
	call  WriteInt

	exit
main ENDP
END main