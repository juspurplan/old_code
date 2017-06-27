
cd Z:/__SchoolWork/EE_460M_lab/lab_1/
vlib lab_1_work
vmap work ./lab_1_work

vlog ALU.v


vsim -nowlfopt -nocollapse ALU

view objects
view wave

add wave A B cb_in cb_out control out

force A			1100 0,		0011 10,	1001 20,	0001 30,	1100 40
force B			0011 0,		0100 10,	0001 20,	1000 30,	1010 40
force cb_in		1 0,		1 10,		1 20,		0 30
force control	000 0,		000 10,		001 20,		001 30,		010 40,		011 50,		100 60,		101 70,		110 80,		111 90

#				ADD			ADD			SUB			SUB			OR			AND			SH-L		SH-R		RO-L		RO-R
#exp out:		0000		1000		0111		stuff		1110		1000		1000		0110		1001		0110
#exp c/b:		1			0			0			1			0			0			0			0			0			0

run 100