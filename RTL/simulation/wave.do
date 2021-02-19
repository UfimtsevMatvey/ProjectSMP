onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /testbench/DUT_clk
add wave -noupdate /testbench/DUT_rst
add wave -noupdate /testbench/DUT_en
add wave -noupdate /testbench/DUT_a
add wave -noupdate /testbench/DUT_b
add wave -noupdate /testbench/DUT_sum
add wave -noupdate /testbench/DUT_rdy
add wave -noupdate /testbench/DUT_adder/reg_data/rst
add wave -noupdate /testbench/DUT_adder/reg_data/clk
add wave -noupdate /testbench/DUT_adder/reg_data/en
add wave -noupdate /testbench/DUT_adder/reg_data/d
add wave -noupdate /testbench/DUT_adder/reg_data/q
add wave -noupdate /testbench/DUT_adder/reg_sum/rst
add wave -noupdate /testbench/DUT_adder/reg_sum/clk
add wave -noupdate /testbench/DUT_adder/reg_sum/en
add wave -noupdate /testbench/DUT_adder/reg_sum/d
add wave -noupdate /testbench/DUT_adder/reg_sum/q
add wave -noupdate /testbench/DUT_adder/reg_stage0/rst
add wave -noupdate /testbench/DUT_adder/reg_stage0/clk
add wave -noupdate /testbench/DUT_adder/reg_stage0/en
add wave -noupdate /testbench/DUT_adder/reg_stage0/d
add wave -noupdate /testbench/DUT_adder/reg_stage0/q
add wave -noupdate /testbench/DUT_adder/reg_stage1/rst
add wave -noupdate /testbench/DUT_adder/reg_stage1/clk
add wave -noupdate /testbench/DUT_adder/reg_stage1/en
add wave -noupdate /testbench/DUT_adder/reg_stage1/d
add wave -noupdate /testbench/DUT_adder/reg_stage1/q
add wave -noupdate /testbench/DUT_adder/reg_stage2/rst
add wave -noupdate /testbench/DUT_adder/reg_stage2/clk
add wave -noupdate /testbench/DUT_adder/reg_stage2/en
add wave -noupdate /testbench/DUT_adder/reg_stage2/d
add wave -noupdate /testbench/DUT_adder/reg_stage2/q
add wave -noupdate /testbench/DUT_adder/reg_stage3/rst
add wave -noupdate /testbench/DUT_adder/reg_stage3/clk
add wave -noupdate /testbench/DUT_adder/reg_stage3/en
add wave -noupdate /testbench/DUT_adder/reg_stage3/d
add wave -noupdate /testbench/DUT_adder/reg_stage3/q
add wave -noupdate /testbench/DUT_adder/reg_stage4/rst
add wave -noupdate /testbench/DUT_adder/reg_stage4/clk
add wave -noupdate /testbench/DUT_adder/reg_stage4/en
add wave -noupdate /testbench/DUT_adder/reg_stage4/d
add wave -noupdate /testbench/DUT_adder/reg_stage4/q
add wave -noupdate /testbench/DUT_adder/reg_stage5/rst
add wave -noupdate /testbench/DUT_adder/reg_stage5/clk
add wave -noupdate /testbench/DUT_adder/reg_stage5/en
add wave -noupdate /testbench/DUT_adder/reg_stage5/d
add wave -noupdate /testbench/DUT_adder/reg_stage5/q
add wave -noupdate /testbench/DUT_adder/reg_stage6/rst
add wave -noupdate /testbench/DUT_adder/reg_stage6/clk
add wave -noupdate /testbench/DUT_adder/reg_stage6/en
add wave -noupdate /testbench/DUT_adder/reg_stage6/d
add wave -noupdate /testbench/DUT_adder/reg_stage6/q
add wave -noupdate /testbench/DUT_adder/reg_stage7/rst
add wave -noupdate /testbench/DUT_adder/reg_stage7/clk
add wave -noupdate /testbench/DUT_adder/reg_stage7/en
add wave -noupdate /testbench/DUT_adder/reg_stage7/d
add wave -noupdate /testbench/DUT_adder/reg_stage7/q
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {36773 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 280
configure wave -valuecolwidth 262
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {118096 ps}
