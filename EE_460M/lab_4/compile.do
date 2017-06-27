
vlib lab_4_work
vmap work ./lab_4_work

#compile
vlog -novopt Divider.v
vlog -novopt TimeLeft.v
vlog -novopt BinaryToBCD4.v
vlog -novopt BCDTo7Segment.v
vlog -novopt DisplayFSM.v
vlog -novopt SevenSegmentDisplayController.v
vlog -novopt debouncer_singlepulser.v

vlog -novopt ParkingMeter.v
