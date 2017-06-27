
module ParkingMeter(add50, add150, add200, add500, reset10, reset205, clock, commons, segments);
	input add50, add150, add200, add500, reset10, reset205, clock;
	output [3:0] commons;
	output [7:0] segments;
	
	parameter CLOCK_FREQUENCY = 100000000; // default to 100 MHz 
	
	wire add50_filtered, add150_filtered, add200_filtered, add500_filtered;
	wire reset10_filtered, reset205_filtered;
	
	wire debouncer_clock;
	wire decrement_tick;
	wire flasher_1Hz;
	wire flasher_halfHz;
	
	wire [13:0] remaining_time;
	
	wire [3:0] d3, d2, d1, d0;
	wire [3:0] c; 
	wire [7:0] s;
	reg [3:0] c_masked;
	
	// Filter our inputs. 
	// Buttons: Debounce then 1-shot.
	// Switches: Debounce only.
	// bounce time is about 10ms, use 20ms to be safe. (20 ms period = 50 Hz)
	// TODO input filter
	DebPul dp_add50 (
		.SIG		(add50),
		.CLK_slow	(debouncer_clock),
		.CLK		(clock),
		.SP			(add50_filtered)
	);
	DebPul dp_add150 (
		.SIG		(add150),
		.CLK_slow	(debouncer_clock),
		.CLK		(clock),
		.SP			(add150_filtered)
	);
	DebPul dp_add200 (
		.SIG		(add200),
		.CLK_slow	(debouncer_clock),
		.CLK		(clock),
		.SP			(add200_filtered)
	);
	DebPul dp_add500 (
		.SIG		(add500),
		.CLK_slow	(debouncer_clock),
		.CLK		(clock),
		.SP			(add500_filtered)
	);
	Debouncer deb_reset10 (
		.BINPUT		(reset10),
		.CLK		(debouncer_clock),
		.DEBOUTPUT	(reset10_filtered)
	);
	Debouncer deb_reset205 (
		.BINPUT		(reset205),
		.CLK		(debouncer_clock),
		.DEBOUTPUT	(reset205_filtered)
	);
	
	// reduced clock for the debouncer
	Divider #(
		.DIVIDE_BY	(CLOCK_FREQUENCY/100),
		.DURATION	()
	)
	db_div (
		.clock_in	(clock),
		.clock_out	(debouncer_clock)
	);

	
	// div0 pulses at 1Hz to decrement the parking meter
	Divider #(
		.DIVIDE_BY	(CLOCK_FREQUENCY),
		.DURATION	(1)
	) 
	div0 (
		.clock_in	(clock),
		.clock_out	(decrement_tick)
	);
	
	// div1, reduced 1 Hz clock for flashers
	// div2, reduced 2 Hz clock for flashers
	// default DURATION, 50% duty cycle for both
	Divider #(
		.DIVIDE_BY	(CLOCK_FREQUENCY),
		.DURATION	()
	) 
	div1 (
		.clock_in	(clock),
		.clock_out	(flasher_1Hz)
	);
	Divider #(
		.DIVIDE_BY	(CLOCK_FREQUENCY*2),
		.DURATION	()
	) 
	div2 (
		.clock_in	(clock),
		.clock_out	(flasher_halfHz)
	);
	
	// keeps track of how much time is left
	TimeLeft tl0 (
		.decrement(decrement_tick),
		.add50		(add50_filtered),
		.add150		(add150_filtered),
		.add200		(add200_filtered),
		.add500		(add500_filtered),
		.reset10	(reset10_filtered),
		.reset205	(reset205_filtered),
		.clock		(clock),
		.count		(remaining_time)
	);
	
	// converts our time left binary number => 4 digit BCD
	BinaryToBCD4 b_to_bcd4_0 (
		.num	(remaining_time),
		.bcd3	(d3),
		.bcd2	(d2),
		.bcd1	(d1),
		.bcd0	(d0)
	);
	
	// takes our 4 BCD digits, and outputs them
	// commons are active low (common anode configuration)
	// each segment is active low.
	SevenSegmentDisplayController #(
		.CLOCK_FREQUENCY	(CLOCK_FREQUENCY),
		.REFRESH_RATE		(80)
	) 
	display0 (
		.bcd3(d3),
		.bcd2(d2),
		.bcd1(d1),
		.bcd0(d0),
		.clock(clock),

		.commons(c),
		.segments(s)
	);
	
	// FLASHER
	// logic to choose which flasher to use (or no flasher) and MASK with the display controller output
	// assigns have a bit-wise NOT, since outputs are active low
	assign commons = ~c_masked;
	assign segments = ~s;
	always @(*) begin
		if(remaining_time == 0) begin
			c_masked = c & {4{flasher_1Hz}};
		end
		else if (remaining_time < 200) begin
			c_masked = c & ( (((remaining_time%2 == 0) && (flasher_halfHz)) || ((remaining_time%2==1) && (~flasher_halfHz)))?({4{flasher_halfHz}}):(~{4{flasher_halfHz}}) );
		end
		else begin
			c_masked = c;
		end
	
	end

endmodule
