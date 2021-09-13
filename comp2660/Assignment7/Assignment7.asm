TITLE Assignment 7

; Name: Dennis Dao
; Date: Mar 8, 2021
; ID: 110010116
; Description: A program to perform procedures using the stack and an array of unsigned double words.

COMMENT !
	“I confirm that I will keep the content of this assignment confidential. I confirm that I have not 
	received any unauthorized assistance in preparing for or writing this assignment. I acknowledge 
	that a mark of 0 may be assigned for copied work.” + Dennis Dao + 110010116 
!

INCLUDE Irvine32.inc
INCLUDELIB Irvine32.lib

.data
	; General data, used by most branches
	nonEmptyStack BYTE "Stack is not empty", 0
	emptyStack BYTE "Stack is empty", 0
	arrIs BYTE "Array is ", 0
	stackIs BYTE "Stack is ", 0
	emptyArr BYTE "Error - Array is empty: Cannot perform operation", 0
	emptyStackErr BYTE "Error - Stack is empty: Cannot perform operation",0
	createErr BYTE "Error - An array was already created: Cannot perform operation", 0

	; Main branch data
	options BYTE "0 - Create an array || 1 - Move array to stack || 2 - Move stack to array || 3 - Reverse array || -1 - Exit", 0
	mainPrompt BYTE "What would you like to do? > ", 0
	bye BYTE "Exiting, thank you for doing Assignment 7 :-)", 0
	err BYTE "Invalid entry, please try again!", 0

	; Create branch data
	sizePrompt BYTE "What is the size N of the array? (1-20) > ", 0
	elemPrompt1 BYTE "What are the ", 0
	elemPrompt2 BYTE " elements in the array? > ", 0
	arraySize BYTE "Size of array is N = ", 0
	arrayContent BYTE "Array = ", 0

	; Array to stack branch data
	beforeArrStack BYTE " before ArrayToStack", 0
	afterArrStack BYTE " after ArrayToStack", 0

	; Stack to array branch data
	beforeStackArr BYTE " before StackToArray", 0
	afterStackArr BYTE " after StackToArray", 0

	; Reverse branch data
	beforeReverse BYTE " before StackReverse", 0
	afterReverse BYTE " after StackReverse", 0

	; User-related data
	maxSize = 20
	
	actualSize DWORD 0
	currentSize DWORD 0
	stackSize DWORD 0
	Array DWORD maxSize DUP(0)
	; Temporary storage for stack when going from arrToStack and stackToArr procedure
	temp DWORD maxSize DUP(0)

.code
main PROC
	; Main block
	mainLoop:
	    mov  edx, OFFSET options                                           ; Instruction message
	    call WriteString 
	    call Crlf
	    call Crlf
	    mov  edx, OFFSET mainPrompt                                        ; Prompt user
	    call WriteString
	    call ReadInt
	    call Crlf
	    push  OFFSET Array

		cmp  eax, -1                                                       ; User wants to exit
		je  exitCall     
		cmp  eax, 0                                                        ; User wants to create array
		je  createCall   
		cmp  eax, 1                                                        ; User wants to move array to stack
		je  arrToStackCall
		cmp  eax, 2                                                        ; User wants to move stack to array
		je  stackToArrCall
		cmp  eax, 3                                                        ; User wants to reverse array
		je  reverseCall                                                                                                    

		mov  edx, OFFSET err                                               ; All above checks failed, input was invalid
		pop  ebx
		call WriteString
	    call Crlf
	    call Crlf
		jmp  mainLoop

	createCall:                                                            ; When user want to create an array
	    call  CreateArr
	    jmp  mainLoop

	arrToStackCall:                                                        ; When user wants to push array elements to the stack
	    call ArrayToStack
		jmp  mainLoop

	stackToArrCall:                                                        ; When user wants to push stack elements to the array
	    call StackToArray	
	    jmp  mainLoop

	reverseCall:                                                           ; When user wants to reverse the elements
	    call StackReverse	
	    jmp  mainLoop

	exitCall:                                                              ; When user wants to exit
	    mov  edx, OFFSET bye
		pop  ebx
		call  WriteString
		call  Crlf
		call  DumpRegs
	    exit
main ENDP

