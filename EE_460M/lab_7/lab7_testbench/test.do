
vlib ./work

vlog -novopt lab7.v

vsim -novopt MIPS_Testbench


add wave CLK MEM/RAM WE

run 10000
