
cd Z:/__SchoolWork/EE_460M_lab/lab_2/
vlib lab_2_work
vmap work ./lab_2_work

vlog divider.v


vsim -gDIVIDE_BY=2 divider

view objects
view wave

add wave clock_in clock_out

#set inputs at 0, 100, 200, etc...
#output/registers clock at 50, 150, 250, etc...
force clock_in		0 0, 1 10 -repeat 20



run 1000