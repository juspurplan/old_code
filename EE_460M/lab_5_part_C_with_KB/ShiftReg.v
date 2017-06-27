module ShiftReg(clk, shift_in, reg_value, read);
	input clk, shift_in;
	output [21:0] reg_value;
	output read;

	reg [21:0] reg_value;
	reg [5:0] cnt;
	reg read;
	
	initial begin
	   cnt = 6'd 1;
	end

	always @(negedge clk)
	begin
		reg_value = reg_value << 1;
		reg_value[0] = shift_in;
		if(cnt == 6'd 11)
		  begin
		      cnt = 6'd 1;
		      read = 1'b 1;
		  end
	    else
          begin
              cnt = (cnt + 6'd 1);
              read = 1'b 0;
          end
	end
endmodule