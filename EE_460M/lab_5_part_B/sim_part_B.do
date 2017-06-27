
do compile.do

vsim -novopt PartB


view objects
view wave

add wave update_clock switches color R G B hsync vsync disp0/hcount disp0/vcount
radix signal color hex
radix signal R unsigned
radix signal G unsigned
radix signal B unsigned
radix signal disp0/hcount unsigned
radix signal disp0/vcount unsigned

#clock
force clock 0 0, 1 5 -repeat 10


force switches 8'b00100000 500

run 50000000
