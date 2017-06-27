// combinational circuit to get new code
module ChangeCode(shift_reg, enable_check, enable_change);
	input [21:0] shift_reg;
	input enable_check;
	output enable_change;

	reg enable_change;

	always @(*)
	begin
		if(enable_check == 1'b 1)
		  begin
		    if (shift_reg[20:13] == 8'h 0F)
		      begin
			  enable_change = 1'b 1;
		      end
		    else
		      begin
			  enable_change = 1'b 0;
		      end
	      end
	    else
	      begin
	       enable_change = 1'b 0;
	      end
	end
endmodule