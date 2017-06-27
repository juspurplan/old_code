// This file is part of the materials accompanying the book 
// "The Elements of Computing Systems" by Nisan and Schocken, 
// MIT Press. Book site: www.idc.ac.il/tecs
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[3], respectively.)

// Put your code here.

	@counter
	M=0
	@R2
	M=0
(LOOP)
	@counter
	D=M
	@R1
	D=M-D
	@END
	D;JLE
	
	@R2
	D=M
	@R0
	D=D+M
	@R2
	M=D
	@counter
	M=M+1
	@LOOP
	0;JMP
(END)
	@END
	0;JMP