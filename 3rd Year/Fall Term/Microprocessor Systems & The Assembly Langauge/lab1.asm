STSG SEGMENT PARA STACK 'STSGM'
	DW 20 DUP (?)
STSG ENDS

DTSG SEGMENT PARA 'DTSGM'
	N DB 4
    VIZE DB 77, 85, 64, 96
    FINAL DB 56, 63, 86, 74
    OBP DB 4 DUP (0)
    DIVIDE DW 10
    REM DB 0
DTSG ENDS

CDSG SEGMENT PARA 'CDSGM'
	ASSUME CS: CDSG, DS: DTSG, SS: STSG
	
	ANA PROC FAR

		PUSH DS
		XOR AX, AX
		PUSH AX

		MOV AX, DTSG
		MOV DS, AX
		
		;CODE	
        XOR SI, SI
        XOR CX, CX
        MOV CL, N

        L1:

        XOR DX, DX
        LEA BX, VIZE
        MOV AL, 4
        MUL BYTE PTR [BX + SI] ; AX = 4 * VIZE[SI]
        DIV WORD PTR DIVIDE ; AX = DX:AX / 10, DX = DX:AX % 10, and DX is 0
        MOV REM, DL ; mod can't be greater then 9 so we use DL
        
        LEA BX, OBP
        MOV BYTE PTR [BX + SI], AL ; obp[SI] = AL, since AX can't be 255, AH is always 0 so we can move AL
        MOV AL, 6

        LEA BX, FINAL
        MUL BYTE PTR [BX + SI] ; AX = 6 * FINAL[SI]
        XOR DX, DX
        DIV WORD PTR DIVIDE
        ADD REM, DL
        
        LEA BX, OBP
        ADD BYTE PTR [BX + SI], AL ; obp[SI] += AL   
        MOV AL, REM
        DIV BYTE PTR DIVIDE ; AL = AL / 10, AH = AL % 10
        ADD [BX + SI], AL
        CMP AH, 5
        JL LESS ; if AH < 5, jump to LESS
        INC BYTE PTR [BX + SI] ; obp[SI]++
        LESS:
        INC SI
        MOV BYTE PTR REM, 0
        LOOP L1 

        ; implementing bubble sort in descending order
        MOV CL, N
        ; since BX is already addressed to OBP, no need to use LEA again
        BUBBLE_LOOP:

        XOR SI, SI
        MOV DX, CX ; dx will be used for the inner loop

        INNER_BUBBLE:

        MOV AL, [BX + SI]
        CMP AL, [BX + SI + 1] ; compare the current element with the next element
        JG DONT_SWAP ; don't swap if the current element is greater than the next element
        XCHG AL, [BX + SI + 1] 
        MOV [BX + SI], AL

        DONT_SWAP:

        INC SI
        DEC DX
        JNZ INNER_BUBBLE
        LOOP BUBBLE_LOOP

		RETF
	ANA ENDP


CDSG ENDS

	END ANA