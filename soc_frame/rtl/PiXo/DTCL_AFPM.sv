`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: TU Wien
// Engineer: Daniel Blattner
// 
// Create Date: 26.06.2023 09:35:05
// Design Name: Decomposition, truncation and chunk-level leading-one quantization (DTCL)
//              based multiplication approximation
// Module Name: DTCL_AFPM
// Project Name: AFPM
// Target Devices: -
// Tool Versions: -
// Description: -
// 
// Dependencies: -
// Revision:
// Revision 0.01 - File Created
// Revision 1.1 28.06.2023 - File Created
// Revision 1.2 12.07.2023 - Fixed bug with chunks being summed up
// Revision 1.3 21.07.2023 - Fixed wrong placement of multiplication result in significant
// Additional Comments: The algorithm for the approximate floating point multiplier is based on the paper by Vishesh et al. 
//                      https://ieeexplore.ieee.org/document/10129296
//
//////////////////////////////////////////////////////////////////////////////////

// import defines::*;

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


`endif




module DTCL_AFPM(
    input float32_t   fp_multiplier,
    input float32_t   fp_multiplicand,
    output float32_t  fp_product);
    
    // Number of exact bits
    parameter E = 10;
    // Number of approximate bits
    parameter A = 6;
    // Size of a chunk 
    parameter K = 2;
    // Partision of martissa
    ////////////////////////////////////////////////////
    //|  E   |      A      |             T           |//
    ////////////////////////////////////////////////////
    
    // DO NOT CHANGE THESE PARAMETER!!
    // Number of truncated bits
    parameter T = FLOAT32_SIG_WIDTH+1-E-A;
    // Number of chunks
    parameter chunk_num = A/K;
    
    parameter RESULT_WIDTH = 2*(A+E);
    
    initial begin
            $display("Current Configuration: Exact Bits: %0d Approximate Bits: %0d Chunk Size: %0d\n",E,A,K);
            assert (A%K == 0) else $display("The number of approximate bits (A) should be devisible by the size of the chunk(s) (K)\n");
    end
    
    logic multiplier_is_nan;
    logic multiplicand_is_nan;
    logic multiplier_is_inf;
    logic multiplicand_is_inf;
    logic multiplier_is_zero;
    logic multiplicand_is_zero;
    logic multiplier_hidden_bit;
    logic multiplicand_hidden_bit;
    logic mul_is_nan;
    
    assign multiplier_is_nan = fp_multiplier.exponent == 8'hff && fp_multiplier.significand != 0;
    assign multiplicand_is_nan = fp_multiplicand.exponent == 8'hff && fp_multiplicand.significand != 0;
    assign multiplier_is_inf = fp_multiplier.exponent == 8'hff && fp_multiplier.significand == 0;
    assign multiplicand_is_inf = fp_multiplicand.exponent == 8'hff && fp_multiplicand.significand == 0;
    assign multiplier_is_zero = fp_multiplier.exponent == 0 && fp_multiplier.significand == 0;
    assign multiplicand_is_zero = fp_multiplicand.exponent == 0 && fp_multiplicand.significand == 0;
    assign multiplier_hidden_bit = fp_multiplier.exponent != 0;         // 0 -> Subnormal number
    assign multiplicand_hidden_bit = fp_multiplicand.exponent != 0;
    // Result is NaN if one number is NaN or a 0.0*inf multiplication occur
    assign mul_is_nan = multiplier_is_nan || multiplicand_is_nan || 
                        (multiplier_is_zero && multiplicand_is_inf) || 
                        (multiplicand_is_zero && multiplier_is_inf);
    
    logic[FLOAT32_SIG_WIDTH:0] multiplier_full_significand;
    logic[FLOAT32_SIG_WIDTH:0] multiplicand_full_significand;
    
    assign multiplier_full_significand = {multiplier_hidden_bit,fp_multiplier.significand};
    assign multiplicand_full_significand = {multiplicand_hidden_bit,fp_multiplicand.significand};
    
    // Return the position of the first '1' from the MSB    
    // If no one was deteced the return LSB is 0 else 1
    function logic[$clog2(K):0] lob (input logic[K-1:0] chunk);
        for (int idx = K-1; idx >= 0; idx--) begin
            if(chunk[idx] == 1) begin
                return {idx,1'b1};
            end
        end
        return 0;
    endfunction;
    
    logic[E-1:0] multiplier_exact;
    logic[E-1:0] multiplicand_exact;
    logic[A-1:0] multiplier_approximate;
    logic[A-1:0] multiplicand_approximate;
    // Part of the significant, which is multiplied using an exact method
    assign multiplier_exact = multiplier_full_significand[FLOAT32_SIG_WIDTH:FLOAT32_SIG_WIDTH-E+1];
    assign multiplicand_exact = multiplicand_full_significand[FLOAT32_SIG_WIDTH:FLOAT32_SIG_WIDTH-E+1];
    // Part of the signigicant, which is multiplied using the approximate method
    // The LSB of the A-region is rounded with the MSB of the T-region
    assign multiplier_approximate = {multiplier_full_significand[FLOAT32_SIG_WIDTH-E:FLOAT32_SIG_WIDTH-E-A+2],
            multiplier_full_significand[FLOAT32_SIG_WIDTH-E-A+1] | multiplier_full_significand[FLOAT32_SIG_WIDTH-E-A]};
    assign multiplicand_approximate = {multiplicand_full_significand[FLOAT32_SIG_WIDTH-E:FLOAT32_SIG_WIDTH-E-A+2],
            multiplicand_full_significand[FLOAT32_SIG_WIDTH-E-A+1] | multiplicand_full_significand[FLOAT32_SIG_WIDTH-E-A]};
    
    logic[K-1:0] multiplier_chunks[chunk_num-1:0];
    logic[K-1:0] multiplicand_chunks[chunk_num-1:0];
    // Slice the approximate part into chunks
    always_comb begin
        for(int idx = 0; idx < chunk_num; idx++) begin
            multiplier_chunks[idx] = multiplier_approximate[K*idx +: K];
            multiplicand_chunks[idx] = multiplicand_approximate[K*idx +: K];
        end
    end
    
    logic[$clog2(K)-1:0] multiplier_chunks_quantized[chunk_num-1:0];
    logic[chunk_num-1:0] multiplier_chunks_nzero;
    logic[$clog2(K)-1:0] multiplicand_chunks_quantized[chunk_num-1:0];
    logic[chunk_num-1:0] multiplicand_chunks_nzero;
    // Get position of first '1' from each chunk
    always_comb begin
        for(int idx = 0; idx < chunk_num; idx++) begin
            {multiplier_chunks_quantized[idx],multiplier_chunks_nzero[idx]} = lob(multiplier_chunks[idx]);
            {multiplicand_chunks_quantized[idx],multiplicand_chunks_nzero[idx]} = lob(multiplicand_chunks[idx]);
        end
    end
    
    logic[A-1:0] const_1 = 1;
    logic[A-1:0] multiplier_approximate_quantized[chunk_num-1:0];
    int quantized_offset[chunk_num-1:0];
    always_comb begin
        if (multiplier_chunks_nzero[0]) begin
            multiplier_approximate_quantized[0] = const_1 << multiplier_chunks_quantized[0];
        end else begin
            multiplier_approximate_quantized[0] = {A{1'b0}};
        end
        for(int idx = 1; idx < chunk_num; idx++) begin
            quantized_offset[idx] = {{32-$clog2(K){1'b0}},multiplier_chunks_quantized[idx]} + idx*K;
            if (multiplier_chunks_nzero[idx]) begin
                multiplier_approximate_quantized[idx] = (const_1 << quantized_offset[idx])
                                                        + multiplier_approximate_quantized[idx-1];
            end else begin
                multiplier_approximate_quantized[idx] = multiplier_approximate_quantized[idx-1];
            end
        end
    end
    
    // Calculate the partial product
    // The E-region uses a accurate multiplier
    // The combined region uses a shit and add method 
    logic[(2*E)-1:0] prod_exact;
    logic[(A+E)-1:0] prod_exact_approximate1[chunk_num-1:0];
    logic[(A+E)-1:0] prod_exact_approximate2[chunk_num-1:0];
    logic[(2*A)-1:0] prod_approximated[chunk_num-1:0];
    int base_offset[chunk_num-1:0];
    int multiplicand_offset[chunk_num-1:0];
    int multiplier_offset[chunk_num-1:0];
    always_comb begin
        prod_exact = multiplier_exact*multiplicand_exact;
        // Reduce the chunk-array
        // Final result is in the last position (index chunk_num-1)
        if (multiplicand_chunks_nzero[0]) begin
            prod_exact_approximate1[0] = {{A{1'b0}},multiplier_exact} << multiplicand_chunks_quantized[0];
            prod_approximated[0] = {{A{1'b0}},multiplier_approximate_quantized[chunk_num-1]} << multiplicand_chunks_quantized[0];
        end else begin
            prod_exact_approximate1[0] = {A+E{1'b0}};
            prod_approximated[0] = {2*A{1'b0}};
        end
        if (multiplier_chunks_nzero[0]) begin
            prod_exact_approximate2[0] = {{A{1'b0}},multiplicand_exact} << multiplier_chunks_quantized[0];
        end else begin
            prod_exact_approximate2[0] = {A+E{1'b0}};
        end

        for(int idx = 1; idx < chunk_num; idx++) begin
            // Thanks verilator ( ?? ???)
            base_offset[idx] = idx*K;
            multiplicand_offset[idx] = {{32-$clog2(K){1'b0}},multiplicand_chunks_quantized[idx]} + base_offset[idx];
            multiplier_offset[idx] = {{32-$clog2(K){1'b0}},multiplier_chunks_quantized[idx]} + base_offset[idx];
            if (multiplicand_chunks_nzero[idx]) begin
                prod_exact_approximate1[idx] = ({{A{1'b0}},multiplier_exact} << (multiplicand_offset[idx][A+E-1:0])) + 
                                                prod_exact_approximate1[idx-1];
                prod_approximated[idx] = ({{A{1'b0}},multiplier_approximate_quantized[chunk_num-1]} << (multiplicand_offset[idx][(2*A)-1:0])) + 
                                        prod_approximated[idx-1];                                
            end else begin
                prod_exact_approximate1[idx] = prod_exact_approximate1[idx-1];
                prod_approximated[idx] = prod_approximated[idx-1];
            end
            if (multiplier_chunks_nzero[idx]) begin
                prod_exact_approximate2[idx] = ({{A{1'b0}},multiplicand_exact} << (multiplier_offset[idx][A+E-1:0])) +
                                                prod_exact_approximate2[idx-1];
            end else begin
                prod_exact_approximate2[idx] = prod_exact_approximate2[idx-1];
            end
        end
    end
    
    /*always_comb begin
        prod_exact = multiplier_exact*multiplicand_exact;
        // Reduce the chunk-array
        // Final result is in the last position (index chunk_num-1)
        if (multiplicand_chunks_nzero[0]) begin
            prod_exact_approximate1[0] = multiplier_exact << multiplicand_chunks_quantized[0];
            prod_approximated[0] = multiplier_approximate << multiplicand_chunks_quantized[0];
        end else begin
            prod_exact_approximate1[0] = {A+E{1'b0}};
            prod_approximated[0] = {2*A{1'b0}};
        end
        if (multiplier_chunks_nzero[0]) begin
            prod_exact_approximate2[0] = multiplicand_exact << multiplier_chunks_quantized[0];
        end else begin
            prod_exact_approximate2[0] = {A+E{1'b0}};
        end
        for(int idx = 1; idx < chunk_num; idx++) begin
            if (multiplicand_chunks_nzero[idx]) begin
                prod_exact_approximate1[idx] = multiplier_exact << (multiplicand_chunks_quantized[idx] + idx*K) + 
                                                prod_exact_approximate1[idx-1];
                prod_approximated[idx] = multiplier_approximate << (multiplicand_chunks_quantized[idx] + idx*K) + 
                                        prod_approximated[idx-1];                                
            end else begin
                prod_exact_approximate1[idx] = prod_exact_approximate1[idx-1];
                prod_approximated[idx] = prod_approximated[idx-1];
            end
            if (multiplier_chunks_nzero[idx]) begin
                prod_exact_approximate2[idx] = multiplicand_exact << (multiplier_chunks_quantized[idx] + idx*K) +
                                                prod_exact_approximate2[idx-1];
            end else begin
                prod_exact_approximate2[idx] = prod_exact_approximate2[idx-1];
            end
        end
    end*/
    
    logic[RESULT_WIDTH-1:0] mul_product;
    logic mul_exponent_cin;
    logic[FLOAT32_EXP_WIDTH-1:0] mul_exponent;
    logic mul_exponent_underflow;
    logic mul_exponent_carry;

    always_comb begin
    
        // Calculate the combined product of the martissa
        mul_product = (prod_exact << 2*A) + 
                    ((prod_exact_approximate1[chunk_num-1] + prod_exact_approximate2[chunk_num-1]) << A) + 
                    (prod_approximated[chunk_num-1]);
        // Normalize matrissa
        if (mul_product[RESULT_WIDTH-1] == 1'b1) begin
            mul_exponent_cin = 1'b1;
        end else begin
            mul_exponent_cin = 1'b0;
        end
        // Calculation of the exponent
        {mul_exponent_underflow, mul_exponent_carry, mul_exponent}
                = {2'd0, fp_multiplier.exponent} + {2'd0, fp_multiplicand.exponent} - 10'd127 + mul_exponent_cin; 
        
        // Result handeling
        if (mul_is_nan) begin
            // Internal NaN encoding
            fp_product.sign = 1'b0;
            fp_product.exponent = 8'hff;
            fp_product.significand = 23'h7FFFFF;
        end else begin
            // Sign bit
            fp_product.sign = fp_multiplier.sign ^ fp_multiplicand.sign;
            if (mul_exponent_underflow || multiplier_is_zero || multiplicand_is_zero) begin
                // Result is zero
                fp_product.exponent = 8'h0;
                fp_product.significand = 23'h0;
            end else begin
                if (mul_exponent_carry) begin
                    // Result is inf
                    fp_product.exponent = 8'hff;
                    fp_product.significand = 23'h0;
                end else begin
                    // Result of approximation
                    fp_product.exponent = mul_exponent;
                    // Normalize matrissa
                    // Result of multiplication can be bigger or smaller than the significant
                    // Therefore both cases must be handeled
                    if (mul_product[2*(A+E)-1]) begin
                        if (2*(A+E)-1 >= FLOAT32_SIG_WIDTH) begin
                            fp_product.significand = mul_product[2*(A+E)-2:2*(A+E)-2-(FLOAT32_SIG_WIDTH-1)]; 
                        end else begin
                            fp_product.significand = {mul_product[2*(A+E)-2:0],'0}; 
                        end
                    end else begin
                        if (2*(A+E)-2 >= FLOAT32_SIG_WIDTH) begin
                            fp_product.significand = mul_product[2*(A+E)-3:2*(A+E)-3-(FLOAT32_SIG_WIDTH-1)];
                        end else begin
                            fp_product.significand = {mul_product[2*(A+E)-3:0],'0};
                        end
                    end
                end
            end
        end
    end

endmodule
