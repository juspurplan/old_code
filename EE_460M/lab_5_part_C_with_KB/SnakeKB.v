
module SnakeKB(clock, PS2_clock, PS2_data, hsync, vsync, R, G, B, s, coms, segs, strobe);
	input clock, PS2_clock, PS2_data;
	output hsync, vsync;
	output [3:0] R, G, B;
	output [2:0] s;
	
	output [3:0] coms;
	output [7:0] segs;
	output strobe;
	
	// PS2 wire declarations
	
	
	// Game State and VGA wire declarations
	wire game_clock, pixel_clock;
	wire [31:0] x,y;
	wire [11:0] c;
	wire [3:0] in;
	
	////
	// PS2 code
	////
	
	partA pa (
		.clock		(clock),
		.PS2Clk		(PS2_clock),
		.PS2Data	(PS2_data),
		.commons	(coms),
		.segments	(segs),
		.strobe		(strobe),
		.command	(in)
	);
	
	
	////
	// Game State and VGA code below
	////
	Divider #(
		.DIVIDE_BY	(2000000)
	)
	div0 (
		.clock_in	(clock),
		.clock_out	(game_clock)
	);
	
	Divider #(
		.DIVIDE_BY	(4)
	)
	div1 (
		.clock_in	(clock),
		.clock_out	(pixel_clock)
	);
	
	GameState gs0 (
		.clock				(game_clock),
		.in					(in),
		.x_coord_in			(x),
		.y_coord_in			(y),
		.pixel_color_out	(c),
		.state_out			(s)
	);
	
	VGADisplayController disp0 (
		.pixel_clock	(pixel_clock),
		.color			(c),
		.x_coord		(x),
		.y_coord		(y),
		.hsync			(hsync),
		.vsync			(vsync),
		.RED			(R),
		.GREEN			(G),
		.BLUE			(B)
	);
	
endmodule	
