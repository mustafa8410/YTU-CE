CODESG SEGMENT PARA 'CODE'
    ORG 100H
    ASSUME CS:CODESG, SS: CODESG, DS: CODESG, ES: CODESG
BILGI: JMP BASLA
primeOddSum DB 15 DUP(0)
nonPrimeOrEvenSum DB 15 DUP(0)
posIndex DB 0 ; which index of the primeOddSum array is going to be filled
npoesIndex DB 0 ; which index of the nonPrimeOrEvenSum array is going to be filled
TARGET DW 0 ; square of the hypothenuse
FLAG DB 0 ; flag for perfect square or prime

BASLA PROC NEAR

    MOV CH, 1

    OUTER_LOOP: ; controlled by CH
        MOV CL, 1
        INNER_LOOP: ; controlled by CL

            MOV AL, CH
            MUL AL
            MOV BX, AX
            MOV AL, CL
            MUL AL
            ADD AX, BX ; AX = squared value of the hypothenuse
            CMP AX, 2500 ; 50^2 = 2500
            JA INNER_LOOP_END ; if squared value is greater than 2500, pass to the next iteration
            CMP AX, 2
            JB INNER_LOOP_END ; if squared value is less than 2, pass to the next iteration
            MOV TARGET, AX ; save the squared value of the hypothenuse
            CALL SQUARE_ROOT ; Hypothenuse is going to be assigned to BL
            CMP FLAG, 0 ; check if the squared value is a perfect square
            JE INNER_LOOP_END ; if it is not a perfect square, pass to the next iteration
            MOV TARGET, BX ; save the value of hypothenuse
            MOV AL, CL
            ADD AL, CH
            TEST AL, 1
            JZ ADD_NPOES ; if a + b is even, add that value to the nonPrimeOrEvenSum array

            ; if a + b is odd, we'll need to check if c is prime
            XOR AX, AX
            CALL CHECK_PRIME
            CMP FLAG, 0
            JE ADD_NPOES ; if c is not a prime number, add that value to the nonPrimeOrEvenSum array

            ; if c is a prime number, add that value to the primeOddSum array
            LEA BX, primeOddSum
            MOV AX, TARGET ; AX = TARGET, but TARGET can't be more than 50 at this point so AL = TARGET
            MOV AH, posIndex
            CALL ARRAY_ADD
            MOV posIndex, AH
            JMP INNER_LOOP_END
            

            ADD_NPOES:
                LEA BX, nonPrimeOrEvenSum
                MOV AX, TARGET
                MOV AH, npoesIndex
                CALL ARRAY_ADD
                MOV npoesIndex, AH
                JMP INNER_LOOP_END


            INNER_LOOP_END:
                INC CL
                CMP CL, 50
                JBE INNER_LOOP
        OUTER_LOOP_END:
            INC CH
            CMP CH, 50
            JBE OUTER_LOOP 

                        RET
BASLA ENDP

SQUARE_ROOT PROC NEAR
    MOV BL, 2 ; low point of the range
    MOV BH, 50 ; high point of the range
    MOV FLAG, 0 ; clear the flag
    SEARCH:
        CMP BL, BH
        JG NON_PERFECT
        XOR AX, AX ; clear AX
        MOV AL, BH
        SUB AL, BL
        SHR AL, 1 ; divide the range by 2
        ADD AL, BL ; find the middle point
        MOV DL, AL ; DL = mid_tmp
        MUL AL ; AX = mid_squared
        CMP AX, TARGET ; compare AX to the target
        JE PERFECT_SQUARE ; if AX equals to the target, jump to the PERFECT_SQUARE
        JA ABOVE ; if AX is greater than the target, jump to the HIGH
        JB BELOW ; if AX is less than the target, jump to the LOW
    ABOVE:
        MOV BH, DL
        DEC BH
        JMP SEARCH
    BELOW:
        MOV BL, DL
        INC BL
        MOV DH, DL ; DL = mid
        JMP SEARCH
    PERFECT_SQUARE:
        MOV BL, DL ; BL = mid
        XOR AH, AH ; clear AH
        INC BYTE PTR FLAG ; set the flag
        JMP FINISH
    NON_PERFECT:
        MOV BL, DH 
    FINISH:
    XOR BH, BH
    XOR AX, AX ; clear AX
    XOR DX, DX ; clear DX

        RET
SQUARE_ROOT ENDP

ARRAY_ADD PROC NEAR ; BX = array address, AL = value to be added, AH = index
    XOR SI, SI
    PUSH CX
    XOR CX, CX
    MOV CL, AH
    CMP CL, 0
    JE NOT_FOUND
    L1:
        MOV DL, [BX+SI]
        CMP AL, DL
        JE FOUND
        INC SI
        CMP SI, CX
        JB L1
    NOT_FOUND:
        MOV [BX+SI], AL
        INC AH
    FOUND:
        POP CX
            RET

ARRAY_ADD ENDP

CHECK_PRIME PROC NEAR ; TARGET = number to be checked, start from 2 and go until the root of target, if it is divisible by any number, it is not a prime number

    CALL SQUARE_ROOT ; BL will be assigned to the square root of the TARGET
    PUSH CX
    MOV FLAG, 1 ; assume the number is prime
    MOV CL, 2 ; start from 2
    L2:
        MOV AX, TARGET ; AX = TARGET, since target is 8 bits at this point, AL = TARGET actually
        DIV CL ; AL = AX / CL, AH = AX % CL
        CMP AH, 0 ; if the remainder is 0, it is not a prime number
        JE NOT_PRIME
        INC CL
        CMP CL, BL ; if CL is greater than the square root of the TARGET, it is a prime number.
        JBE L2
    JMP PRIME
    NOT_PRIME:
        MOV FLAG, 0
    PRIME:
        POP CX

            RET

CHECK_PRIME ENDP

CODESG ENDS
        END BILGI        