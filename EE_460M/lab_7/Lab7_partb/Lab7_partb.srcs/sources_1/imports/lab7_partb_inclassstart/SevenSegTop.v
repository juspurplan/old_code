module SevenSegTop(clock, data, commons, segments);
	input clock;
	input [15:0] data;
	output [3:0] commons;
	output [6:0] segments;
	
	parameter CLOCK_FREQUENCY = 100000000; // default to 100 MHz
	
	wire [3:0] h3, h2, h1, h0;
	wire [3:0] commons, c;
	wire [6:0] segments, s;
	reg [3:0] c_masked;
	reg [6:0] s_masked;
	
	assign h3 = data[15:12];
	assign h2 = data[11:8];
	assign h1 = data[7:4];
	assign h0 = data[3:0];
	
	// takes our 2 hex digits, and outputs them
	// commons are active low (common anode configuration)
	// each segment is active low.
	SevenSegmentDisplayController #(
		.CLOCK_FREQUENCY	(CLOCK_FREQUENCY),
		.REFRESH_RATE		(80)
	) 
	display0 (
	    .hex3(h3),
	    .hex2(h2),
		.hex1(h1),
		.hex0(h0),
		.clock(clock),

		.commons(c),
		.segments(s)
	);
	
	assign commons = c_masked;
	assign segments = s_masked;
	always @(*) begin
	   /*if((h1 == 4'b 0) && (h0 == 4'b 0))
	   begin
	       c_masked = 4'b 1111;
           s_masked = 8'b 1111111;
       end
	   else*/
	   //begin
	       c_masked = c;
           s_masked = s;
       //end
	end
	
endmodule