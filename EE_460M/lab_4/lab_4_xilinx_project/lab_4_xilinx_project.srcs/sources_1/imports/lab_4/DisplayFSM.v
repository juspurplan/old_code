
module DisplayFSM(clock, current_state);
	input clock;
	output [1:0] current_state;
	
	reg [1:0] s;
	
	assign current_state = s;
	
	initial begin
		s <= 0;
	end
	
	always @(posedge clock) begin
		case(s)
		2'd 0: s <= 2'd 1;
		2'd 1: s <= 2'd 2;
		2'd 2: s <= 2'd 3;
		2'd 3: s <= 2'd 0;
		endcase
	end
	
endmodule
