webtalk_init -webtalk_dir Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.hw/webtalk/
webtalk_register_client -client project
webtalk_add_data -client project -key date_generated -value "Wed Apr 20 19:11:17 2016" -context "software_version_and_target_device"
webtalk_add_data -client project -key product_version -value "Vivado v2014.4 (64-bit)" -context "software_version_and_target_device"
webtalk_add_data -client project -key build_version -value "1071353" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_platform -value "WIN64" -context "software_version_and_target_device"
webtalk_add_data -client project -key registration_id -value "210777625_1777494353_210565950_607" -context "software_version_and_target_device"
webtalk_add_data -client project -key tool_flow -value "labtool" -context "software_version_and_target_device"
webtalk_add_data -client project -key beta -value "FALSE" -context "software_version_and_target_device"
webtalk_add_data -client project -key route_design -value "FALSE" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_family -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_device -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_package -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key target_speed -value "not_applicable" -context "software_version_and_target_device"
webtalk_add_data -client project -key random_id -value "112be7d2-2d94-47ce-9f69-92b6ed7e5c20" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_id -value "d780996f-8fdd-4ade-8a9b-2b2cbb3ad308" -context "software_version_and_target_device"
webtalk_add_data -client project -key project_iteration -value "2" -context "software_version_and_target_device"
webtalk_add_data -client project -key os_name -value "Microsoft Windows 7 , 64-bit" -context "user_environment"
webtalk_add_data -client project -key os_release -value "Service Pack 1  (build 7601)" -context "user_environment"
webtalk_add_data -client project -key cpu_name -value "Intel(R) Core(TM)2 Duo CPU     E7400  @ 2.80GHz" -context "user_environment"
webtalk_add_data -client project -key cpu_speed -value "2793 MHz" -context "user_environment"
webtalk_add_data -client project -key total_processors -value "1" -context "user_environment"
webtalk_add_data -client project -key system_ram -value "4.000 GB" -context "user_environment"
webtalk_register_client -client labtool
webtalk_add_data -client labtool -key cable -value "Digilent/Basys3/15000000" -context "labtool\\usage"
webtalk_add_data -client labtool -key chain -value "0362D093" -context "labtool\\usage"
webtalk_add_data -client labtool -key pgmcnt -value "02:00:00" -context "labtool\\usage"
webtalk_transmit -clientid 1979984858 -regid "210777625_1777494353_210565950_607" -xml Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.hw/webtalk/usage_statistics_ext_labtool.xml -html Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.hw/webtalk/usage_statistics_ext_labtool.html -wdm Z:/EE460M/Lab7_partA_lights/Lab7_partA_lights.hw/webtalk/usage_statistics_ext_labtool.wdm -intro "<H3>LABTOOL Usage Report</H3><BR>"
webtalk_terminate
