.ORIG #1000

LEA R0, num1
LDW R0, R0, #0
LEA R1, num2
LDW R1, R1, #0

NOT R0, R0
NOT R1, R1
XOR R2, R0, R1
XOR R3, R0, #-16

HALT

num1	.FILL xAAAA
num2	.FILL x5555


.END