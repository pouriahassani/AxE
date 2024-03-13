// This does not work
// module test (
//     input wire clk,
//     input wire resetn,
//     output wire [7:0] data_out);

//     reg [7:0] counter;
//     assign data_out = counter; 

//     initial begin
//         $display("Hello, World! This is a test.sv");
//         counter = 8'd0;
//     end
    
//     always @(posedge clk) begin
//         if(resetn == 1'b0) begin
//             data_out <= 8'd0;
//         end
//         data_out <= data_out + 8'd1;
//     end

// endmodule

//This works
// module test(input clk, input resetn, output reg [7:0] data_out);
//     initial begin
//         $display("Hello, World! This is a test.sv");
//     end
//     always @(posedge clk) begin
//         if(resetn == 1'b0) begin
//             $display("Hello, World! This is a test.sv RESETN");
//         end
//         data_out <= data_out + 8'd1; //data_out initialised outside (either I guess by Verilator implicitly or by hand in /home/user/soc_frame/rtl/PiXo/picorv32_extended.v topmodule)
//         $display("Hello, World! This is a test.sv CLOCK data_out = %b", data_out);
//     end
// endmodule
// ********************************************************************************************************************
// Insert in /home/user/soc_frame/rtl/PiXo/picorv32_extended.v:
// ********************************************************************************************************************
//  `include "../../rtl/PiXo/test.sv"
//   ...
//   reg [7:0] testout = 8'd0;
//   test testi(.clk(clk), .resetn(resetn), .data_out(testout));
//   //TODO: remove these redundant test lines

