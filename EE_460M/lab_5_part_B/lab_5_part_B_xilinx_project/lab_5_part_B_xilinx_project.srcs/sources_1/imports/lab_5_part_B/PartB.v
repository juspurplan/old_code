
module PartB(clock, switches, hsync, vsync, R, G, B);
	input clock;
	input [7:0] switches;
	output hsync, vsync;
	output [3:0] R, G, B;
	
	
	wire pixel_clock;
	wire update_clock;
	
	reg [11:0] color;
	
	initial begin
		color <= 0;
	end
	
	Divider #(
		.DIVIDE_BY	(2000000)
	) 
	div1 (
		.clock_in	(clock),
		.clock_out	(update_clock)
	);
	
	// update color  register based on switches
	always @(posedge update_clock) begin
		case(switches)
		8'b 00000001: begin // black
			color <= 12'h 000;
		end
		8'b 00000010: begin // blue
			color <= 12'h 00F;
		end
		8'b 00000100: begin // brown 
			color <= 12'h 841;
		end
		8'b 00001000: begin // cyan
			color <= 12'h 0FF;
		end
		8'b 00010000: begin // red
			color <= 12'h F00;
		end
		8'b 00100000: begin // magenta
			color <= 12'h F0F;
		end
		8'b 01000000: begin // yellow
			color <= 12'h FF0;
		end
		8'b 10000000: begin // white
			color <= 12'h FFF;
		end
		default: begin // black
			color <= 12'h 000;
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
		.color			(color),
		.hsync			(hsync),
		.vsync			(vsync),
		.RED			(R),
		.GREEN			(G),
		.BLUE			(B)
	);

endmodule
