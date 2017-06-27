
cd Z:/__SchoolWork/EE_460M_lab/lab_1/
vlib lab_1_work
vmap work ./lab_1_work

vlog subtract1bit.v


vsim -nowlfopt -nocollapse subtract1bit

view objects
view wave

add wave A B borrow_in borrow_out diff

force A			0 0,	1 5,	0 10,	1 15,	0 20,	1 25,	0 30,	1 35
force B			0 0,	0 5,	1 10,	1 15,	0 20, 	0 25,	1 30, 	1 35
force borrow_in	0 0,	0 5,	0 10,	0 15,	1 20,	1 25,	1 30, 	1 35

run 40