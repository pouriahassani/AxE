`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: TU Wien
// Engineer: Daniel Blattner
// 
// Create Date: 12.05.2023 08:56:30
// Design Name: -
// Module Name: Defines for constants and structs
// Project Name: AFPM
// Target Devices: - 
// Tool Versions: -
// Description: -
// 
// Dependencies: -
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

`ifndef __DEFINES_SV
`define __DEFINES_SV

package defines;

    //
    // Floating point types
    //
    
    parameter FLOAT32_EXP_WIDTH = 8;
    parameter FLOAT32_SIG_WIDTH = 23;
    
    // IEEE 754 Binary 32 encoding
    typedef struct packed {
        logic sign;
        logic[FLOAT32_EXP_WIDTH - 1:0] exponent;
        logic[FLOAT32_SIG_WIDTH - 1:0] significand;
    } float32_t;

endpackage

`endif
