
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name Lab5-manual -dir "Z:/__SchoolWork/EE316_Lab5/lab5-part 2/Lab5-manual/planAhead_run_3" -part xc3s1000ft256-5
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "Z:/__SchoolWork/EE316_Lab5/lab5-part 2/Lab5-manual/lab5_manual.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {Z:/__SchoolWork/EE316_Lab5/lab5-part 2/Lab5-manual} }
set_property target_constrs_file "lab5_manual.ucf" [current_fileset -constrset]
add_files [list {lab5_manual.ucf}] -fileset [get_property constrset [current_run]]
link_design
