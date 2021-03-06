# 
# Synthesis run script generated by Vivado
# 

set_param gui.test TreeTableDev
debug::add_scope template.lib 1
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000

create_project -in_memory -part xc7a35tcpg236-2L
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir Z:/__SchoolWork/EE_460M_lab/lab_1/lab_1_xilinx_project/lab_1_xilinx_project.cache/wt [current_project]
set_property parent.project_path Z:/__SchoolWork/EE_460M_lab/lab_1/lab_1_xilinx_project/lab_1_xilinx_project.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
read_verilog -library xil_defaultlib {
  Z:/__SchoolWork/EE_460M_lab/lab_1/lab_1_xilinx_project/lab_1_xilinx_project.srcs/sources_1/imports/lab_1/subtract1bit.v
  Z:/__SchoolWork/EE_460M_lab/lab_1/lab_1_xilinx_project/lab_1_xilinx_project.srcs/sources_1/imports/lab_1/subtract4bit.v
}
read_xdc Z:/__SchoolWork/EE_460M_lab/lab_1/lab_1_xilinx_project/lab_1_xilinx_project.srcs/constrs_1/imports/lab_1/ioconstraint.xdc
set_property used_in_implementation false [get_files Z:/__SchoolWork/EE_460M_lab/lab_1/lab_1_xilinx_project/lab_1_xilinx_project.srcs/constrs_1/imports/lab_1/ioconstraint.xdc]

catch { write_hwdef -file subtract4bit.hwdef }
synth_design -top subtract4bit -part xc7a35tcpg236-2L
write_checkpoint -noxdef subtract4bit.dcp
catch { report_utilization -file subtract4bit_utilization_synth.rpt -pb subtract4bit_utilization_synth.pb }
