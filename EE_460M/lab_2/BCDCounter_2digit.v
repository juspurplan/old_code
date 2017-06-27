
module BCDCounter_2digit (D1, D0, enable, up, load, clear, clock, Q1, Q0, carry_out);
	input [3:0] D1, D0;
	input enable, up, load, clear, clock;
	output [7:0] Q1, Q0;
	output carry_out;
	
	wire c0_out;
	reg c1_in;
	
	
	BCDCounter bcd0 (
		.D 			(D0),
		.enable		(enable),
		.up			(up),
		.load		(load),
		.clear		(clear),
		.clock		(clock),
		.Q			(Q0),
		.carry_out	(c0_out)
	);
	
	BCDCounter bcd1 (
		.D 			(D1),
		.enable		(enable),
		.up			(up),
		.load		(load),
		.clear		(clear),
		.clock		(c1_in),
		.Q			(Q1),
		.carry_out	(carry_out)
	);
	
	
	//we must store the carry_out from BCD0 in a register in order to synchronize it with bcd1. 
	//Otherwise it will clock bcd1 ansychronously. before bcd0 clocks. 
	//example:  98 => 99 => 09 => 00

	always @(posedge clock) begin
		c1_in <= c0_out;
	end

endmodule
