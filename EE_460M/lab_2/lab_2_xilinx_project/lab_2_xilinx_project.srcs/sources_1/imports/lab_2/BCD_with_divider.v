
module BCD_with_divider(D, enable, load, up, clear, clock, Q, carry_out);
	parameter N = 100000000;

	input [3:0] D;
	input enable, load, up, clear, clock;
	output [3:0] Q;
	output carry_out;
	
	wire reduced_clock;
	
	divider #(.DIVIDE_BY(N)) div (
		.clock_in	(clock),
		.clock_out	(reduced_clock)
	);
	
	BCDCounter bcd0 (
		.D			(D),
		.enable		(enable),
		.load		(load),
		.up			(up),
		.clear		(clear),
		.clock		(reduced_clock),
		.Q			(Q),
		.carry_out	(carry_out)
	);
	
	
endmodule
