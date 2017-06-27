

module subtract1bit(A, B, borrow_in, diff, borrow_out);
	input A, B, borrow_in;
	output diff, borrow_out;
	
	assign borrow_out = ((!A) && (B || borrow_in))  ||  (A && B && borrow_in); 
	assign diff = 	(A^B)^borrow_in;
	
endmodule
