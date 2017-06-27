
cd Z:/__SchoolWork/EE_460M_lab/lab_3/
vlib lab_3_work
vmap work ./lab_3_work

#compile
vlog sorter.v
vlog sorter_testbench.v

#simulate
vsim sorter_testbench

#view objects
#view wave

#add wave clock g1 g2 g3 g4 g5 g6 cg

radix signal g1 d 
radix signal g2 d
radix signal g3 d
radix signal g4 d
radix signal g5 d
radix signal g6 d
radix signal cg d


run 2000

#vcd2wlf sorter_testbench_sim.vcd sorter_testbench_sim.wlf
#open sorter_testbench_sim.wlf