;----------------------------------------------------------
CreateArr PROC
; Receives: The offset of the array, and size and input provided by the user
; Returns: An initialized array of doublewords
; Requires: No array size has been set
;----------------------------------------------------------
    input:
	    mov  eax, actualSize
	    cmp  eax, 0
		jne  arrSizeSet                                                   ; Make sure array size hasn't been already set

	    mov  edx, OFFSET sizePrompt
	    call  WriteString
	    call  ReadInt

		cmp  eax, 0                                                       ; Check for invalid entries (too small, too large)
		jle  invalidInput
		cmp  eax, maxSize
		jg  invalidInput

		mov  ecx, eax                                                     ; Set up loop to get numbers
		mov  actualSize, eax
		push  ebp
		mov  ebp, esp
	    mov  esi, [ebp+8]
		mov  edx, OFFSET elemPrompt1
		call WriteString
		call WriteDec
		mov  edx, OFFSET elemPrompt2
		call WriteString

		L1:                                                               ; Get the numbers
			call  ReadInt
			mov  [esi], eax
			add  esi, TYPE DWORD
			inc  currentSize
		    loop L1

		mov  eax, actualSize                                              ; Display properties of the array and stack ("status update")
	    mov  ecx, actualSize
		mov  edx, OFFSET arraySize
		call  Crlf
		call  WriteString
		call  WriteDec
		call  Crlf
		mov  edx, OFFSET arrayContent
		call  WriteString
		 
	    push  [ebp+8]
		call  PrintElements

		call  Crlf
		mov  edx, OFFSET emptyStack
		call  WriteString
		call  Crlf
		call  Crlf
		pop  ebp
	    ret  4

	invalidInput:                                                         ; Output error message, then let user try again
	    mov  edx, OFFSET err
		call  WriteString
		call  Crlf
		call  Crlf
		jmp  input

	arrSizeSet:                                                           ; Output error message, then leave procedure
	    mov  edx, OFFSET createErr
		call  WriteString
		call  Crlf
		call  Crlf
		ret  4
createArr ENDP

;----------------------------------------------------------
ArrayToStack PROC
; Copies N elements of an array to the runtime stack
; Receives: Offset of the Array
; Returns: An array of doublewords with values 0
; Requires: The array must have at least one element
;----------------------------------------------------------
	mov  eax, currentSize                                                  ; Check for at least one element in the array
	cmp  eax, 0
	je  empty

	push  ebp
	mov  ebp, esp
	mov  ecx, actualSize
	mov  edx, OFFSET arrIs                                                 ; Output contents of array
	call  WriteString
	push  [ebp+8]
	call  PrintElements
	mov  ecx, actualSize
	mov  edx, OFFSET beforeArrStack
	call  WriteString
	call  Crlf

	mov  esi, [ebp+8]
	L1:                                                                   ; Move elements to the stack and replace array elements with zeros
	    push  [esi]
		mov  eax, 0
		mov  [esi], eax
		add  esi, TYPE DWORD
		inc  stackSize
		dec  currentSize
		loop L1

	mov  ecx, actualSize                                             
	mov  edx, OFFSET stackIs                                             
	mov  esi, OFFSET temp
	call  WriteString

    L2:                                                                   ; Output stack contents and place into temp array for next procedure
	    mov  eax, [esp]
		mov  [esi], eax
		call  WriteDec
		mov  eax, 32
		call  WriteChar
		add  esi, TYPE DWORD
		add  esp, 4
		loop L2

	mov  ecx, actualSize                        
	mov  edx, OFFSET afterArrStack                                       ; Output messages
	call WriteString
	call  Crlf
	mov  edx, OFFSET arrIs
	call  WriteString
	push  [ebp+8]
	call  PrintElements
	mov  edx, OFFSET afterArrStack                                       
	call  WriteString
	call  Crlf
	mov  edx, OFFSET nonEmptyStack
	call  WriteString
	call  Crlf
	call  Crlf
	pop  ebp
	ret  4

	empty:                                                               ; Handle error message for empty array and leave the procedure
	    mov  edx, OFFSET emptyArr
		call WriteString
		call Crlf
		call Crlf
		ret  4
ArrayToStack ENDP

