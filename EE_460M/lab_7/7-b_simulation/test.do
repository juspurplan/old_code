
do compile.do

vsim -novopt Complete_MIPS

view objects
view wave

add wave CPUclock RST deb_swtch dp_btns CPU/pc CPU/instr CPU/state CPU/memR CPU/op  CPU/alu_in_A CPU/alu_in_B CPU/alu_result CPU/alu_result_save CPU/special_reg_HI CPU/special_reg_LO CPU/Register/REG MEM/RAM 
add wave data CPU/sevensegreg

radix signal CPU/pc unsigned
radix signal CPU/memR unsigned
radix signal CPU/state unsigned
radix signal CPU/instr hexadecimal
radix signal CPU/alu_result unsigned
radix signal CPU/Register/REG unsigned

radix signal CPU/special_reg_HI hexadecimal
radix signal CPU/special_reg_LO hexadecimal

radix signal CPU/op unsigned
radix signal CPU/alu_in_A unsigned
radix signal CPU/alu_in_B unsigned
radix signal CPU/alu_result_save unsigned

radix signal data hexadecimal



force CPUclock 0 0, 1 5 -repeat 10
force divCLK 0 0, 1 5 -repeat 10
force RST 1 0, 0 10
force deb_swtch 3'b000 10, 3'b011 400
force dp_btns 2'b 00 0, 2'b01 1000, 2'b00 1500

run 2000
