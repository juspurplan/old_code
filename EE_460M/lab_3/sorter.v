
module sorter (weight, clock, reset, group1, group2, group3, group4, group5, group6, current_group);
	input [11:0] weight;
	input clock, reset;
	output [7:0] group1, group2, group3, group4, group5, group6;
	output [2:0] current_group;
	
	parameter GROUP1_UPPER_LIMIT = 250;
	parameter GROUP2_UPPER_LIMIT = 500;
	parameter GROUP3_UPPER_LIMIT = 750;
	parameter GROUP4_UPPER_LIMIT = 1500;
	parameter GROUP5_UPPER_LIMIT = 2000;
	// 		  GROUP6_UPPER_LIMIT = infinity
	
	
	
	// NOTES:
	// 1) reset is active high. Asynchronous
	// 2) at start, assume nothing is on the sorter. 
	// 3) registers change on falling edge of clock.
	// 4) group1 goes from [1 to GROUP1_UPPER_LIMIT] inclusive
	// 		group2 goes from [GROUP1_UPPER_LIMIT+1 to GROUP2_UPPER_LIMIT] inclusive
	// 		similarly for group3, 4, 5, 6.
	
	// RS latch to communicate when the package data (the weight) as been read.
	// latches 1: when has_package transitions 0 => 1
	// 		if we [place a package] and it has [not been read], then we [place a new package],
	// 		the old package will never be read. new_package stays latched to 1.
	// latches 0: when the package is read, and the groups are updated.
	wire new_package; 
	
	// signal that resets the new_package latch.
	reg read_package;	
	
	// groupN outputs are registered outputs.
	reg [7:0] g1, g2, g3, g4, g5, g6;
	
	// since always blocks cannot drive type net. We put it through a reg type.
	reg [2:0] cg;
	
	
	reg has_package; //= (weight == 12'b 000000000000 || weight === 12'b xxxxxxxxxxxx )?(0):(1);
	always @(*) begin
		if((weight === 12'b zzzzzzzzzzzz) || (weight == 12'd 0) ) begin
			has_package = 0;
		end
		else begin
			has_package = 1;
		end
	end
	
	// tie cg to current_group
	assign current_group = cg;
	
	//tie the registered outputs to output pins
	assign group1 = g1;
	assign group2 = g2;
	assign group3 = g3;
	assign group4 = g4;
	assign group5 = g5;
	assign group6 = g6;
	
	// latching action for new_package
	latch l0 (
		.set	(has_package & (read_package == 0 | read_package === 1'b x)),
		.reset	(read_package),
		.out	(new_package)
	);
	
	// combinational for current_group
	always @(weight) begin
		if (weight == 0) begin
			cg = 3'd 0;
		end
		else if ((weight > 0) && (weight < GROUP1_UPPER_LIMIT+1)) begin
			// in group 1
			cg = 3'd 1;
		end
		else if ((weight > GROUP1_UPPER_LIMIT) && (weight < GROUP2_UPPER_LIMIT+1)) begin
			// in group 2
			cg = 3'd 2;
		end
		else if ((weight > GROUP2_UPPER_LIMIT) && (weight < GROUP3_UPPER_LIMIT+1)) begin
			// in group 3
			cg = 3'd 3;
		end
		else if ((weight > GROUP3_UPPER_LIMIT) && (weight < GROUP4_UPPER_LIMIT+1)) begin
			// in group 4
			cg = 3'd 4;
		end
		else if ((weight > GROUP4_UPPER_LIMIT) && (weight < GROUP5_UPPER_LIMIT+1)) begin
			// in group 5
			cg = 3'd 5;
		end
		else if (weight > GROUP5_UPPER_LIMIT ) begin
			// in group 6
			cg = 3'd 6;
		end
		else begin 
			// error should never happen
			cg = 3'd 7;
		end
	end

	
	// register clocking
	always @(negedge clock, reset) begin
		if(reset == 1) begin
			// async reset
			g1 <= 0;
			g2 <= 0;
			g3 <= 0;
			g4 <= 0;
			g5 <= 0;
			g6 <= 0;
			read_package <= 0;
		end
		else begin
			// on falling edge clock. See NOTES
			if (new_package == 1) begin
				case (cg)
				3'd 0: begin end // could happen if someone places/removes packages too quickly. In this case, DO NOTHING. Counts as read the data
				3'd 1: g1 <= g1 +1;
				3'd 2: g2 <= g2 +1;
				3'd 3: g3 <= g3 +1;
				3'd 4: g4 <= g4 +1;
				3'd 5: g5 <= g5 +1;
				3'd 6: g6 <= g6 +1;
				3'd 7: begin end // should never happen
				endcase
				
				// reset the new_package latch. 
				read_package <= 1;
			end
			else begin
				g1 <= g1;
				g2 <= g2;
				g3 <= g3;
				g4 <= g4;
				g5 <= g5;
				g6 <= g6;
				
				//no new packages
				//check if package is still there
				read_package <= (has_package)?(1):(0);
			end
		end
		
		
		
	end

endmodule


module latch(set, reset, out);
	input set, reset;
	output out;
	// this is a self gated latch based on the output
	// SET and RESET signals will be gated by the output
	// this way, if out == 1, it will wait for a reset and ignore the SET.
	// 		if out == 0, it will wait for SET, and ignore RESET.
	
	//active high SET, and RESET.
	
	reg result;
	
	assign out = result;
	
	always @(set, reset) begin
		if (set == 1 && (result != 1 || result === 1'bx) )begin
			result <= 1;
		end
		else if (reset == 1 && (result != 0 || result === 1'bx) )begin
			// result == 1 case
			result <= 0;
		end
		
		
		
	end

endmodule
