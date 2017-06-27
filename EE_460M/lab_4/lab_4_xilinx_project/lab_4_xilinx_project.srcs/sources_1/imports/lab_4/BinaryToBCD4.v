
// combinational circuit to convert a 14-bit binary to 4-digit BCD
module BinaryToBCD4 (num, bcd3, bcd2, bcd1, bcd0);
	input [13:0] num;
	output [3:0] bcd3, bcd2, bcd1, bcd0;
	
	reg [3:0] d3, d2, d1, d0;
	
	assign bcd3 = d3;
	assign bcd2 = d2;
	assign bcd1 = d1;
	assign bcd0 = d0;
	
	always @(*) begin:stuff
		reg [13:0] temp;
		reg [13:0] foo;
		temp = num;
		foo = temp%10;
		d0 = {foo[3:0]};
		
		temp = temp/10;
		foo = temp%10;
		d1 = {foo[3:0]};
		
		temp = temp/10;
		foo = temp%10;
		d2 = {foo[3:0]};
		
		temp = temp/10;
		foo = temp%10;
		d3 = {foo[3:0]};
	
	end
endmodule
