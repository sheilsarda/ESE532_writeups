Part 1 console output

```
Starting C simulation ...
/opt/Xilinx/Vitis/2020.1/bin/vitis_hls /home/centos/ESE532_Projects/hw5/hw5_project/solution1/csim.tcl
INFO: [HLS 200-10] Running '/opt/Xilinx/Vitis/2020.1/bin/unwrapped/lnx64.o/vitis_hls'
INFO: [HLS 200-10] For user 'centos' on host 'ip-172-31-77-247.ec2.internal' (Linux_x86_64 version 3.10.0-1127.10.1.el7.x86_64) on Thu Oct 15 16:38:55 UTC 2020
INFO: [HLS 200-10] On os "CentOS Linux release 7.7.1908 (Core)"
INFO: [HLS 200-10] In directory '/home/centos/ESE532_Projects/hw5'
Sourcing Tcl script '/home/centos/ESE532_Projects/hw5/hw5_project/solution1/csim.tcl'
INFO: [HLS 200-10] Opening project '/home/centos/ESE532_Projects/hw5/hw5_project'.
INFO: [HLS 200-10] Adding design file 'hls/MatrixMultiplication.cpp' to the project
INFO: [HLS 200-10] Adding design file 'hls/MatrixMultiplication.h' to the project
INFO: [HLS 200-10] Adding test bench file 'hls/Testbench.cpp' to the project
INFO: [HLS 200-10] Opening solution '/home/centos/ESE532_Projects/hw5/hw5_project/solution1'.
INFO: [SYN 201-201] Setting up clock 'default' with a period of 10ns.
INFO: [HLS 200-10] Setting target device to 'xcvu9p-flgb2104-2-i'
INFO: [HLS 200-1505] Using flow_target 'vitis'
Resolution: For help on HLS 200-1505 see www.xilinx.com/html_docs/xilinx2020_1/hls-guidance/200-1505.html
INFO: [HLS 200-435] Setting 'config_flow -target' configuration: config_interface -m_axi_latency=64
INFO: [HLS 200-435] Setting 'config_flow -target' configuration: config_interface -m_axi_alignment_byte_size=64
INFO: [HLS 200-435] Setting 'config_flow -target' configuration: config_interface -m_axi_max_widen_bitwidth=512
INFO: [HLS 200-435] Setting 'config_flow -target' configuration: config_interface -default_slave_interface=s_axilite
INFO: [HLS 200-435] Setting 'config_flow -target' configuration: config_rtl -register_reset_num=3
INFO: [HLS 200-1464] Running solution command: config_compile -dump_cfg=false
INFO: [HLS 200-1464] Running solution command: config_compile -name_max_length=80
INFO: [XFORM 203-1161] The maximum of name length is set into 80.
INFO: [HLS 200-1464] Running solution command: config_compile -no_signed_zeros=false
INFO: [XFORM 203-1172] Optimizing floating point zeros and discarding its signedness.
INFO: [XFORM 203-1161] The maximum of name length is set into 80.
INFO: [HLS 200-1464] Running solution command: config_compile -pipeline_loops=0
INFO: [XFORM 203-1171] Pipeline the innermost loop with trip count more than 0 or its parent loop when its trip count is less than or equal 0.
INFO: [XFORM 203-1172] Optimizing floating point zeros and discarding its signedness.
INFO: [XFORM 203-1161] The maximum of name length is set into 80.
INFO: [HLS 200-1464] Running solution command: config_compile -pipeline_style=stp
INFO: [XFORM 203-1171] Pipeline the innermost loop with trip count more than 0 or its parent loop when its trip count is less than or equal 0.
INFO: [XFORM 203-1172] Optimizing floating point zeros and discarding its signedness.
INFO: [XFORM 203-1161] The maximum of name length is set into 80.
INFO: [HLS 200-1464] Running solution command: config_compile -pragma_strict_mode=false
INFO: [XFORM 203-1171] Pipeline the innermost loop with trip count more than 0 or its parent loop when its trip count is less than or equal 0.
INFO: [XFORM 203-1172] Optimizing floating point zeros and discarding its signedness.
INFO: [XFORM 203-1161] The maximum of name length is set into 80.
INFO: [HLS 200-1464] Running solution command: config_compile -unsafe_math_optimizations=false
INFO: [XFORM 203-1171] Pipeline the innermost loop with trip count more than 0 or its parent loop when its trip count is less than or equal 0.
INFO: [XFORM 203-1172] Optimizing floating point zeros and discarding its signedness.
INFO: [XFORM 203-1173] Reordering floating point operations aggressively.
INFO: [XFORM 203-1176] Optimizing floating point comparison without checking NaN.
INFO: [XFORM 203-1161] The maximum of name length is set into 80.
INFO: [SYN 201-201] Setting up clock 'default' with a period of 10ns.
INFO: [XFORM 203-1171] Pipeline the innermost loop with trip count more than 0 or its parent loop when its trip count is less than or equal 0.
INFO: [XFORM 203-1172] Optimizing floating point zeros and discarding its signedness.
INFO: [XFORM 203-1173] Reordering floating point operations aggressively.
INFO: [XFORM 203-1176] Optimizing floating point comparison without checking NaN.
INFO: [XFORM 203-1161] The maximum of name length is set into 80.
INFO: [SIM 211-2] *************** CSIM start ***************
INFO: [SIM 211-4] CSIM will launch GCC as the compiler.
   Compiling ../../../../hls/Testbench.cpp in debug mode
   Compiling ../../../../hls/MatrixMultiplication.cpp in debug mode
   Generating csim.exe
TEST PASSED
INFO: [SIM 211-1] CSim done with 0 errors.
INFO: [SIM 211-3] *************** CSIM finish ***************
Finished C simulation.

```

