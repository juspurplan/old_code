
module SnakeNoKB (clock, up, down, left, right, start, stop, pause, resume, hsync, vsync, R, G, B, s);
	input clock, up, down, left, right, start, stop, pause, resume;
	output hsync, vsync;
	output [3:0] R, G, B;
	output [2:0] s;
	
	wire game_clock, pixel_clock;
	wire [31:0] x,y;
	wire [11:0] c;
	
	reg [3:0] in;
	
	// combinational to turn our inputs into a number representing our input.
	// assumes only 1 input is presed at a time.
	always @(*) begin
		if(start == 1) begin
			in = 4'd 1;
		end
		else if (stop == 1) begin
			in = 4'd 2;
		end
		else if (pause == 1) begin
			in = 4'd 3;
		end
		else if (resume == 1) begin
			in = 4'd 4;
		end
		else if (up == 1) begin
			in = 4'd 5;
		end
		else if (right == 1) begin
			in = 4'd 6;
		end
		else if (down == 1) begin
			in = 4'd 7;
		end
		else if (left == 1) begin
			in = 4'd 8;
		end
		else begin
			in = 4'd 0;
		end
	end
	
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
