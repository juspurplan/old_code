


module divider (clock_in, clock_out);
	parameter DIVIDE_BY = 1000;
	parameter DURATION = DIVIDE_BY/2;
	input clock_in;
	output clock_out;
	
	integer count;
	reg out;
	
	initial begin
		count <= 0;
		out <= 0;
	end
	
	assign clock_out = out;
	
	always @(posedge clock_in) begin
		if (count == DIVIDE_BY -1) begin
			count <= 0;
		end
		else begin
			count <= count+1;
		end
		
		if (count >= 0 && count < DURATION) begin
			out <= 1;
		end
		else begin
			out <= 0;
		end
		
	end

endmodule
