# create modelsim working library
vlib work

# compile all the Verilog sources
vlog   ../../testbench/testbench_adder.v  ../../alu/*.v  ../../alu/adder/*.v  

# open the testbench module for simulation
vsim -novopt work.testbench_adder

# add signals to time diagram
add wave sim:/testbench_adder/*
add wave sim:/testbench_adder/DUT_alu/adder_l_en
add wave sim:/testbench_adder/DUT_alu/adder_h_en
add wave sim:/testbench_adder/DUT_alu/shift_code
add wave sim:/testbench_adder/DUT_alu/shift_arg
add wave sim:/testbench_adder/DUT_alu/shift_value
add wave sim:/testbench_adder/DUT_alu/shift_carry_in
add wave sim:/testbench_adder/DUT_alu/result_out
add wave sim:/testbench_adder/DUT_alu/shift_en
add wave sim:/testbench_adder/DUT_alu/shift_rdy
add wave sim:/testbench_adder/DUT_alu/shift_res
# run the simulation
run -all

# expand the signals time diagram
wave zoom full