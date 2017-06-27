
module excess3_behavioral (X, S, V, clock);
	input clock;
	input X;
	output S, V;

	reg [1:0] state;
	reg out;
	reg carry;
	
	initial begin
		state <= 2'b00;
		out <= 0;
		carry <= 0;
	end
	
	
	
	assign S = out; // registered (syncronized) output AKA output changes with clock and is delayed by 1 cycle..
					// the dataflow version does not have registered outputs. they can contain "glitches". they are not delayed.
	assign V = carry && !state[1] && !state[0];
	
	always @(posedge clock) begin
		case (state) 
		2'b00: begin
			{carry, out} <= X + 1;
			state <= 2'b01;
		end
		2'b01: begin
			{carry, out} <= X + 1 + carry;
			state <= 2'b10;
		end
		2'b10: begin
			{carry, out} <= X + carry;
			state <= 2'b11;
		end
		2'b11: begin
			{carry, out} <= X + carry;
			state <= 2'b00;
		end
		endcase
		
	end

endmodule
