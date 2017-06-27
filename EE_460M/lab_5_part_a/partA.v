module partA(clock, PS2Clk, PS2Data, commons, segments, strobe, command);
	input clock, PS2Clk, PS2Data;
	output [3:0] commons;
	output [7:0] segments;
	output strobe;
	output [3:0] command;
	
	parameter CLOCK_FREQUENCY = 100000000; // default to 100 MHz
	
	wire [21:0] codes, new_code;
	wire [3:0] h3, h2, h1, h0;
	wire [3:0] commons, c;
	wire [7:0] segments, s;
	wire en_change, read;
	reg [3:0] c_masked;
	reg [7:0] s_masked;

	// reads in code and saves as a single 22-bit register
	// format: Start, 0, 1, 2, 3, 4, 5, 6, 7, P, Stop [x2]
	ShiftReg shift(
		.clk		(PS2Clk),
		.shift_in	(PS2Data),
		.reg_value	(codes),
		.read       (en_check)
	);

	// change BCD4 when codes == F0??
	ChangeCode en_chg (
		.shift_reg		(codes),
		.enable_check   (en_check),
		.enable_change	(en_change)
	);
	
	CodeReg CR (
		.enable_change	(en_change),
		.new_code	    (codes),
		.hex1		    (h1),
		.hex0		    (h0)
	);
	
	Strobe str (
	    .clk       (clock),
	    .PS2Clk    (PS2Clk),
	    .en_check  (en_check),
	    .en_change (en_change),
	    .strobe    (strobe)
	);
	
	// takes our 2 hex digits, and outputs them
	// commons are active low (common anode configuration)
	// each segment is active low.
	SevenSegmentDisplayController #(
		.CLOCK_FREQUENCY	(CLOCK_FREQUENCY),
		.REFRESH_RATE		(80)
	) 
	display0 (
		.hex1(h1),
		.hex0(h0),
		.clock(clock),

		.commons(c),
		.segments(s)
	);
            
            KeyToCommand ktc(
               .clk        (clock),
               .PS2Clk     (PS2Clk),
               .hex1       (hex1),
               .hex0       (hex0),
               .command    (command),
			   .en_change	(en_change)
            );
	
	assign commons = c_masked;
	assign segments = s_masked;
	always @(*) begin
	   if((h1 == 4'b 0) && (h0 == 4'b 0))
	   begin
	       c_masked = 4'b 1111;
           s_masked = 8'b 11111111;
       end
	   else
	   begin
	       c_masked = c;
           s_masked = s;
       end
	end
	
endmodule