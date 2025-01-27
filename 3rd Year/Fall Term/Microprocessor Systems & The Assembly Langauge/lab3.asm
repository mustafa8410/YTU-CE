SSEG SEGMENT PARA STACK 'STACK'
    DW 32 DUP (?)
SSEG ENDS

DATASG SEGMENT PARA 'DATA'
    CR	EQU 13
    LF	EQU 10
    MOD_VALUE DB 0
    N DB 0
    SAYILAR DB 10 DUP (0)
    MSG1 DB 'N degeri: ',0
    MSG2 DB CR, LF, 'Sayi giriniz: ',0
    HATA DB CR, LF, 'Hatali giris, tekrar deneyin: ',0
    MSG3 DB CR, LF, 'Mod: ',0
DATASG ENDS

CSEG SEGMENT PARA 'CODE'
    ASSUME CS:CSEG, DS:DATASG, SS:SSEG

    GIRIS_DIZI MACRO MSG1, MSG2, HATA, SAYILAR, N
    LOCAL GET_LENGTH, L1
        PUSH AX
        PUSH BX
        PUSH CX
        PUSH DX
        PUSH SI

        GET_LENGTH:
            MOV AX, OFFSET MSG1
            CALL PUT_STR
            CALL GETN
            CMP AX, 10
            JA GET_LENGTH
            CMP AX, 0
            JE GET_LENGTH
            MOV BYTE PTR N, AL ; save the length of the array, since length can't be greater than 10, we can use AL
        MOV CX, AX ; save the length of the array to CX register for looping
        XOR SI, SI
        LEA SI, SAYILAR
        L1:
            MOV AX, OFFSET MSG2
            CALL PUT_STR
            CALL GETN
            MOV BYTE PTR [SI], AL
            INC SI
        LOOP L1

        POP SI
        POP DX
        POP CX
        POP BX
        POP AX
    ENDM

    MAIN PROC FAR

        PUSH DS
        XOR AX,AX
        PUSH AX

        MOV AX, DATASG
        MOV DS, AX

        GIRIS_DIZI MSG1, MSG2, HATA, SAYILAR, N

        LEA BX, SAYILAR
        XOR CX, CX
        MOV CL, N
        CALL BUBBLESORT
        XOR AX, AX
        PUSH AX
        LEA SI, SAYILAR
        CALL MY_MOD
        POP AX
        MOV BYTE PTR MOD_VALUE, AL
        MOV AX, OFFSET MSG3
        CALL PUT_STR
        XOR AX, AX
        MOV AL, MOD_VALUE
        CALL PUTN
        
        
        RETF

    MAIN ENDP

    BUBBLESORT PROC NEAR ; BX has the array address, CX has the array length
        PUSH AX
        PUSH BX
        PUSH CX
        PUSH DX
        PUSH SI
        DEC CX ; CX = N - 1
        XOR AX, AX
        XOR DX , DX ; DH = i, DL = upper bound for SI
        MOV DL, CL ; DL = N - 1
        BUBBLE_LOOP:
        XOR SI, SI
        
        INNER_BUBBLE:
        

        MOV AL, [BX + SI]
        CMP AL, [BX + SI + 1] ; compare the current element with the next element
        JBE DONT_SWAP ; don't swap if the current element is smaller than the next element
        XCHG AL, [BX + SI + 1] 
        MOV [BX + SI], AL

        DONT_SWAP:

        INC SI
        MOV AL, DL
        CMP SI, AX
        JB INNER_BUBBLE
        INC DH
        DEC DL
        CMP DH, CL
        JB BUBBLE_LOOP

        POP SI
        POP DX
        POP CX
        POP BX
        POP AX


        RET
    BUBBLESORT ENDP

    MY_MOD PROC NEAR
        PUSH BX
        PUSH CX
        PUSH DX
        PUSH SI
        PUSH BP
        MOV BP, SP
        ; AL = mode, AH = current number, BL = previous number, SI = array address, CX = array length, DH = max count, DL = current count
        XOR AX, AX
        MOV DL, 1
        MOV DH, 1
        MOV AL, [SI]
        MOV BL, AL
        DEC CX
        INC SI
        L_MOD:
            MOV AH, [SI]
            CMP AH, BL
            JE INCREMENT
            JMP NOT_EQUAL
            INCREMENT:
                INC DL
                JMP CONTINUE
            NOT_EQUAL:
                CMP DL, DH
                JBE NO_NEW_MODE
                MOV DH, DL
                MOV AL, BL
            NO_NEW_MODE:
                MOV DL, 1
            CONTINUE:
                INC SI
                MOV BL, AH
        LOOP L_MOD
        CMP DL, DH
        JBE MOD_END
        MOV AL, BL
        MOD_END:
        XOR AH, AH
        MOV [BP + 12], AX
        POP BP
        POP SI
        POP DX
        POP CX
        POP BX
                    RET
    MY_MOD ENDP

    GETC	PROC NEAR
        ;------------------------------------------------------------------------
        ; Klavyeden basılan karakteri AL yazmacına alır ve ekranda gösterir. 
        ; işlem sonucunda sadece AL etkilenir. 
        ;------------------------------------------------------------------------
        MOV AH, 1h
        INT 21H
        RET 
