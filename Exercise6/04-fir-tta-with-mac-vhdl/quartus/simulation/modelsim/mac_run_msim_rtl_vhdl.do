transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+/home/user/04-fir-tta-with-mac-vhdl/quartus {/home/user/04-fir-tta-with-mac-vhdl/quartus/usedw_to_status.v}
vlog -vlog01compat -work work +incdir+/home/user/04-fir-tta-with-mac-vhdl/quartus {/home/user/04-fir-tta-with-mac-vhdl/quartus/start_trigger.v}
vlog -vlog01compat -work work +incdir+/home/user/04-fir-tta-with-mac-vhdl/quartus {/home/user/04-fir-tta-with-mac-vhdl/quartus/pc_init.v}
vlog -vlog01compat -work work +incdir+/home/user/04-fir-tta-with-mac-vhdl/quartus {/home/user/04-fir-tta-with-mac-vhdl/quartus/fiforeader.v}
vlog -vlog01compat -work work +incdir+/home/user/04-fir-tta-with-mac-vhdl/quartus {/home/user/04-fir-tta-with-mac-vhdl/quartus/data_src1.v}
vlog -vlog01compat -work work +incdir+/home/user/04-fir-tta-with-mac-vhdl/quartus {/home/user/04-fir-tta-with-mac-vhdl/quartus/checksum.v}
vlog -vlog01compat -work work +incdir+/home/user/04-fir-tta-with-mac-vhdl/quartus {/home/user/04-fir-tta-with-mac-vhdl/quartus/addr_gen.v}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/quartus/tiny_fifo.vhd}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/util_pkg.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/toplevel_params_pkg.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/toplevel_imem_mau_pkg.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/toplevel_globals_pkg.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/tce_util_pkg.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/mac.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/ldh_ldhu_ldq_ldqu_ldw_sth_stq_stw.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/fifo_stream_out_1.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/fifo_stream_in_1.vhd}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/input_socket_2.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/gcu_opcodes_pkg.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/quartus/dataram.vhd}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/quartus/instrom.vhd}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/toplevel.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/rf_1wr_1rd_always_1_guarded_0.vhd}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/vhdl/add_and_eq_gt_gtu_ior_shl_shr_shru_sub_sxhw_sxqw_xor.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/output_socket_2_1.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/output_socket_1_1.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/ifetch.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/idecompressor.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/ic.vhdl}
vcom -93 -work work {/home/user/04-fir-tta-with-mac-vhdl/hdl_files/gcu_ic/decoder.vhdl}

