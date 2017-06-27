
module GameState(clock, in, x_coord_in, y_coord_in, pixel_color_out, state_out);
	input clock;
	input [3:0] in;
	input  [31:0] x_coord_in, y_coord_in;
	output [11:0] pixel_color_out;
	output [2:0] state_out;
	
	parameter SNAKE_MAX_LENGTH = 60;
	parameter SNAKE_DEFAULT_LENGTH = 20;
	parameter SNAKE_LENGTH_INC = 1;
	
	parameter SNAKE_MAX_SPEED = 5;
	parameter SNAKE_DEFAULT_SPEED = 1;
	parameter SNAKE_SPEED_INC = 1;
	
	parameter SNAKE_SEGMENT_SIZE = 10;
	parameter SNAKE_START_X = 0;
	parameter SNAKE_START_Y = 100;
	parameter SNAKE_START_DIR = 1;
	
	parameter TICKS_BEFORE_INC = 300;
	
	
	// Inputs
	// 0: no input
	// 1: start
	// 2: end
	// 3: pause
	// 4: resume
	// 5: up
	// 6: right
	// 7: down
	// 8: left
	// 9 to 15 : unused.
	
	// direction
	// 0: up
	// 1: right
	// 2: down
	// 3: left
	reg [1:0] direction;	
	integer x [0:SNAKE_MAX_LENGTH-1];
	integer y [0:SNAKE_MAX_LENGTH-1];
	integer speed;
	integer length;			
	
	integer tick_count;
	
	reg [2:0] state;
	// Game States
	// 0: Black Screen - default
	// 1: Init - auto transition to running
	// 2: Running
	// 3: Paused
	// 4: Game Over (super pause)
	// 5 to 7 unused.
		// DEBUG
	assign state_out = state;
	
	reg [11:0] pixel_out;
	assign pixel_color_out = pixel_out;
	
	always @(posedge clock) begin : game_state_update
		integer i;
		
		case(state) 
		0: begin // BLACK SCREEN
			// Do Nothing,
			// Check for Start Game
			direction <= direction;
			for(i = 0; i <SNAKE_MAX_LENGTH; i = i+1) begin
				x[i] <= x[i];
				y[i] <= y[i];
			end
			speed <= speed;
			length <= length;
			tick_count <= tick_count;
			
			case(in)
			1: begin // start
				state <= 1;
			end
			default: begin // othe rinputs
				state <= 0;
			end
			endcase
		end
		
		1: begin // INIT
			speed <= SNAKE_DEFAULT_SPEED;
			length <= SNAKE_DEFAULT_LENGTH;
			direction <= SNAKE_START_DIR[1:0];
			
			for(i = 0; i < SNAKE_MAX_LENGTH; i = i + 1) begin
				x[i] <= SNAKE_START_X;
				y[i] <= SNAKE_START_Y;
			end
			
			tick_count <= TICKS_BEFORE_INC;
			
			state <= 2;
		end
		
		2: begin :running_state // RUNNING 
			// check for collisions
			reg has_boundary_collision;
			has_boundary_collision = 0;
			if (x[0] < 0 || x[0] >= 640 || y[0] < 0 || y[0] >= 480) begin
				has_boundary_collision = 1;
			end
			
			// check tick_count
			if(tick_count == 0) begin
				tick_count <= TICKS_BEFORE_INC;
				speed <= (speed >= SNAKE_MAX_SPEED)?(speed):(speed + SNAKE_SPEED_INC);
				length <= (length >= SNAKE_MAX_LENGTH)?(length):(length + SNAKE_LENGTH_INC);
			end
			else begin
				tick_count <= tick_count -1;
				speed <= speed;
				length <= length;
			end
			
			// shift old positions, for positions >= length, just copy over, since they are invalid
			for (i = 1; i < SNAKE_MAX_LENGTH; i = i +1) begin
				x[i] <= x[i -1];
				y[i] <= y[i -1];
			end
			
			// calculate new current positions
			case(direction)
			0: begin // UP
				x[0] <= x[0];
				y[0] <= y[0] - speed;
			end
			1: begin // RIGHT
				x[0] <= x[0] + speed;
				y[0] <= y[0];
			end
			2: begin // DOWN
				x[0] <= x[0];
				y[0] <= y[0] + speed;
			end
			3: begin // LEFT
				x[0] <= x[0] - speed;
				y[0] <= y[0];
			end
			endcase
			
			// check for pause, end game, and start game.
			// check inputs and alter direction
			case(in)
			1: begin // start
				state <= 1;
			end
			2: begin // end
				state <= 0;
			end
			3: begin // pause
				state <= 3;
			end
			5: begin // up
				state <= 2;
				direction <= (direction == 0 || direction == 2)?(direction):(0);
			end
			6: begin // right
				state <= 2;
				direction <= (direction == 1 || direction == 3)?(direction):(1);
			end
			7: begin // down
				state <= 2;
				direction <= (direction == 0 || direction == 2)?(direction):(2);
			end
			8: begin // left
				state <= 2;
				direction <= (direction == 1 || direction == 3)?(direction):(3);
			end
			default: begin
				if(has_boundary_collision == 1) begin
					state <= 4;
				end
				else begin
					state <= 2;
				end
				direction <= direction;
			end
			endcase
			
		end
		
		3: begin // PAUSED				
			// Do nothing.
			// Check for Resume, End Game, New Game, 
			direction <= direction;
			for(i = 0; i<SNAKE_MAX_LENGTH; i = i+1) begin
				x[i] <= x[i];
				y[i] <= y[i];
			end
			speed <= speed;
			length <= length;
			tick_count <= tick_count;
			
			case(in)
			1: begin // start
				state <= 1;
			end
			2:begin // end
				state <= 0;
			end
			4: begin // resume
				state <= 2;
			end
			default: begin // other input
				state <= 3;
			end
			endcase
		end
	
		4: begin // GAME Over
			// do nothing. only start does something.
			// TODO.. add in inputs
			direction <= direction;
			for(i = 0; i<SNAKE_MAX_LENGTH; i = i+1) begin
				x[i] <= x[i];
				y[i] <= y[i];
			end
			speed <= speed;
			length <= length;
			tick_count <= tick_count;
			case(in)
			1: begin // start
				state <= 1;
			end
			2: begin //end
				state <= 0;
			end
			default: begin // other input
				state <= 4;
			end
			endcase
		end
		default: begin // default state.. should never happen.
			// if this someho happens, go to BLACK SCREEN.
			speed <= SNAKE_DEFAULT_SPEED;
			length <= SNAKE_DEFAULT_LENGTH;
			
			for(i = 0; i < SNAKE_MAX_LENGTH; i = i +1) begin
				x[i] <= SNAKE_START_X;
				y[i] <= SNAKE_START_Y;
			end
			direction <= 2'd 1;
			
			tick_count <= TICKS_BEFORE_INC;
			
			state <= 0;
		end
		endcase
	end
	
	
	// combinational logic to render to screen
	// depends on current state, and x_coord_in, y_coord_in.
	always @(*) begin : render
		integer j;
	
		case(state)
		0: begin // BLACK SCREEN state
			//DEBUG: i use white for now to see if things work.
			pixel_out = 12'h 000;
		end
		1: begin // Init state
			pixel_out = 12'h 000;
		end
		
		// States 2, 3, 4 (Run, Puase, Game Over) and unused states all do the same rendering
		// Draw the game board.
		// snake green 		12'h 060;
		// background brown 12'h 841;
		default: begin
			pixel_out = 12'h FFF;
			for(j = 0; j < SNAKE_MAX_LENGTH; j = j +1) begin
				// edit: changed loop condition to a static parameter
				// then added "j < length" condition to if to ignore the indices we dont want
				if(j < length && x[j]<=x_coord_in && x_coord_in<=x[j]+SNAKE_SEGMENT_SIZE && y[j]<=y_coord_in && y_coord_in<=y[j]+SNAKE_SEGMENT_SIZE) begin
					pixel_out = 12'h 00C;
				end
			end
		end
		endcase
	end

endmodule