;----------------------------------------------------------
StackToArray PROC
; Copies the last N double words pushed onto the stack to an array (popping the stack)
; Receives: A stack of doublewords and an empty array
; Returns: An array of doublewords popped from the stack
; Requires: The stack must have at least one element
;----------------------------------------------------------
    mov  eax, stackSize                                                    ; Check for at least one element in the stack
	cmp  eax, 0
	je  empty

	push  ebp
	mov  ebp, esp
	mov  ecx, actualSize
	mov  esi, OFFSET temp
	mov  edx, OFFSET stackIs
	call  WriteString
	L1:                                                                    ; Output the saved contents from the previous function to the stack
	    sub  esp, 4
	    mov  eax, [esi]
		mov  [esp], eax
	    call  WriteDec
	    mov  eax, 32
	    call  WriteChar
		add  esi, TYPE DWORD
		loop  L1

	mov  esi, [ebp+8]
	mov  edx, OFFSET beforeStackArr
	call  WriteString
	call  Crlf

	mov  ecx, actualSize
	L2:                                                                   ; Move elements to the array       
		pop  eax
		mov  [esi], eax
	    add  esi, TYPE DWORD
		inc  currentSize
		dec  stackSize
        loop  L2

	mov  ecx, actualSize
	mov  edx, OFFSET arrIs                                               ; Output messages
	call  WriteString
	push  [ebp+8]
	call  PrintElements	
	mov  edx, OFFSET afterStackArr
	call  WriteString
	call  Crlf
	mov  edx, OFFSET emptyStack
	call  WriteString
	call  Crlf
	call  Crlf
	pop  ebp
	ret  4

	empty:                                                               ; Handle an error message, then leave the procedure
	    mov  edx, OFFSET emptyStackErr
		call  WriteString
		call  Crlf
		call  Crlf
		ret  0
StackToArray ENDP

;----------------------------------------------------------
StackReverse PROC
; Reverses an array of N double word integers using the runtime stack
; Receives: An array of doublewords
; Returns: An array of doublewords, reversed
; Requires: The array must have at least one element
;----------------------------------------------------------
	mov  eax, currentSize                                                  ; Make sure the array isn't empty
	cmp  eax, 0
	je  emptyArray

    push  ebp
	mov  ecx, actualSize
	mov  ebp, esp
	mov  edx, OFFSET arrIs                                                ; Output messages
	call  WriteString
	push  [ebp+8]
	call  PrintElements
	mov  edx, OFFSET beforeReverse
	call  WriteString
	call  Crlf
	
	mov  ecx, actualSize                                                  ; Set up loop paramters
	mov  esi, OFFSET Array

	L1: 
	    push [esi]                                                        ; Push the elements of the array
	    add  esi, TYPE DWORD
		loop  L1

	mov  edx, OFFSET nonEmptyStack
	call  WriteString
	call  Crlf
	mov  ecx, actualSize                                                  ; Restart the loop to reverse the array
	mov  esi, [ebp+8]                                                     ; Set the index back to start

	L2: 
	    pop  eax                                                          ; Pop the elements, putting them in reverse order
	    mov  [esi], eax
		add  esi, TYPE DWORD
		loop  L2

	mov  edx, OFFSET arrIs                                                ; Output messages
	call  WriteString
	push  [ebp+8]
	mov  ecx, actualSize
	call  PrintElements	
	mov  edx, OFFSET afterReverse
	call  WriteString
	call  Crlf
	mov  edx, OFFSET emptyStack
	call  WriteString
	call  Crlf
	call  Crlf
	pop  ebp
	ret  4

	emptyArray:                                                          ; Handle error message, then leave the procedure
	    mov  edx, OFFSET emptyArr
		call WriteString
		call Crlf
		call Crlf
		ret  0
StackReverse ENDP

;----------------------------------------------------------
PrintElements PROC
; Helper procedure to print doubleword array elements
; Receives: The array offset
; Returns: The elements as part of the output message
;----------------------------------------------------------
	push  ebp
	mov  ebp, esp
	mov  esi, [ebp+8]
    L1:                                                                   ; Print the inputted elements          
	    mov  eax, [esi]
	    call WriteDec
	    mov  eax, 32                                                      ; Add space between each
	    call WriteChar
	    add  esi, TYPE DWORD
        loop  L1 
	pop  ebp
	ret  4
PrintElements ENDP
END main