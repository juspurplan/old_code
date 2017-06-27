.ORIG #1000

		LEA R0, num
		LDW R0, R0, #0

		ADD R0, R0, #2

		JSR double

		ADD R5, R0, #2

		LEA R1, quad
		JSRR R1

		ADD R6, R0, #2
		HALT

double 	ADD R0, R0, R0
		RET
quad 	LEA R4, pointer
		STW R7, R4, #0
		JSR double
		JSR double
		LDW R7, R4, #0
		RET

num .FILL x004A
pointer .FILL x0000


.END