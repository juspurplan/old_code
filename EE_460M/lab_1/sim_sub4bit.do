
cd Z:/__SchoolWork/EE_460M_lab/lab_1/
vlib lab_1_work
vmap work ./lab_1_work

vlog subtract1bit.v
vlog subtract4bit.v


vsim -nowlfopt -nocollapse subtract4bit

view objects
view wave

add wave A B borrow_in borrow_out diff

force A			1001 0,	0011 10,	1001 20
force B			0011 0,	0110 10,	0011 20
force borrow_in	1 0,	1 10,		0 20

run 40