
module VGADisplayController (pixel_clock, raster, hsync, vsync, RED, GREEN, BLUE);
	input pixel_clock;
	output hsync, vsync;
	output [7:0] RED, GREEN, BLUE;
	
	parameter WIDTH = 640;
	parameter HEIGHT = 480;
	input [WIDTH*HEIGHT*12 -1 : 0] raster;
	
	parameter X_BLANK_SIZE = 160;
	parameter X_BLANK_LOW = 19;
	parameter X_BLANK_HIGH = 116;
	
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
	
	// convert flatten raster into 2d raster array
	reg [11:0] raster_array [0 : WIDTH-1][0 : HEIGHT-1];
	integer x, y;
	always @(*) begin
		for(x = 0; x < WIDTH; x= x+1) begin
			for(y = 0; y < HEIGHT; y= y+1) begin
				raster_array[x][y] = raster[y*HEIGHT + x*12 +: 12];
			end
		end
	end
	
	always @(posedge pixel_clock) begin
		// update hcount, vcount registers
		if (hcount >= WIDTH + X_BLANK_SIZE) begin
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
		end
		
		// update hs_out and vs_out registers based on current hcount,vcount
		if(hcount >= WIDTH + X_BLANK_LOW && hcount < WIDTH + X_BLANK_HIGH) begin
			hs_out <= 0;
		end
		else begin
			hs_out <= 1;
		end
			
		if(vcount >= HEIGHT + Y_BLANK_LOW && vcount < WIDTH + Y_BLANK_HIGH) begin
			vs_out <= 0;
		end
		else begin
			vs_out <= 1;
		end
		
		// update color registers, based on current hcount, vcount, and combinational input from raster data
		if(hcount >= 0 && hcount < WIDTH && vcount >= 0 && vcount < HEIGHT) begin
			R_out <= raster_array [hcount][vcount] [11:8];		// upper 4 bits
			G_out <= raster_array [hcount][vcount] [7:4];		// mid 4 bits
			B_out <= raster_array [hcount][vcount] [3:0];		// lower 4 bits
		end
		else begin
			R_out <= 4'd 0;
			G_out <= 4'd 0;
			B_out <= 4'd 0;
		end

	end
	
endmodule
	