

#compile
do compile.do

#simulate
vsim -novopt BCDTo7Segment

view objects
view wave

add wave bcd segments

#tests
force bcd 4'd0 0, 4'd1 10, 4'd2 20, 4'd3 30, 4'd4 40, 4'd5 50, 4'd6 60, 4'd7 70, 4'd8 80, 4'd9 90, 4'd10 100


run 500