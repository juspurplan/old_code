
module SevenSegmentDisplayController(bcd3, bcd2, bcd1, bcd0, clock, commons, segments);
	input [3:0] bcd3, bcd2, bcd1, bcd0;
	input clock;
	output [3:0] commons;
	output [7:0] segments;
	
	parameter CLOCK_FREQUENCY = 100000000;
	parameter REFRESH_RATE = 80;
	parameter DIVIDE_FREQUENCY = (CLOCK_FREQUENCY/REFRESH_RATE)/4; // divide by 4 since we have 4 digits/states
	
	wire [7:0] seg3, seg2, seg1, seg0;
	wire [1:0] state;
	reg [3:0] c;
	reg [7:0] s;
	
	// convert bcd inputs to 7-segment signals
	BCDTo7Segment convert0 (
		.bcd		(bcd0),
		.segments	(seg0)
	);
	BCDTo7Segment convert1 (
		.bcd		(bcd1),
		.segments	(seg1)
	);
	BCDTo7Segment convert2 (
		.bcd		(bcd2),
		.segments	(seg2)
	);
	BCDTo7Segment convert3 (
		.bcd		(bcd3),
		.segments	(seg3)
	);
	
	// reduce the clock so we loop through the FSM at the REFRESH_RATE
	Divider #(
		.DIVIDE_BY(DIVIDE_FREQUENCY)
	) 
	div0 (
		.clock_in	(clock),
		.clock_out	(reduced_clock)
	);
	
	// state machine that loops through all 4 digits.
	DisplayFSM fsm0 (
		.clock			(reduced_clock),
		.current_state	(state)
	);
	
	// combinational logic based on current_state
	assign commons = c;
	assign segments = s;
	
	always @(*) begin
		case(state)
		2'd 0: begin
			c = 4'b 0001;
			s = seg0;
		end
		2'd 1: begin
			c = 4'b 0010;
			s = seg1;
		end
		2'd 2: begin
			c = 4'b 0100;
			s = seg2;
		end
		2'd 3: begin
			c = 4'b 1000;
			s = seg3;
		end
		endcase
		
		
	end

endmodule
