
module PartB(clock, switches, hsync, vsync, R, G, B);
	input clock;
	input [7:0] switches;
	output hsync, vsync;
	output [3:0] R, G, B;
	
	
	wire pixel_clock;
	wire update_clock;
	
	reg [11:0] raster_array [0:640-1][0:480-1];
	reg [640*480*12 -1 : 0] flat_raster;
	
	// flatten the raster array
	integer x, y;
	always @(*) begin
		for(x = 0; x < 640; x= x+1) begin
			for(y = 0; y < 480; y= y+1) begin
				flat_raster[y*480 + x*12 +: 12] = raster_array[x][y];
			end
		end
	end
	
	Divider #(
		.DIVIDE_BY	(2000000)
	) 
	div1 (
		.clock_in	(clock),
		.clock_out	(update_clock)
	);
	
	// update raster  register based on switches
	always @(posedge update_clock) begin
		case(switches)
		8'b 00000001: begin // black
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h 000;
				end
			end
		end
		8'b 00000010: begin // blue
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h 00F;
				end
			end
		end
		8'b 00000100: begin // brown 
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h A22;
				end
			end
		end
		8'b 00001000: begin // cyan
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h 0FF;
				end
			end
		end
		8'b 00010000: begin // red
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h F00;
				end
			end
		end
		8'b 00100000: begin // magenta
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h F0F;
				end
			end
		end
		8'b 01000000: begin // yellow
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h FF0;
				end
			end
		end
		8'b 10000000: begin // white
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h FFF;
				end
			end
		end
		default: begin // black
			for(x = 0; x < 640; x= x+1) begin
				for(y = 0; y < 480; y= y+1) begin
					raster_array[x][y] <= 12'h 000;
				end
			end
		end
		endcase
	end
	
	// divide main clock by 4 to get 25 MHz pixel clock
	// 100 MHz / 4 = 25 MHz
	Divider #(
		.DIVIDE_BY	(4)
	)
	div0 (
		.clock_in	(clock),
		.clock_out	(pixel_clock)
	);
	
	VGADisplayController disp0 (
		.pixel_clock	(pixel_clock),
		.raster			(flat_raster),
		.hsync			(hsync),
		.vsync			(vsync),
		.RED			(R),
		.GREEN			(G),
		.BLUE			(B)
	);

endmodule
