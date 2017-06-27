
do compile.do

vsim -novopt Complete_MIPS

view objects
view wave

add wave CPUclock RST leds CPU/pc CPU/instr CPU/state CPU/R1 CPU/op CPU/opsave CPU/alu_in_A CPU/alu_in_B CPU/alu_result CPU/alu_result_save CPU/Register/REG MEM/RAM 
radix signal CPU/pc unsigned
radix signal CPU/R1 unsigned
radix signal CPU/state unsigned
radix signal CPU/instr hexadecimal
radix signal CPU/alu_result unsigned
radix signal CPU/Register/REG unsigned

radix signal CPU/op unsigned
radix signal CPU/opsave unsigned 
radix signal CPU/alu_in_A unsigned
radix signal CPU/alu_in_B unsigned
radix signal CPU/alu_result_save unsigned


force CPUclock 0 0, 1 5 -repeat 10
force divCLK 0 0, 1 5 -repeat 10
force RST 1 0, 0 10

run 1000
