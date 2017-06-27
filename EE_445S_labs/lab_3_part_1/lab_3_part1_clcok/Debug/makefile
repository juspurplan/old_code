################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/c6000_7.4.14

ORDERED_OBJS += \
"./FIRmono_ISRs.obj" \
"./LCDK_Support_DSP.obj" \
"./StartUp.obj" \
"./coeff.obj" \
"./main.obj" \
"./vectors.obj" \
"../link6748.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
lab_3_part1_clcok.out \

EXE_OUTPUTS__QUOTED += \
"lab_3_part1_clcok.out" \

BIN_OUTPUTS += \
lab_3_part1_clcok.hex \

BIN_OUTPUTS__QUOTED += \
"lab_3_part1_clcok.hex" \


# All Target
all: lab_3_part1_clcok.out

# Tool invocations
lab_3_part1_clcok.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv6740 --abi=coffabi -g --display_error_number --diag_warning=225 --diag_wrap=off -z -m"lab_3_part1_clcok.map" -i"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/lib" -i"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="lab_3_part1_clcok_linkInfo.xml" --rom_model -o "lab_3_part1_clcok.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

lab_3_part1_clcok.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C6000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/hex6x"  -o "lab_3_part1_clcok.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "FIRmono_ISRs.pp" "LCDK_Support_DSP.pp" "StartUp.pp" "coeff.pp" "main.pp" 
	-$(RM) "FIRmono_ISRs.obj" "LCDK_Support_DSP.obj" "StartUp.obj" "coeff.obj" "main.obj" "vectors.obj" 
	-$(RM) "vectors.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

