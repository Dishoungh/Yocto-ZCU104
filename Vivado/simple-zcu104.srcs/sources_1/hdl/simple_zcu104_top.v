//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.2 (lin64) Build 6299465 Fri Nov 14 12:34:56 MST 2025
//Date        : Sun Feb  1 10:54:42 2026
//Host        : localhost.localdomain running 64-bit AlmaLinux 9.7 (Moss Jungle Cat)
//Command     : generate_target simple_bd_wrapper.bd
//Design      : simple_bd_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module simple_zcu104
(
    input wire reset,
    input wire[3:0] dip_switch_4bits_tri_i,
    input wire[3:0] push_button_4bits_tri_i,
    output wire[3:0] led_4bits_tri_o
);

// Block Design Instantiation
simple_bd design_i
(
    .reset(reset),
    .dip_switch_4bits_tri_i(dip_switch_4bits_tri_i),
    .push_button_4bits_tri_i(push_button_4bits_tri_i),
    .led_4bits_tri_o(led_4bits_tri_o)    
);
endmodule
