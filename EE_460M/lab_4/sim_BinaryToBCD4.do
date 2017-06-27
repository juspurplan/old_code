

#compile
do compile.do

#simulate
vsim -novopt BinaryToBCD4

view objects
view wave

add wave num bcd3 bcd2 bcd1 bcd0
radix signal num unsigned

#tests
force num 14'd9999 0, 14'd1234 10, 14'd5678 20


run 500