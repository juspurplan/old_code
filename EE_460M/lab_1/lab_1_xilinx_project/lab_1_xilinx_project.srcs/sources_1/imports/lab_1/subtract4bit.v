

module subtract4bit(A, B, borrow_in, diff, borrow_out);
	input [3:0] A;
	input [3:0] B;
	input borrow_in;
	output [3:0] diff;
	output borrow_out;
	
	wire b0, b1, b2, b3;
	
	subtract1bit sub0 (A[0], B[0], borrow_in, diff[0], b0);
	subtract1bit sub1 (A[1], B[1], b0, diff[1], b1);
	subtract1bit sub2 (A[2], B[2], b1, diff[2], b2);
	subtract1bit sub3 (A[3], B[3], b2, diff[3], b3);

	assign borrow_out = b3;
	
endmodule
