
module ALU (A, B, cb_in, control, out, cb_out);
	input [3:0] A,B;
	input cb_in;
	input [2:0] control;
	output [3:0] out;
	output cb_out;
	
	wire [3:0] add_result, sub_result, or_result, and_result, 
		shl_result, shr_result, rol_result, ror_result;
	wire add_overflow, sub_underflow;
	
	reg cb_result;
	reg [3:0] result;
	
	assign {add_overflow, add_result} = A + B + cb_in;
	assign {sub_underflow, sub_result} = A - B - cb_in;
	assign or_result = A | B;
	assign and_result = A & B;
	assign shl_result = {A[2:0], 1'b0};
	assign shr_result = {1'b0, A[3:1]};
	assign rol_result = {A[2:0], A[3]};
	assign ror_result = {A[0], A[3:1]};
	
	assign out = result;
	assign cb_out = cb_result;
	
	//serves to multiplex ALU results based on control
	//also assigns the correct cb_result
	always @(*)
	begin
		case(control)
		3'b000:
			result <= add_result;
		3'b001:
			result <= sub_result;
		3'b010:
			result <= or_result;
		3'b011:
			result <= and_result;
		3'b100:
			result <= shl_result;
		3'b101:
			result <= shr_result;
		3'b110:
			result <= rol_result;
		3'b111:
			result <= ror_result;

		endcase
		
		if( control[2:1] == 2'b00) begin//checks if ALU is doing an ADD or SUB
			if (control[0] == 1'b0) begin
				cb_result <= add_overflow;
			end else begin
				cb_result <= sub_underflow;
			end
		end
		else begin
			cb_result <= 1'b0;
		end
		
		
	end

endmodule