GETC	ENDP 

PUTC	PROC NEAR
        ;------------------------------------------------------------------------
        ; AL yazmacındaki değeri ekranda gösterir. DL ve AH değişiyor. AX ve DX 
        ; yazmaçlarının değerleri korumak için PUSH/POP yapılır. 
        ;------------------------------------------------------------------------
        PUSH AX
        PUSH DX
        MOV DL, AL
        MOV AH,2
        INT 21H
        POP DX
        POP AX
        RET 
PUTC 	ENDP 

GETN 	PROC NEAR
        ;------------------------------------------------------------------------
        ; Klavyeden basılan sayiyi okur, sonucu AX yazmacı üzerinden dondurur. 
        ; DX: sayının işaretli olup/olmadığını belirler. 1 (+), -1 (-) demek 
        ; BL: hane bilgisini tutar 
        ; CX: okunan sayının islenmesi sırasındaki ara değeri tutar. 
        ; AL: klavyeden okunan karakteri tutar (ASCII)
        ; AX zaten dönüş değeri olarak değişmek durumundadır. Ancak diğer 
        ; yazmaçların önceki değerleri korunmalıdır. 
        ;------------------------------------------------------------------------
        PUSH BX
        PUSH CX
        PUSH DX
GETN_START:
        MOV DX, 1	                        ; sayının şimdilik + olduğunu varsayalım 
        XOR BX, BX 	                        ; okuma yapmadı Hane 0 olur. 
        XOR CX,CX	                        ; ara toplam değeri de 0’dır. 
NEW:
        CALL GETC	                        ; klavyeden ilk değeri AL’ye oku. 
        CMP AL,CR 
        JE FIN_READ	                        ; Enter tuşuna basilmiş ise okuma biter
        CMP  AL, '-'	                        ; AL ,'-' mi geldi ? 
        JNE  CTRL_NUM	                        ; gelen 0-9 arasında bir sayı mı?
NEGATIVE:                      
        JMP ERROR		                        ; yeni haneyi al
CTRL_NUM:
        CMP AL, '0'	                        ; sayının 0-9 arasında olduğunu kontrol et.
        JB error 
        CMP AL, '9'
        JA error		                ; değil ise HATA mesajı verilecek
        SUB AL,'0'	                        ; rakam alındı, haneyi toplama dâhil et 
        MOV BL, AL	                        ; BL’ye okunan haneyi koy 
        MOV AX, 10 	                        ; Haneyi eklerken *10 yapılacak 
        PUSH DX		                        ; MUL komutu DX’i bozar işaret için saklanmalı
        MUL CX		                        ; DX:AX = AX * CX
        POP DX		                        ; işareti geri al 
        MOV CX, AX	                        ; CX deki ara değer *10 yapıldı 
        ADD CX, BX 	                        ; okunan haneyi ara değere ekle 
        JMP NEW 		                ; klavyeden yeni basılan değeri al 
