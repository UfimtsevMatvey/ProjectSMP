# create modelsim working library
vlib work

# compile all the Verilog sources
vlog   ../../testbench/testbench_adder.v  ../../alu/*.v  ../../alu/adder/*.v  

# open the testbench module for simulation
vsim -novopt work.testbench_adder

# add all testbench signals to time diagram
add wave sim:/testbench_adder/*

# run the simulation
run -all

# expand the signals time diagram
wave zoom full