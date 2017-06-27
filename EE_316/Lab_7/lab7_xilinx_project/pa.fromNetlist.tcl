
# PlanAhead Launch Script for Post-Synthesis pin planning, created by Project Navigator

create_project -name lab7_xilinx_project -dir "Z:/__SchoolWork/lab7/lab7_xilinx_project/planAhead_run_2" -part xc3s1000ft256-5
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "Z:/__SchoolWork/lab7/lab7_xilinx_project/lab7.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {Z:/__SchoolWork/lab7/lab7_xilinx_project} }
set_param project.pinAheadLayout  yes
set_property target_constrs_file "lab7.ucf" [current_fileset -constrset]
add_files [list {lab7.ucf}] -fileset [get_property constrset [current_run]]
link_design
