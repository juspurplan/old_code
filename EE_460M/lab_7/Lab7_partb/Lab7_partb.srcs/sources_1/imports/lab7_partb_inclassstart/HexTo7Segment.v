module HexTo7Segment(hex, segments);
	input [3:0] hex;
	output [6:0] segments;

	reg [6:0] result, segments;
	
	initial begin
	   segments = 7'b 0000000;
	end
	
	// 7 segment
	// 7	6	5	4	3	2	1	0
	// A	B	C	D	E	F	G	dot
	always @(*) begin
		case (hex)
		4'd 0: result = 7'b 1111110;
		4'd 1: result = 7'b 0110000;
		4'd 2: result = 7'b 1101101;
		4'd 3: result = 7'b 1111001;
		4'd 4: result = 7'b 0110011;
		4'd 5: result = 7'b 1011011;
		4'd 6: result = 7'b 1011111;
		4'd 7: result = 7'b 1110000;
		4'd 8: result = 7'b 1111111;
		4'd 9: result = 7'b 1110011;
		4'h A: result = 7'b 1110111;
		4'h B: result = 7'b 0011111;
		4'h C: result = 7'b 1001110;
		4'h D: result = 7'b 0111101;
		4'h E: result = 7'b 1001111;
		4'h F: result = 7'b 1000111;
		//default:  result = 7'b 1111111;	// should never happen
		endcase
	end
            
    always @(result) begin
        segments = result;
    end
endmodule