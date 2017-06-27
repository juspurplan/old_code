
cd Z:/__SchoolWork/EE_460M_lab/lab_3/
vlib lab_3_work
vmap work ./lab_3_work

#compile
vlog sorter.v

#simulate
vsim latch

view objects
view wave

add wave set reset out

force set		1 1,	1 10,	0 20,	1 30
force reset		0 1,	1 10,	1 20,	1 30 

run 100