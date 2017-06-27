
do compile.do

vsim -novopt SinglePulser

view objects
view wave

add wave CLK PINPUT PULINPUT

force CLK 0 0, 1 5 -repeat 10
force PINPUT 0 0, 1 23, 0 50, 1 77, 0 113

run 200