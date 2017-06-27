
do compile.do

#altering clock frequency to 640 so we see internal state changes every 2 cycles 
#the divider cannot divide by 1.. minimum is divide by 2
vsim -novopt -gCLOCK_FREQUENCY=640 SevenSegmentDisplayController

view objects
view wave

add wave clock reduced_clock bcd3 bcd2 bcd1 bcd0 commons segments fsm0/current_state
radix signal bcd3 unsigned
radix signal bcd2 unsigned
radix signal bcd1 unsigned
radix signal bcd0 unsigned
radix signal fsm0/current_state unsigned

force clock 0 0, 1 5 -repeat 10
force bcd3 4'd1 0
force bcd2 4'd2 0
force bcd1 4'd3 0
force bcd0 4'd4 0

run 500