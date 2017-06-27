	.ORIG x3000
LEA R0, fun
LDW R1, R0, #0
LEA R0, wee
ADD R0, R0, #8

STW R1, R0, #0
ADD R1, R1, #1
STW R1, R0, #2
STB R1, R0, #6
STB R1, R0, #5

HALT

; check address #12315 to #12330

fun .FILL x0123
wee .FILL x1111
.END