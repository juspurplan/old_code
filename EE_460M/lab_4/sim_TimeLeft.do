
#compile
do compile.do

#simulate
vsim -novopt TimeLeft

view objects
view wave

add wave clock reset10 reset205 decrement add50 add150 add200 add500 count calculate_time/temp
radix signal count unsigned
radix signal calculate_time/temp unsigned

#set up clock 
force clock 0 0, 1 5 -repeat 10

#initialize inputs to 0
force reset10 0 0
force reset205 0 0
force decrement 0 0
force add50 0 0
force add150 0 0
force add200 0 0
force add500 0 0

#test reset10, and decrememnt, and no negative underflow
force reset10 1 0, 0 10
force decrement 1 10, 0 119

#test reset205 and adding everything
force reset205 1 120
force decrement 1 120
force add50 1 120
force add150 1 120
force add200 1 120
force add500 1 120

#test both resets together..turn off resetn then keep adding everything
force reset10 1 140
force reset10 0 150
force reset205 0 150

#turn off adds, keep decrementing
force add50 0 180
force add150 0 180
force add200 0 180
force add500 0 180

#do each add 1 at a time, keep decrementing
force add50 1 190, 0 200
force add150 1 210, 0 220
force add200 1 230, 0 240
force add500 1 250, 0 260

#reset to 10, wait until decrememnt to 0
#then add 2 at a time
force reset10 1 280, 0 290
force add50 1 390, 0 400
force add500 1 390, 0 400
force add50 1 410, 0 420
force add150 1 410, 0 420


run 500