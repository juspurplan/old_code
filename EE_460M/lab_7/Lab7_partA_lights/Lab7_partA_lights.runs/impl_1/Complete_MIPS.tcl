proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000

start_step init_design
set rc [catch {
  create_msg_db init_design.pb
  set_param gui.test TreeTableDev
  set_param xicom.use_bs_reader 1
  debug::add_scope template.lib 1
  set_property design_mode GateLvl [current_fileset]
  set_property webtalk.parent_dir Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.cache/wt [current_project]
  set_property parent.project_path Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.xpr [current_project]
  set_property ip_repo_paths z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.cache/ip [current_project]
  set_property ip_output_repo z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.cache/ip [current_project]
  add_files -quiet Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.runs/synth_1/Complete_MIPS.dcp
  read_xdc Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.srcs/constrs_1/imports/Downloads/Basys3_Master.xdc
  link_design -top Complete_MIPS -part xc7a35tcpg236-1
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
}

start_step opt_design
set rc [catch {
  create_msg_db opt_design.pb
  catch {write_debug_probes -quiet -force debug_nets}
  opt_design 
  write_checkpoint -force Complete_MIPS_opt.dcp
  catch {report_drc -file Complete_MIPS_drc_opted.rpt}
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
}

start_step place_design
set rc [catch {
  create_msg_db place_design.pb
  place_design 
  write_checkpoint -force Complete_MIPS_placed.dcp
  catch { report_io -file Complete_MIPS_io_placed.rpt }
  catch { report_clock_utilization -file Complete_MIPS_clock_utilization_placed.rpt }
  catch { report_utilization -file Complete_MIPS_utilization_placed.rpt -pb Complete_MIPS_utilization_placed.pb }
  catch { report_control_sets -verbose -file Complete_MIPS_control_sets_placed.rpt }
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
}

start_step route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force Complete_MIPS_routed.dcp
  catch { report_drc -file Complete_MIPS_drc_routed.rpt -pb Complete_MIPS_drc_routed.pb }
  catch { report_timing_summary -warn_on_violation -max_paths 10 -file Complete_MIPS_timing_summary_routed.rpt -rpx Complete_MIPS_timing_summary_routed.rpx }
  catch { report_power -file Complete_MIPS_power_routed.rpt -pb Complete_MIPS_power_summary_routed.pb }
  catch { report_route_status -file Complete_MIPS_route_status.rpt -pb Complete_MIPS_route_status.pb }
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
}

start_step write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  write_bitstream -force Complete_MIPS.bit 
  if { [file exists Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.runs/synth_1/Complete_MIPS.hwdef] } {
    catch { write_sysdef -hwdef Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.runs/synth_1/Complete_MIPS.hwdef -bitfile Complete_MIPS.bit -meminfo Complete_MIPS.mmi -file Complete_MIPS.sysdef }
  }
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
}
