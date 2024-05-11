module DTCL_AFPM (
	fp_multiplier,
	fp_multiplicand,
	fp_product
);
	reg _sv2v_0;
	localparam FLOAT32_EXP_WIDTH = 8;
	localparam FLOAT32_SIG_WIDTH = 23;
	input wire [31:0] fp_multiplier;
	input wire [31:0] fp_multiplicand;
	output reg [31:0] fp_product;
	parameter E = 10;
	parameter A = 6;
	parameter K = 2;
	parameter T = (24 - E) - A;
	parameter chunk_num = A / K;
	parameter RESULT_WIDTH = 2 * (A + E);
	//initial $display("Current Configuration: Exact Bits: %0d Approximate Bits: %0d Chunk Size: %0d\n", E, A, K);
	wire multiplier_is_nan;
	wire multiplicand_is_nan;
	wire multiplier_is_inf;
	wire multiplicand_is_inf;
	wire multiplier_is_zero;
	wire multiplicand_is_zero;
	wire multiplier_hidden_bit;
	wire multiplicand_hidden_bit;
	wire mul_is_nan;
	assign multiplier_is_nan = (fp_multiplier[30-:8] == 8'hff) && (fp_multiplier[22-:FLOAT32_SIG_WIDTH] != 0);
	assign multiplicand_is_nan = (fp_multiplicand[30-:8] == 8'hff) && (fp_multiplicand[22-:FLOAT32_SIG_WIDTH] != 0);
	assign multiplier_is_inf = (fp_multiplier[30-:8] == 8'hff) && (fp_multiplier[22-:FLOAT32_SIG_WIDTH] == 0);
	assign multiplicand_is_inf = (fp_multiplicand[30-:8] == 8'hff) && (fp_multiplicand[22-:FLOAT32_SIG_WIDTH] == 0);
	assign multiplier_is_zero = (fp_multiplier[30-:8] == 0) && (fp_multiplier[22-:FLOAT32_SIG_WIDTH] == 0);
	assign multiplicand_is_zero = (fp_multiplicand[30-:8] == 0) && (fp_multiplicand[22-:FLOAT32_SIG_WIDTH] == 0);
	assign multiplier_hidden_bit = fp_multiplier[30-:8] != 0;
	assign multiplicand_hidden_bit = fp_multiplicand[30-:8] != 0;
	assign mul_is_nan = ((multiplier_is_nan || multiplicand_is_nan) || (multiplier_is_zero && multiplicand_is_inf)) || (multiplicand_is_zero && multiplier_is_inf);
	wire [FLOAT32_SIG_WIDTH:0] multiplier_full_significand;
	wire [FLOAT32_SIG_WIDTH:0] multiplicand_full_significand;
	assign multiplier_full_significand = {multiplier_hidden_bit, fp_multiplier[22-:FLOAT32_SIG_WIDTH]};
	assign multiplicand_full_significand = {multiplicand_hidden_bit, fp_multiplicand[22-:FLOAT32_SIG_WIDTH]};
	function [$clog2(K):0] lob;
		input reg [K - 1:0] chunk;
		reg [0:1] _sv2v_jump;
		begin
			_sv2v_jump = 2'b00;
			begin : sv2v_autoblock_1
				reg signed [31:0] idx;
				begin : sv2v_autoblock_2
					reg signed [31:0] _sv2v_value_on_break;
					for (idx = K - 1; idx >= 0; idx = idx - 1)
						if (_sv2v_jump < 2'b10) begin
							_sv2v_jump = 2'b00;
							if (chunk[idx] == 1) begin
								lob = {idx, 1'b1};
								_sv2v_jump = 2'b11;
							end
							_sv2v_value_on_break = idx;
						end
					if (!(_sv2v_jump < 2'b10))
						idx = _sv2v_value_on_break;
					if (_sv2v_jump != 2'b11)
						_sv2v_jump = 2'b00;
				end
			end
			if (_sv2v_jump == 2'b00) begin
				lob = 0;
				_sv2v_jump = 2'b11;
			end
		end
	endfunction
	wire [E - 1:0] multiplier_exact;
	wire [E - 1:0] multiplicand_exact;
	wire [A - 1:0] multiplier_approximate;
	wire [A - 1:0] multiplicand_approximate;
	assign multiplier_exact = multiplier_full_significand[FLOAT32_SIG_WIDTH:(FLOAT32_SIG_WIDTH - E) + 1];
	assign multiplicand_exact = multiplicand_full_significand[FLOAT32_SIG_WIDTH:(FLOAT32_SIG_WIDTH - E) + 1];
	assign multiplier_approximate = {multiplier_full_significand[FLOAT32_SIG_WIDTH - E:((FLOAT32_SIG_WIDTH - E) - A) + 2], multiplier_full_significand[((FLOAT32_SIG_WIDTH - E) - A) + 1] | multiplier_full_significand[(FLOAT32_SIG_WIDTH - E) - A]};
	assign multiplicand_approximate = {multiplicand_full_significand[FLOAT32_SIG_WIDTH - E:((FLOAT32_SIG_WIDTH - E) - A) + 2], multiplicand_full_significand[((FLOAT32_SIG_WIDTH - E) - A) + 1] | multiplicand_full_significand[(FLOAT32_SIG_WIDTH - E) - A]};
	reg [K - 1:0] multiplier_chunks [chunk_num - 1:0];
	reg [K - 1:0] multiplicand_chunks [chunk_num - 1:0];
	always @(*) begin
		if (_sv2v_0)
			;
		begin : sv2v_autoblock_3
			reg signed [31:0] idx;
			for (idx = 0; idx < chunk_num; idx = idx + 1)
				begin
					multiplier_chunks[idx] = multiplier_approximate[K * idx+:K];
					multiplicand_chunks[idx] = multiplicand_approximate[K * idx+:K];
				end
		end
	end
	reg [$clog2(K) - 1:0] multiplier_chunks_quantized [chunk_num - 1:0];
	reg [chunk_num - 1:0] multiplier_chunks_nzero;
	reg [$clog2(K) - 1:0] multiplicand_chunks_quantized [chunk_num - 1:0];
	reg [chunk_num - 1:0] multiplicand_chunks_nzero;
	always @(*) begin
		if (_sv2v_0)
			;
		begin : sv2v_autoblock_4
			reg signed [31:0] idx;
			for (idx = 0; idx < chunk_num; idx = idx + 1)
				begin
					{multiplier_chunks_quantized[idx], multiplier_chunks_nzero[idx]} = lob(multiplier_chunks[idx]);
					{multiplicand_chunks_quantized[idx], multiplicand_chunks_nzero[idx]} = lob(multiplicand_chunks[idx]);
				end
		end
	end
	reg [A - 1:0] const_1 = 1;
	reg [A - 1:0] multiplier_approximate_quantized [chunk_num - 1:0];
	reg signed [31:0] quantized_offset [chunk_num - 1:0];
	always @(*) begin
		if (_sv2v_0)
			;
		if (multiplier_chunks_nzero[0])
			multiplier_approximate_quantized[0] = const_1 << multiplier_chunks_quantized[0];
		else
			multiplier_approximate_quantized[0] = {A {1'b0}};
		begin : sv2v_autoblock_5
			reg signed [31:0] idx;
			for (idx = 1; idx < chunk_num; idx = idx + 1)
				begin
					quantized_offset[idx] = {{32 - $clog2(K) {1'b0}}, multiplier_chunks_quantized[idx]} + (idx * K);
					if (multiplier_chunks_nzero[idx])
						multiplier_approximate_quantized[idx] = (const_1 << quantized_offset[idx]) + multiplier_approximate_quantized[idx - 1];
					else
						multiplier_approximate_quantized[idx] = multiplier_approximate_quantized[idx - 1];
				end
		end
	end
	reg [(2 * E) - 1:0] prod_exact;
	reg [(A + E) - 1:0] prod_exact_approximate1 [chunk_num - 1:0];
	reg [(A + E) - 1:0] prod_exact_approximate2 [chunk_num - 1:0];
	reg [(2 * A) - 1:0] prod_approximated [chunk_num - 1:0];
	reg signed [31:0] base_offset [chunk_num - 1:0];
	reg signed [31:0] multiplicand_offset [chunk_num - 1:0];
	reg signed [31:0] multiplier_offset [chunk_num - 1:0];
	always @(*) begin
		if (_sv2v_0)
			;
		prod_exact = multiplier_exact * multiplicand_exact;
		if (multiplicand_chunks_nzero[0]) begin
			prod_exact_approximate1[0] = {{A {1'b0}}, multiplier_exact} << multiplicand_chunks_quantized[0];
			prod_approximated[0] = {{A {1'b0}}, multiplier_approximate_quantized[chunk_num - 1]} << multiplicand_chunks_quantized[0];
		end
		else begin
			prod_exact_approximate1[0] = {A + E {1'b0}};
			prod_approximated[0] = {2 * A {1'b0}};
		end
		if (multiplier_chunks_nzero[0])
			prod_exact_approximate2[0] = {{A {1'b0}}, multiplicand_exact} << multiplier_chunks_quantized[0];
		else
			prod_exact_approximate2[0] = {A + E {1'b0}};
		begin : sv2v_autoblock_6
			reg signed [31:0] idx;
			for (idx = 1; idx < chunk_num; idx = idx + 1)
				begin
					base_offset[idx] = idx * K;
					multiplicand_offset[idx] = {{32 - $clog2(K) {1'b0}}, multiplicand_chunks_quantized[idx]} + base_offset[idx];
					multiplier_offset[idx] = {{32 - $clog2(K) {1'b0}}, multiplier_chunks_quantized[idx]} + base_offset[idx];
					if (multiplicand_chunks_nzero[idx]) begin
						prod_exact_approximate1[idx] = ({{A {1'b0}}, multiplier_exact} << multiplicand_offset[idx][(A + E) - 1:0]) + prod_exact_approximate1[idx - 1];
						prod_approximated[idx] = ({{A {1'b0}}, multiplier_approximate_quantized[chunk_num - 1]} << multiplicand_offset[idx][(2 * A) - 1:0]) + prod_approximated[idx - 1];
					end
					else begin
						prod_exact_approximate1[idx] = prod_exact_approximate1[idx - 1];
						prod_approximated[idx] = prod_approximated[idx - 1];
					end
					if (multiplier_chunks_nzero[idx])
						prod_exact_approximate2[idx] = ({{A {1'b0}}, multiplicand_exact} << multiplier_offset[idx][(A + E) - 1:0]) + prod_exact_approximate2[idx - 1];
					else
						prod_exact_approximate2[idx] = prod_exact_approximate2[idx - 1];
				end
		end
	end
	reg [RESULT_WIDTH - 1:0] mul_product;
	reg mul_exponent_cin;
	reg [7:0] mul_exponent;
	reg mul_exponent_underflow;
	reg mul_exponent_carry;
	always @(*) begin
		if (_sv2v_0)
			;
		mul_product = ((prod_exact << (2 * A)) + ((prod_exact_approximate1[chunk_num - 1] + prod_exact_approximate2[chunk_num - 1]) << A)) + prod_approximated[chunk_num - 1];
		if (mul_product[RESULT_WIDTH - 1] == 1'b1)
			mul_exponent_cin = 1'b1;
		else
			mul_exponent_cin = 1'b0;
		{mul_exponent_underflow, mul_exponent_carry, mul_exponent} = (({2'd0, fp_multiplier[30-:8]} + {2'd0, fp_multiplicand[30-:8]}) - 10'd127) + mul_exponent_cin;
		if (mul_is_nan) begin
			fp_product[31] = 1'b0;
			fp_product[30-:8] = 8'hff;
			fp_product[22-:FLOAT32_SIG_WIDTH] = 23'h7fffff;
		end
		else begin
			fp_product[31] = fp_multiplier[31] ^ fp_multiplicand[31];
			if ((mul_exponent_underflow || multiplier_is_zero) || multiplicand_is_zero) begin
				fp_product[30-:8] = 8'h00;
				fp_product[22-:FLOAT32_SIG_WIDTH] = 23'h000000;
			end
			else if (mul_exponent_carry) begin
				fp_product[30-:8] = 8'hff;
				fp_product[22-:FLOAT32_SIG_WIDTH] = 23'h000000;
			end
			else begin
				fp_product[30-:8] = mul_exponent;
				if (mul_product[(2 * (A + E)) - 1]) begin
					if (((2 * (A + E)) - 1) >= FLOAT32_SIG_WIDTH)
						fp_product[22-:FLOAT32_SIG_WIDTH] = mul_product[(2 * (A + E)) - 2:(2 * (A + E)) - 24];
					else
						fp_product[22-:FLOAT32_SIG_WIDTH] = {mul_product[(2 * (A + E)) - 2:0], 1'sb0};
				end
				else if (((2 * (A + E)) - 2) >= FLOAT32_SIG_WIDTH)
					fp_product[22-:FLOAT32_SIG_WIDTH] = mul_product[(2 * (A + E)) - 3:(2 * (A + E)) - 25];
				else
					fp_product[22-:FLOAT32_SIG_WIDTH] = {mul_product[(2 * (A + E)) - 3:0], 1'sb0};
			end
		end
	end
	initial _sv2v_0 = 0;
endmodule