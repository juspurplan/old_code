
cd Z:/__SchoolWork/EE_460M_lab/lab_2/
vlib lab_2_work
vmap work ./lab_2_work

vlog BCDCounter.v


vsim BCDCounter

view objects
view wave

add wave clock Q carry_out enable up

#set inputs at 0, 100, 200, etc...
#output/registers clock at 50, 150, 250, etc...
force clock		0 0, 1 50 -repeat 100 

#load counter with 6
force D 	0110 0
force load 	1 0,	0 100

#enable is alwasy one. Clear is always 1
force enable 1 0
force clear 1 0

#clock up 4 times, then down 2 times
force up 	1 100, 1 200, 1 300, 1 400, 0 500, 0 600

#stop, enable = 0110
force enable 0 700


#test async clear
force clear 0 700


run 900