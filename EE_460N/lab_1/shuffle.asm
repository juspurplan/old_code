.ORIG x3000
LEA R0, maskptr   
LDW R0, R0, #0  ;R0 <= x4004 
LDW R0, R0, #0 ;R0 <= MASK
LEA R1, maskmask 
LDW R1, R1, #0 ;R1 <= 0x003

LEA R2, inptr
LDW R2, R2, #0 ;R2<= x4000 input
LEA R3, outptr
LDW R3, R3, #0 ;R3 <= x4005 output

AND R4, R0, R1 ;R4 <= mask right 2 bits
ADD R4, R4, R2
LDB R4, R4, #0
STB R4, R3, #0

RSHFL R0, R0, #2 ;shift remask
AND R4, R0, R1 ;R4 <= mask right 2 bits
ADD R4, R4, R2
LDB R4, R4, #0
STB R4, R3, #1

RSHFL R0, R0, #2 ;shift remask
AND R4, R0, R1 ;R4 <= mask right 2 bits
ADD R4, R4, R2
LDB R4, R4, #0
STB R4, R3, #2

RSHFL R0, R0, #2 ;shift remask
AND R4, R0, R1 ;R4 <= mask right 2 bits
ADD R4, R4, R2
LDB R4, R4, #0
STB R4, R3, #3


inptr .FILL x4000
maskptr .FILL x4004
outptr .FILL x4005

maskmask .FILL x0003

.END