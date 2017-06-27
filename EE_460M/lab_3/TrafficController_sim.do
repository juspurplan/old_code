
cd Z:/__SchoolWork/EE_460M_lab/lab_3/
vlib lab_3_work
vmap work ./lab_3_work

#compile
vlog -novopt divider.v
vlog -novopt Timer.v
vlog -novopt FSM.v
vlog -novopt LEDController.v
vlog -novopt TrafficController.v

#simulate
vsim -novopt -gCLOCK_FREQUENCY=8 TrafficController

view objects
view wave

add wave clock reset tick current_state time0/count led_a led_b led_walk
radix signal current_state unsigned
radix signal time0/count unsigned

force clock 1 0, 0 5 -repeat 10

force reset 1 0, 0 500


run 2000