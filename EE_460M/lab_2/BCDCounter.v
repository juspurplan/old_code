
module BCDCounter (D, enable, load, up, clear, clock, Q, carry_out);
	input [3:0] D;
	input enable, load, up, clear, clock;
	//output [7:0] Q;
	output [3:0] Q;
	output carry_out;
	
	
	reg [3:0] count;
	//reg [7:0] segments;
	
	
	//combinational
	assign carry_out = (enable && up && (count == 9)) || (enable && !up && (count == 0));
	//assign Q = segments;
	assign Q = count;
	
	
	//combinational for 7 segment output
	//Q[7]	Q[6]	Q[5]	Q[4]	Q[3]	Q[2]	Q[1]	Q[0]
	//Dot	A		B		C		D		E		F		G
/*	always @(*) begin
		case(count)
		0: segments = 8'b01111110;
		1: segments = 8'b00110000;
		2: segments = 8'b01101101;
		3: segments = 8'b01111001; 
		4: segments = 8'b00110011;
		5: segments = 8'b01011011;
		6: segments = 8'b01011111;
		7: segments = 8'b01110000;
		8: segments = 8'b01111111;
		9: segments = 8'b01111011;
		default: segments = 8'b11111111; //should never happen
		endcase
	end
*/
	
	always @(posedge clock, negedge clear) begin
		if (clear == 0) begin
			count <= 0;
		end
		else if (enable == 1'b1) begin
			if(load == 1'b1) begin
				count <= D;
			end
			else if (up == 1'b1) begin
				//count up
				count <= (count+1 >=10)?(0):(count+1);
			end
			else begin  
				//count down
				count <= ( count == 0 )?(9):(count-1);
			end
			
		end
		else begin
			//enable == 0
			// do nothign to counter
		end
		
	end

endmodule
