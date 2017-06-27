
module VGADisplayController (pixel_clock, color, hsync, vsync, RED, GREEN, BLUE);
	input pixel_clock;
	input [11:0] color;
	output hsync, vsync;
	output [3:0] RED, GREEN, BLUE;
	
	parameter WIDTH = 640;
	parameter HEIGHT = 480;
	
	parameter X_BLANK_SIZE = 160;
	parameter X_BLANK_LOW = 19;
	parameter X_BLANK_HIGH = 115;
	
	parameter Y_BLANK_SIZE = 45;
	parameter Y_BLANK_LOW = 13;
	parameter Y_BLANK_HIGH = 15;

	reg [31:0] hcount;
	reg [31:0] vcount;
	
	// output registers
	reg hs_out;
	reg vs_out;
	reg [3:0] R_out;
	reg [3:0] G_out;
	reg [3:0] B_out;
	
	assign hsync = hs_out;
	assign vsync = vs_out;
	assign RED = R_out;
	assign GREEN = G_out;
	assign BLUE = B_out;
	
	initial begin
		hcount <= 0;
		vcount <= 0;
		hs_out <= 0;
		vs_out <= 0;
		R_out <= 0;
		G_out <= 0;
		B_out <= 0;
	end
	
	
	always @(posedge pixel_clock) begin
		// update hcount, vcount registers
		if (hcount +1 >= WIDTH + X_BLANK_SIZE) begin
			hcount <= 0;
			
			if (vcount +1 >= HEIGHT + Y_BLANK_SIZE) begin
				vcount <= 0;
			end
			else begin
				vcount <= vcount +1;
			end
		end
		else begin
			hcount <= hcount +1;
			vcount <= vcount;
		end
		

		
		// update color registers, based on current hcount, vcount
		if(hcount >= 0 && hcount < WIDTH && vcount >= 0 && vcount < HEIGHT) begin
			R_out <= color[11:8];
			G_out <= color[7:4];
			B_out <= color[3:0];
		end
		else begin
			R_out <= 4'd 0;
			G_out <= 4'd 0;
			B_out <= 4'd 0;
		end

	end
	
	
	always @(*) begin
		// update hs_out and vs_out registers based on current hcount,vcount
		if(hcount >= WIDTH + X_BLANK_LOW && hcount < WIDTH + X_BLANK_HIGH) begin
			hs_out <= 0;
		end
		else begin
			hs_out <= 1;
		end
			
		if(vcount >= HEIGHT + Y_BLANK_LOW  && vcount < HEIGHT + Y_BLANK_HIGH ) begin
			vs_out <= 0;
		end
		else begin
			vs_out <= 1;
		end
	end
	
endmodule
	