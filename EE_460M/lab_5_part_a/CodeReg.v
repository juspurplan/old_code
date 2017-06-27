module CodeReg(enable_change, new_code, hex1, hex0);
	input enable_change;
	input [21:0] new_code;
	output [3:0] hex1, hex0;

	//reg [3:0] hex1, hex0;
	reg [3:0] temp1, temp0;

	always @(posedge enable_change)
	begin
		temp1 = new_code[5:2];
		temp0 = new_code[9:6];
	end
	
	assign hex1 = {temp1[0], temp1[1], temp1[2], temp1[3]};
	assign hex0 = {temp0[0], temp0[1], temp0[2], temp0[3]};
endmodule