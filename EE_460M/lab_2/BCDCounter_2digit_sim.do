
cd Z:/__SchoolWork/EE_460M_lab/lab_2/
vlib lab_2_work
vmap work ./lab_2_work

vlog BCDCounter.v
vlog BCDCounter_2digit.v


vsim BCDCounter_2digit

view objects
view wave

add wave clock Q0 Q1 up enable carry_out

#set inputs at 0, 100, 200, etc...
#output/registers clock at 50, 150, 250, etc...
force clock		0 0, 1 50 -repeat 100 

#				x 0,		x 100,		x 200,		x 300,		x 400,		x 500,		x 600,		x 700,		x 800,		x 900,		x 1000,		x 1100

#load counter with 97
force D0 		0111 0
force D1		1001 0
force load 		1 0,		0 100

#clear = 1 during oepration
force clear 	1 0

#enable = 1 during operation
force enable	1 0


#increment 4 times
force up					1 100

#do nothing 2 times
force enable																0 500

#decrement 2 times
force enable																						1 700
force up																							0 700

#clear
force enable																												0 900
force clear																																			0 1100



run 1200