ERROR:
        MOV AX, OFFSET HATA 
        CALL PUT_STR	                        ; HATA mesajını göster 
        JMP GETN_START                          ; o ana kadar okunanları unut yeniden sayı almaya başla 
FIN_READ:
        MOV AX, CX	                        ; sonuç AX üzerinden dönecek 
        CMP DX, 1	                        ; İşarete göre sayıyı ayarlamak lazım 
        JE FIN_GETN
        NEG AX		                        ; AX = -AX
FIN_GETN:
        POP DX
        POP CX
        POP DX
        RET 
GETN 	ENDP 

PUTN 	PROC NEAR
        ;------------------------------------------------------------------------
        ; AX de bulunan sayiyi onluk tabanda hane hane yazdırır. 
        ; CX: haneleri 10’a bölerek bulacağız, CX=10 olacak
        ; DX: 32 bölmede işleme dâhil olacak. Soncu etkilemesin diye 0 olmalı 
        ;------------------------------------------------------------------------
        PUSH CX
        PUSH DX 	
        XOR DX,	DX 	                        ; DX 32 bit bölmede soncu etkilemesin diye 0 olmalı 
        PUSH DX		                        ; haneleri ASCII karakter olarak yığında saklayacağız.
                                                ; Kaç haneyi alacağımızı bilmediğimiz için yığına 0 
                                                ; değeri koyup onu alana kadar devam edelim.
        MOV CX, 10	                        ; CX = 10
        CMP AX, 0
        JGE CALC_DIGITS	
        NEG AX 		                        ; sayı negatif ise AX pozitif yapılır. 
        PUSH AX		                        ; AX sakla 
        MOV AL, '-'	                        ; işareti ekrana yazdır. 
        CALL PUTC
        POP AX		                        ; AX’i geri al 
        
CALC_DIGITS:
        DIV CX  		                ; DX:AX = AX/CX  AX = bölüm DX = kalan 
        ADD DX, '0'	                        ; kalan değerini ASCII olarak bul 
        PUSH DX		                        ; yığına sakla 
        XOR DX,DX	                        ; DX = 0
        CMP AX, 0	                        ; bölen 0 kaldı ise sayının işlenmesi bitti demek
        JNE CALC_DIGITS	                        ; işlemi tekrarla 
        
DISP_LOOP:
                                                ; yazılacak tüm haneler yığında. En anlamlı hane üstte 
                                                ; en az anlamlı hane en alta ve onu altında da 
                                                ; sona vardığımızı anlamak için konan 0 değeri var. 
        POP AX		                        ; sırayla değerleri yığından alalım
        CMP AX, 0 	                        ; AX=0 olursa sona geldik demek 
        JE END_DISP_LOOP 
        CALL PUTC 	                        ; AL deki ASCII değeri yaz
        JMP DISP_LOOP                           ; işleme devam
        
END_DISP_LOOP:
        POP DX 
        POP CX
        RET
PUTN 	ENDP 

PUT_STR	PROC NEAR
        ;------------------------------------------------------------------------
        ; AX de adresi verilen sonunda 0 olan dizgeyi karakter karakter yazdırır.
        ; BX dizgeye indis olarak kullanılır. Önceki değeri saklanmalıdır. 
        ;------------------------------------------------------------------------
	PUSH BX 
        MOV BX,	AX			        ; Adresi BX’e al 
        MOV AL, BYTE PTR [BX]	                ; AL’de ilk karakter var 
PUT_LOOP:   
        CMP AL,0		
        JE  PUT_FIN 			        ; 0 geldi ise dizge sona erdi demek
        CALL PUTC 			        ; AL’deki karakteri ekrana yazar
        INC BX 				        ; bir sonraki karaktere geç
        MOV AL, BYTE PTR [BX]
        JMP PUT_LOOP			        ; yazdırmaya devam 
PUT_FIN:
	POP BX
	RET 
PUT_STR	ENDP

CSEG 	ENDS 
END MAIN