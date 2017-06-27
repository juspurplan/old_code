
# PlanAhead Launch Script for Post-Synthesis pin planning, created by Project Navigator

create_project -name EE316_lab3a -dir "Z:/__SchoolWork/EE316_lab3a/planAhead_run_3" -part xc3s1000ft256-5
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "Z:/__SchoolWork/EE316_lab3a/EE316_lab2_circuit_vhdl.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {Z:/__SchoolWork/EE316_lab3a} }
set_param project.pinAheadLayout  yes
set_property target_constrs_file "EE316_lab2_circuit_vhdl.ucf" [current_fileset -constrset]
add_files [list {EE316_lab2_circuit_vhdl.ucf}] -fileset [get_property constrset [current_run]]
link_design
