
cd Z:/__SchoolWork/EE_460M_lab/lab_2/
vlib lab_2_work
vmap work ./lab_2_work

vlog excess3_dataflow.v


vsim excess3_dataflow

view objects
view wave

add wave X S V clock

#set inputs at 0, 100, 200, etc...
#output/registers clock at 50, 150, 250, etc...
force clock		0 0, 1 50 -repeat 100 

#X = 1011 1100 1101   Least Significan Bit first (rightmost)
force X			1 0, 0 100, 1 200, 1 300,		0 400, 0 500, 1 600, 1 700, 		1 800, 1 900, 0 1000, 1 1100





#expected:
#S (sum)		0    0     0     0 (10000)      1      1      1      1 (1111)       0      1      1       1 (1110) 
#V (overflow)   0    0     0     1              0      0      0      0              0      0      0       0


run 1200