
module LEDController (current_state, clock, led_a, led_b, led_walk);
	input [2:0] current_state;
	input clock;
	output [2:0] led_a, led_b;
	output [1:0] led_walk;
	
	parameter CLOCK_FREQUENCY = 10000000;
	
	wire reduced_clock_1Hz;
	wire reduced_clock_2Hz;
	reg [2:0] led_a_out;
	reg [2:0] led_b_out;
	reg [1:0] led_walk_out;
	
	assign led_a = led_a_out;
	assign led_b = led_b_out;
	assign led_walk = led_walk_out;
	
	divider #(.DIVIDE_BY(CLOCK_FREQUENCY)) div0 (
		.clock_in (clock),
		.clock_out (reduced_clock_1Hz)
	);
	
	divider #(.DIVIDE_BY(CLOCK_FREQUENCY/2)) div1 (
		.clock_in (clock),
		.clock_out (reduced_clock_2Hz)
	);
	
	always @(*) begin
		case(current_state)
		3'd 0: begin // maintainence
			led_a_out = {1'b 0, 1'b 0, 1'b 1 & reduced_clock_1Hz};
			led_b_out = {1'b 0, 1'b 0, 1'b 1 & reduced_clock_1Hz};
			led_walk_out = {1'b 0, 1'b 1 & reduced_clock_1Hz};
		end
		3'd 1: begin // Ga Rb Rw
			led_a_out = 3'b 100;
			led_b_out = 3'b 001;
			led_walk_out = 2'b 01;
		end
		3'd 2: begin // Ya Rb Rw
			led_a_out = 3'b 010;
			led_b_out = 3'b 001;
			led_walk_out = 2'b 01;
		end
		3'd 3: begin // Ra Gb Rw
			led_a_out = 3'b 001;
			led_b_out = 3'b 100;
			led_walk_out = 2'b 01;
		end
		3'd 4: begin // Ra Yb Rw
			led_a_out = 3'b 001;
			led_b_out = 3'b 010;
			led_walk_out = 2'b 01;
		end
		3'd 5: begin // Ra Rb Gw
			led_a_out = 3'b 001;
			led_b_out = 3'b 001;
			led_walk_out = 2'b 10;
		end
		3'd 6: begin // Ra Rb Rw (flash)
			led_a_out = 3'b 001;
			led_b_out = 3'b 001;
			led_walk_out = {1'b 0, 1'b 1 & reduced_clock_2Hz};
		end
		3'd 7: begin // unused state. should never occur.
			led_a_out = 3'b 111;
			led_b_out = 3'b 111;
			led_walk_out = 2'b 11;
		end
		endcase
		
	end
	
endmodule
