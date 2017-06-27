
module excess3_structural (X, S, V, clock, rst) ;
	input X;
	input clock;
	input rst;
	output S, V;
	
	wire [1:0] state;
	wire carry;
	
	wire next_carry;
	wire [1:0] next_state;
	

	
	DFF s0 ( 
		.D (next_state[0]),
		.Q (state[0]),
		.clk (clock),
		.reset (rst) 
	);
	DFF s1 (
		.D (next_state[1]),
		.Q (state[1]),
		.clk (clock),
		.reset (rst)
	);
	DFF c (
		.D (next_carry),
		.Q (carry),
		.clk (clock),
		.reset (rst)
		
	);
	
	assign next_state[0] = !state[0];
	// next_state[0] is 1 when state is 00 or 10
	
	
	assign next_state[1] = (!state[1] && state[0]) || (state[1] && !state[0]);
	//next_state[1] is 1 when state is 01 or 10
	
	assign next_carry = (X && carry) || (X && !state[1] && state[0]) || (!state[1] && state[0] && carry) || (!state[1] && !state[0] && X);
	
	assign S = (!state[1] && !state[0] && !X) || (!state[1] && state[0] && !(X ^ carry)) || (state[1] && !state[0] && (X ^ carry)) || (state[1] && state[0] && (X^carry));
	assign V = (!state[1] && !state[0] && carry);
	
	
	

endmodule



module DFF (D, Q, clk, reset);
	input D, clk, reset;
	output Q;
	
	reg result;
	
	assign Q = result;
	
	//active low reset
	always @(posedge clk, reset) begin
		if (!reset) begin
			result <= 0;
		end
		else  begin
			result <= D;
		end
	end

endmodule


