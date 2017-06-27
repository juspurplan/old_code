
module Timer (in_state, clock,  out_clock);
	input [2:0] in_state;
	input clock;
	output out_clock;
	
	parameter CLOCK_FREQUENCY = 100000000;
	parameter RESOLUTION = 4;
	parameter STATE1_DURATION = 3;
	parameter STATE2_DURATION = 2;
	parameter STATE3_DURATION = 3;
	parameter STATE4_DURATION = 1;
	parameter STATE5_DURATION = 2;
	parameter STATE6_DURATION = 2;
	
	integer count;
	reg out;
	wire reduced_clock;
	
	
	assign out_clock = out;
	
	initial begin
		count <= 32'd 0;
		out <= 0;
	end
	
	
	divider #(.DIVIDE_BY(CLOCK_FREQUENCY/RESOLUTION)) div0 (
		.clock_in(clock),
		.clock_out(reduced_clock)
	);
	

	always @(posedge reduced_clock) begin

			case(in_state)
			3'd 0: begin 
				if(count >= 1) begin
					out <= 1;
					count <= 0;
				end
				else begin
					out <= 0;
					count <= count +1;
				end
			end
			
			3'd 1: begin
				if(count >= STATE1_DURATION*RESOLUTION -1) begin
					out <= 1;
					count <= 0;
				end
				else begin
					out <= 0;
					count <= count +1;
				end
			end
			
			3'd 2: begin
				if(count >= STATE2_DURATION*RESOLUTION -1) begin
					out <= 1;
					count <= 0;
				end
				else begin
					out <= 0;
					count <= count +1;
				end
			end
			
			3'd 3: begin
				if(count >= STATE3_DURATION*RESOLUTION -1) begin
					out <= 1;
					count <= 0;
				end
				else begin
					out <= 0;
					count <= count +1;
				end
			end
			
			3'd 4: begin
				if(count >= STATE4_DURATION*RESOLUTION -1) begin
					out <= 1;
					count <= 0;
				end
				else begin
					out <= 0;
					count <= count +1;
				end
			end
			
			3'd 5: begin
				if(count >= STATE5_DURATION*RESOLUTION -1) begin
					out <= 1;
					count <= 0;
				end
				else begin
					out <= 0;
					count <= count +1;
				end
			end
			
			3'd 6: begin
				if(count >= STATE6_DURATION*RESOLUTION -1) begin
					out <= 1;
					count <= 0;
				end
				else begin	
					out <= 0;
					count <= count +1;
				end
			end
			
			3'd 7: begin // unused state.
				out <= 0;
				count <= 0;
			end
			endcase
	

	end

endmodule
