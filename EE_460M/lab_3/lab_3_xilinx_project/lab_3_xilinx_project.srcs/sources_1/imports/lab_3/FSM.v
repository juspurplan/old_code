
module FSM ( clock, reset, current_state);
	input clock, reset;
	output [2:0] current_state;
	
	
	reg [2:0] state;
	
	assign current_state = state;
	
	initial begin
		state <= 3'd 1;
	end
	
	always @(posedge clock) begin
		if (reset == 1) begin
			state <= 3'd 0;
		end
		else begin
			case(state)
			3'd 0: state <= 3'd 1;
			3'd 1: state <= 3'd 2;
			3'd 2: state <= 3'd 3;
			3'd 3: state <= 3'd 4;
			3'd 4: state <= 3'd 5; 
			3'd 5: state <= 3'd 6;
			3'd 6: state <= 3'd 1;
			3'd 7: begin end // unused state.
			endcase
		end
	
	end

endmodule
