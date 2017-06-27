
do compile.do

vsim -novopt -gDIVIDE_BY=10 -gDURATION=1 Divider

view objects
view wave

add wave clock_in clock_out

force clock_in 0 0, 1 5 -repeat 10

run 1000
