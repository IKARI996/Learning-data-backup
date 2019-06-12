set prj_name "MIPS_CPU"
set prj_path "../prj"

create_project $prj_name $prj_path -part xc7a35tcpg236-1 -force

set_property ip_repo_paths ../IPCatalog [current_fileset]
update_ip_catalog

create_bd_design "MIPS_CPU"

################################################################
# This is a generated script based on design: MIPS_CPU
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################
################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source MIPS_CPU_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7a35tcpg236-1


# CHANGE DESIGN NAME HERE
set design_name MIPS_CPU

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}


# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "ERROR: Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      puts "INFO: Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   puts "INFO: Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   puts "INFO: Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   puts $errMsg
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set alu_pinout [ create_bd_port -dir O -from 31 -to 0 alu_pinout ]
  set clk [ create_bd_port -dir I clk ]
  set data_pinout [ create_bd_port -dir O -from 31 -to 0 data_pinout ]
  set inst_pinout [ create_bd_port -dir O -from 31 -to 0 inst_pinout ]
  set pc_pinout [ create_bd_port -dir O -from 31 -to 0 pc_pinout ]
  set restet [ create_bd_port -dir I restet ]

  # Create instance: ALU32_0, and set properties
  set ALU32_0 [ create_bd_cell -type ip -vlnv dtysky:XUP:ALU32:1.0 ALU32_0 ]

  # Create instance: CONTROL_UNIT_0, and set properties
  set CONTROL_UNIT_0 [ create_bd_cell -type ip -vlnv dtysky:XUP:CONTROL_UNIT:1.0 CONTROL_UNIT_0 ]

  # Create instance: DATAPATH_0, and set properties
  set DATAPATH_0 [ create_bd_cell -type ip -vlnv dtysky:XUP:DATAPATH:1.2 DATAPATH_0 ]

  # Create instance: DATA_MEM_0, and set properties
  set DATA_MEM_0 [ create_bd_cell -type ip -vlnv dtysky:XUP:DATA_MEM:1.0 DATA_MEM_0 ]

  # Create instance: INST_MEM_0, and set properties
  set INST_MEM_0 [ create_bd_cell -type ip -vlnv dtysky:XUP:INST_MEM:1.1 INST_MEM_0 ]

  # Create instance: REGFILE_0, and set properties
  set REGFILE_0 [ create_bd_cell -type ip -vlnv dtysky:XUP:REGFILE:1.0 REGFILE_0 ]

  # Create instance: clk_wiz_0, and set properties
  set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:5.1 clk_wiz_0 ]
  set_property -dict [ list CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {100} CONFIG.CLKOUT2_USED {false}  ] $clk_wiz_0

  # Create port connections
  connect_bd_net -net ALU32_0_r [get_bd_ports alu_pinout] [get_bd_pins ALU32_0/r] [get_bd_pins DATAPATH_0/alu_r]
  connect_bd_net -net ALU32_0_z [get_bd_pins ALU32_0/z] [get_bd_pins DATAPATH_0/alu_z]
  connect_bd_net -net CONTROL_UNIT_0_aluc [get_bd_pins CONTROL_UNIT_0/aluc] [get_bd_pins DATAPATH_0/con_aluc]
  connect_bd_net -net CONTROL_UNIT_0_aluimm [get_bd_pins CONTROL_UNIT_0/aluimm] [get_bd_pins DATAPATH_0/con_aluimm]
  connect_bd_net -net CONTROL_UNIT_0_jal [get_bd_pins CONTROL_UNIT_0/jal] [get_bd_pins DATAPATH_0/con_jal]
  connect_bd_net -net CONTROL_UNIT_0_m2reg [get_bd_pins CONTROL_UNIT_0/m2reg] [get_bd_pins DATAPATH_0/con_m2reg]
  connect_bd_net -net CONTROL_UNIT_0_pcsource [get_bd_pins CONTROL_UNIT_0/pcsource] [get_bd_pins DATAPATH_0/con_pcsource]
  connect_bd_net -net CONTROL_UNIT_0_regrt [get_bd_pins CONTROL_UNIT_0/regrt] [get_bd_pins DATAPATH_0/con_regrt]
  connect_bd_net -net CONTROL_UNIT_0_sext [get_bd_pins CONTROL_UNIT_0/sext] [get_bd_pins DATAPATH_0/con_sext]
  connect_bd_net -net CONTROL_UNIT_0_shfit [get_bd_pins CONTROL_UNIT_0/shfit] [get_bd_pins DATAPATH_0/con_shfit]
  connect_bd_net -net CONTROL_UNIT_0_wmem [get_bd_pins CONTROL_UNIT_0/wmem] [get_bd_pins DATAPATH_0/con_wmem]
  connect_bd_net -net CONTROL_UNIT_0_wreg [get_bd_pins CONTROL_UNIT_0/wreg] [get_bd_pins DATAPATH_0/con_wreg]
  connect_bd_net -net DATAPATH_0_alu_a [get_bd_pins ALU32_0/a] [get_bd_pins DATAPATH_0/alu_a]
  connect_bd_net -net DATAPATH_0_alu_aluc [get_bd_pins ALU32_0/aluc] [get_bd_pins DATAPATH_0/alu_aluc]
  connect_bd_net -net DATAPATH_0_alu_b [get_bd_pins ALU32_0/b] [get_bd_pins DATAPATH_0/alu_b]
  connect_bd_net -net DATAPATH_0_con_func [get_bd_pins CONTROL_UNIT_0/func] [get_bd_pins DATAPATH_0/con_func]
  connect_bd_net -net DATAPATH_0_con_op [get_bd_pins CONTROL_UNIT_0/op] [get_bd_pins DATAPATH_0/con_op]
  connect_bd_net -net DATAPATH_0_con_z [get_bd_pins CONTROL_UNIT_0/z] [get_bd_pins DATAPATH_0/con_z]
  connect_bd_net -net DATAPATH_0_data_a [get_bd_pins DATAPATH_0/data_a] [get_bd_pins DATA_MEM_0/addr]
  connect_bd_net -net DATAPATH_0_data_di [get_bd_pins DATAPATH_0/data_di] [get_bd_pins DATA_MEM_0/data_in]
  connect_bd_net -net DATAPATH_0_data_we [get_bd_pins DATAPATH_0/data_we] [get_bd_pins DATA_MEM_0/we]
  connect_bd_net -net DATAPATH_0_inst_a [get_bd_pins DATAPATH_0/inst_a] [get_bd_pins INST_MEM_0/a]
  connect_bd_net -net DATAPATH_0_pc_out [get_bd_ports pc_pinout] [get_bd_pins DATAPATH_0/pc_out]
  connect_bd_net -net DATAPATH_0_reg_d [get_bd_pins DATAPATH_0/reg_d] [get_bd_pins REGFILE_0/d]
  connect_bd_net -net DATAPATH_0_reg_rna [get_bd_pins DATAPATH_0/reg_rna] [get_bd_pins REGFILE_0/rna]
  connect_bd_net -net DATAPATH_0_reg_rnb [get_bd_pins DATAPATH_0/reg_rnb] [get_bd_pins REGFILE_0/rnb]
  connect_bd_net -net DATAPATH_0_reg_we [get_bd_pins DATAPATH_0/reg_we] [get_bd_pins REGFILE_0/we]
  connect_bd_net -net DATAPATH_0_reg_wn [get_bd_pins DATAPATH_0/reg_wn] [get_bd_pins REGFILE_0/wn]
  connect_bd_net -net DATA_MEM_0_data_out [get_bd_ports data_pinout] [get_bd_pins DATAPATH_0/data_do] [get_bd_pins DATA_MEM_0/data_out]
  connect_bd_net -net INST_MEM_0_inst_out [get_bd_ports inst_pinout] [get_bd_pins DATAPATH_0/inst_do] [get_bd_pins INST_MEM_0/inst_out]
  connect_bd_net -net REGFILE_0_qa [get_bd_pins DATAPATH_0/reg_qa] [get_bd_pins REGFILE_0/qa]
  connect_bd_net -net REGFILE_0_qb [get_bd_pins DATAPATH_0/reg_qb] [get_bd_pins REGFILE_0/qb]
  connect_bd_net -net clk_1 [get_bd_ports clk] [get_bd_pins clk_wiz_0/clk_in1]
  connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_pins DATAPATH_0/clk] [get_bd_pins DATA_MEM_0/clk] [get_bd_pins REGFILE_0/clk] [get_bd_pins clk_wiz_0/clk_out1]
  connect_bd_net -net restet_1 [get_bd_ports restet] [get_bd_pins DATAPATH_0/clrn] [get_bd_pins REGFILE_0/clrn]

  # Create address segments
  

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""

generate_target {synthesis implementation} [get_files $prj_path/$prj_name.srcs/sources_1/bd/MIPS_CPU/MIPS_CPU.bd]

make_wrapper -files [get_files $prj_path/$prj_name.srcs/sources_1/bd/MIPS_CPU/MIPS_CPU.bd] -top
import_files -force -norecurse -fileset sources_1 $prj_path/$prj_name.srcs/sources_1/bd/MIPS_CPU/hdl/MIPS_CPU_wrapper.v
set_property top design_1_wrapper [current_fileset]
import_files -force -norecurse -fileset sim_1 ../Sim/MIPS_CPU_TB.sv
update_compile_order -fileset sim_1
update_compile_order -fileset sources_1

launch_simulation
run -all