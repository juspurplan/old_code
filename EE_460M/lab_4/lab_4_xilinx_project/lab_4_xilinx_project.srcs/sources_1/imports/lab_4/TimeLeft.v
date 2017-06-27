
module TimeLeft(decrement, add50, add150, add200, add500, reset10, reset205, clock, count);
	input decrement, add50, add150, add200, add500, reset10, reset205, clock;
	output [13:0] count;
	
	reg [13:0] num;
	
	initial begin
		num <= 0;
	end
	
	assign count = num;
	
	always @(posedge clock) begin:calculate_time
		reg [13:0] temp; // temporary local variable
		temp = num;
	
		/* compute new number using temporary variable */
		/* should synthesize as combinational */
		if (reset10) begin
			/* reset10 has priority over reset205 (when both resets are active) */
			temp = 10;
		end
		else if (reset205) begin
			temp = 205;
		end
		else if (num == 14'd 0 && decrement && {add50, add150, add200, add500} == 4'b 0000) begin
			/* case where we check if our new number < 0 */
			temp = 0;
		end
		else begin
			temp = (decrement)?(temp -1):(temp);
			temp = (add50)?(temp +50):(temp);
			temp = (add150)?(temp +150):(temp);
			temp = (add200)?(temp +200):(temp);
			temp = (add500)?(temp +500):(temp);
			
			/* check for new number > 9999 */
			temp = (temp > 9999)?(9999):(temp);
		end
		
		/* assign temporary variable to our register */
		num <= temp;
	end
	
endmodule
