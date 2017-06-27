
module BCDTo7Segment(bcd, segments);
	input [3:0] bcd;
	output [7:0] segments;
	
	reg [7:0] result;
	
	assign segments = result;
	
	// 7 segment
	// 7	6	5	4	3	2	1	0
	// A	B	C	D	E	F	G	dot
	always @(*) begin
		case (bcd)
		4'd 0: result = 8'b 11111100;
		4'd 1: result = 8'b 01100000;
		4'd 2: result = 8'b 11011010;
		4'd 3: result = 8'b 11110010;
		4'd 4: result = 8'b 01100110;
		4'd 5: result = 8'b 10110110;
		4'd 6: result = 8'b 10111110;
		4'd 7: result = 8'b 11100000;
		4'd 8: result = 8'b 11111110;
		4'd 9: result = 8'b 11100110;
		default:  result = 8'b 11111111; // should never happen
		endcase
	end
	
endmodule
