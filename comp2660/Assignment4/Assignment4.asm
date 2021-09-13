TITLE Assignment 4

; Name: Dennis Dao
; Date: February 22, 2021
; ID: 110010116
; Description: A program to print the first 7 fibonacci terms and a program to analyze the carry flag

COMMENT !
	“I confirm that I will keep the content of this assignment confidential. I confirm that I have not 
	received any unauthorized assistance in preparing for or writing this assignment. I acknowledge 
	that a mark of 0 may be assigned for copied work.” + Dennis Dao + 110010116 
!

INCLUDE Irvine32.inc
INCLUDELIB Irvine32.lib

.data
	; Fibonacci data
	fib1 DWORD 0
	fib2 DWORD 1

	; Carry flag data
	max DWORD 4294967295

.code
main PROC
	; Fibonacci program
	mov  ecx, 8               ; run the x times, where x is the value in the ecx register

	top: mov  eax, fib1
         call  WriteInt       ; added to avoid confusion with hexadecimal numbers in the registers
         call  DumpRegs
		 jecxz  next
         add  eax, fib2
         mov  ebx, eax        ; Rest of the loop is equivalent to fib1 = fib2, fib2 = fib3
         mov  eax, fib2
         mov  fib1, eax
         mov  fib2, ebx
         loop  top
	next:
	call  Crlf                ; separate the two programs

	; Carry flag program
	mov  eax, max             ; max possible value for eax register
	call  DumpRegs  
	add  eax, 1
	call  DumpRegs            ; value was out of range (too large for the register), so the carry flag is set and register sets a value of 0
	add  eax, 1
	call  DumpRegs            ; value becomes 1 with no overflow so the carry flag isn't set
	sub  eax, 1
	call  DumpRegs            ; value becomes 0 with no overflow so the carry flag isn't set
	sub  eax, 1
	call  DumpRegs            ; min value of eax is 0, new value will be out of range (too small for the register) so the carry flag is set and sets a value of FFFFFFFFh

	exit

main ENDP
END main