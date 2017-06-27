// This file is part of the materials accompanying the book 
// "The Elements of Computing Systems" by Nisan and Schocken, 
// MIT Press. Book site: www.idc.ac.il/tecs
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

// Put your code here.

(START)
	@24576
	D=M
	@WHITEOUT
	D;JEQ
	@BLACKOUT
	0;JMP
(WHITEOUT)
	@whattowrite
	M=0
	@PREDRAW
	0;JMP
(BLACKOUT)
	@whattowrite
	M=-1
(PREDRAW)
	@16384
	D=A
	@loc
	M=D
(DRAW)
	@whattowrite
	D=M
	@loc
	A=M
	M=D
	@24575
	D=A
	@loc
	D=D-M
	M=M+1
	@DRAW
	D;JGE
	@START
	0;JMP
