module DFF(D, CLK, Q, QN);
	input D;
	input CLK;
	output Q;
	output QN;

	reg Q;
	reg QN;

	initial
	begin
		Q <= 1'b0;
		QN <= 1'b1;
	end

	always @(posedge CLK)
	begin
		Q <= D;
		QN <= (~D);
	end
endmodule

module AND_2 (A1, A2, Z);
	input A1, A2;
	output Z;

	assign Z = (A1 & A2);
endmodule

module Debouncer(BINPUT, CLK, DEBOUTPUT);		// switch only needs this
	input BINPUT, CLK;
	output DEBOUTPUT;
	wire BINPUT;
	wire CLK;
	wire Q2, Q3N;
	
	DFF FF1(BINPUT, CLK, Q1, Q1N);
	DFF FF2(Q1, CLK, Q2, Q2N);
	DFF FF3(Q2, CLK, DEBOUTPUT, Q3N);
endmodule

module SinglePulser(PINPUT, CLK, PULINPUT);	// button needs this too
	input PINPUT, CLK;
	output PULINPUT;
	wire PINPUT;
	wire CLK;
	wire PULINPUT;

	DFF FF3(PINPUT, CLK, Q, QN);
	AND_2 G1(PINPUT, QN, PULINPUT);
endmodule

module DebPul(SIG, CLK_slow, CLK, SP);
	input SIG, CLK_slow, CLK;
	output SP;
	wire SIG;
	wire CLK;
	wire SP;
	wire SYNCPRESS;

	Debouncer DEB(SIG, CLK_slow, SYNCPRESS);
	SinglePulser PUL(SYNCPRESS, CLK, SP);
endmodule