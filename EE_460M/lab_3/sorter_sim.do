
cd Z:/__SchoolWork/EE_460M_lab/lab_3/
vlib lab_3_work
vmap work ./lab_3_work

#compile
vlog -novopt sorter.v

#simulate
vsim -novopt sorter

view objects
view wave

add wave clock reset
add wave weight current_group group1 group2 group3 group4 group5 group6
radix signal current_group unsigned
radix signal weight unsigned
radix signal group1 unsigned
radix signal group2 unsigned
radix signal group3 unsigned
radix signal group4 unsigned
radix signal group5 unsigned
radix signal group6 unsigned

add wave has_package new_package read_package

force clock 1 0, 0 5 -repeat 10
force reset 1 0, 0 3

#inputs: reset -> 270 -> 0 -> 300 -> 0 -> 501 -> 1013 -> 0 -> 753 -> 0 -> 330 -> reset -> 990 -> 0 -> 2157 -> 0 -> 1318 -> 0 -> 1973
force weight 100001110 33, 0 53, 100101100 63, 0 73, 111110101 83, 1111110101 93, 0 95, 1011110001 100, 0 110, 101001010 120, 0 140, 1111011110 150, 0 160, 100001101101 170, 0 180, 10100100110 190, 0 200, 11110110101 210

#reset at t = 130
force reset 1 130, 0 133



run 400