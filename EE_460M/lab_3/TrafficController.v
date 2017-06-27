/*
Configuration 2:

Main (A) Street:
 Green: lasts 3 seconds.
 Yellow: lasts 2 seconds.
 Red: lasts 8 seconds.

Side (B) Street:
 Red: lasts 5 seconds.
 Green: lasts 3 seconds.
 Yellow: lasts 1 seconds.
 Red: lasts 4 more seconds.

Pedestrian Crossing:
 Red: lasts for 9 seconds.
 Green: lasts 2 second.
 Red: Flashes 2 seconds at 2Hz.

Maintenance mode:
 RST=1: Ra, Rb, and Rw all flash at 1Hz
 RST=0: Traffic lights should resume operation with Ga,Rb,Rw as initial state

*/


	// For street A and B
	// led[2]	led[1]	led[0]
	// Green 	Yellow 	Red
	//
	// For Pedestrian
	// led[1]	led[0]
	// Green	Red


	// #	|States					| Duration
	// ====================================
	// 0	| maintanence			| indefinite
	// 1	| Ga Rb Rw				| 3 sec
	// 2	| Ya Rb Rw				| 2 sec
	// 3	| Ra Gb Rw				| 3
	// 4	| Ra Yb Rw				| 1
	// 5	| Ra Rb Gw				| 2
	// 6	| Ra Rb Rw (flash)		| 2
	// 		| repeat from top		|

module TrafficController (clock, reset, led_a, led_b, led_walk);
	input clock, reset;
	output [2:0] led_a, led_b;
	output [1:0] led_walk;
	
	parameter CLOCK_FREQUENCY = 100000000;
	
	wire [2:0] current_state;
	wire tick;
	
	FSM fsm0 (
		.clock			(tick),
		.reset			(reset),
		.current_state	(current_state)
	);
	
	Timer #(.CLOCK_FREQUENCY(CLOCK_FREQUENCY)) time0 (
		.in_state(current_state),
		.clock(clock),
		.out_clock(tick)
	);
	
	LEDController #(.CLOCK_FREQUENCY(CLOCK_FREQUENCY)) leds (
		.current_state(current_state),
		.clock(clock),
		.led_a(led_a),
		.led_b(led_b),
		.led_walk(led_walk)
	);
	
endmodule
