`timescale 1ns / 1ps

`ifdef SYN
`include "/home/shuemer/cadence/approx_riscv-master/SoC_PiXo_repo/configurations/default/defines_axi.vh"
`include "/home/shuemer/cadence/approx_riscv-master/SoC_PiXo_repo/configurations/default/defines_mem.vh"
`include "/home/shuemer/cadence/approx_riscv-master/SoC_PiXo_repo/configurations/default/defines_ascii.vh"
`endif

module riscv_tb;

    // Parameters are defined in these files
    parameter TIMEOUT = 2000000;
    // `include "inc/macros.inc"

    // Memory initialization files
   // parameter MEM_MIF      = "/home/sayandipde/approx_riscv/SoC_PiXo_repo/mem.hex";
    //~ parameter MEM_MIF      = "/home/sayandipde/approx_riscv/SoC_PiXo_repo/mif/mul.hex";
    //~ parameter MEM_MIF      = "/home/shuemer/SoC_SaCySoc_repo_cadence/mem.hex";
    //~ parameter MEM_MIF      = "/home/shuemer/SoC_SaCySoc_repo/mul.hex";
    parameter MEM_MIF      = "/home/shuemer/SoC_SaCySoc_repo/mem.hex";
    
    // Simulation Variables
    integer i, j, k;
    real PERIOD;

    // Inputs
    reg clk;
    
    reg res_n;
    reg res_n_controller;
    reg res_n_nodes;
    
 	reg we_ext;
	reg [ `AXI_DATA_WIDTH-1 : 0 ] dload_data;
	reg [ `AXI_ADDR_WIDTH-1 : 0 ] dload_addr;

    // Outputs
    wire [`ASCII_WIDTH-1:0] debugger_ascii;
    wire debugger_sig;
    wire ill_awaddr_out_of_range;
    wire ill_araddr_out_of_range;
    wire trap;
       
    // Instantiate the Unit Under Test (UUT)
    
    top #()top_inst (
        .clk(clk),
        .res_n(res_n),
        .res_n_controller(res_n_controller),
        .res_n_nodes(res_n_nodes),
        .debugger_sig(debugger_sig),
        .debugger_ascii(debugger_ascii),
        .ill_awaddr_out_of_range(ill_awaddr_out_of_range),
        .ill_araddr_out_of_range(ill_araddr_out_of_range),
        .trap(trap),
        .we_ext(we_ext),      
        .dload_data(dload_data),
        .dload_addr(dload_addr)
    );

	// memory ram init.
    reg[ `AXI_DATA_WIDTH-1:0 ] im_init[ `MEM_SIZE-1:0 ];
    
	initial begin
		im_init[ `MEM_SIZE-1:0 ] = {`MEM_SIZE{0}};
        
        // has to be in reversed order
        // ncelab: *W,MEMODR (/home/shuemer/SoC_SaCySoc_repo/configurations/noc_one_node/tb.sv,69|35): $readmem default memory order incompatible with IEEE1364.
        
        $readmemh( MEM_MIF, im_init, `MEM_SIZE-1, 0);
    end


    // Clock Generation
    always begin
    PERIOD = 4;
    #(PERIOD/2) clk =~clk;
    end
    
    always@(posedge trap) begin
        $display ("TRAP!");
    end
    
    //~ always@(posedge debugger_sig) begin
        
        //~ $display ("%h", debugger_ascii);
        
    //~ end
    
    always@(posedge clk)
    begin
        
        if ( debugger_sig == 1'b1 ) $write ("%0s", debugger_ascii);
        
    end
    
    /*// Output Validation
    always @(posedge CLK) begin
        
        if (npu_dout_valid==1) begin
            $fwrite(f,"%h\n",npu_dout);
        end
       if ((npu_dout_valid==1 && outDataIdx != 0) && outData!==npu_dout && outData!==16'h7fff) begin
            $display ("ERROR at time %d", $time);
            $display ("    Output index: %d", outDataIdx_delay/OUTPUT_SIZE);
            $display ("    Expected value %h, got value %h", outData, npu_dout);
            // #100;
            // $finish;
        end

        if (outDataIdx_delay == NPU_TEST_SIZE*OUTPUT_SIZE) begin
            $display ("Simulation testbench done! SUCCESS!!!");
            #100;
            $finish;
        end
    end*/

    // TESTBENCH
    initial begin
        
        `ifndef SDF
            //$dumpfile("dut.vcd");
            //$dumpvars;
        

            /*for (i = 0; i < `MEM_SIZE; i = i + 1) begin
                for (j = 0; j < `AXI_DATA_WIDTH; j = j + 1) begin
                    $dumpvars(0, top_inst.memory_inst.mem[i][j]);
                end
            end*/
        `endif
        
        `ifdef SDF
        //~ $sdf_annotate("",top_inst,,"/home/sayandipde/approx_riscv/SoC_PiXo_repo/asic_flow/sim/sdf.log" , "MAXIMUM", ,"FROM_MTM");      
        $sdf_annotate("",top_inst,,"/home/shuemer/cadence/approx_riscv-master/SoC_PiXo_repo/asic_flow/sim/sdf.log" , "MAXIMUM", ,"FROM_MTM");      
        `endif

        // Initialize Inputs
        clk = 0;
        res_n = 0;
        res_n_controller = 0;
        res_n_nodes = 0;
		we_ext = 1;
		dload_data = 0;
		dload_addr = 0;
		
		// Wait 100 ns for global reset to finish
        #(PERIOD);
        res_n = 1; // reset is 1 at 10 ns
        #(PERIOD*10);
        
        $display ("Starting simulation!");

        // Load memories
		//`ifdef READ_WRITE_MEMORY
        #(PERIOD*10);
        for (i = 0; i < 1; i = i+1) begin
            #(PERIOD);
            //we_ext = 1;
            case (i)
                0: begin // instruction memory
                    $display ("Loading instruction memory!");
                    k = `MEM_SIZE;
                    //ram_mem_adr = 0;
                end
            endcase
            for (j = 0; j < k; j = j + 1) begin
                #(PERIOD);
                dload_addr = j;
                case (i)
                    0: begin // instruction memory
						#(PERIOD);
                        dload_data = im_init[(k-1) - j];//{{(RAMDATA_W-IM_WIDTH){1'b0}}, im_init[j]}; #DE
						$display("loading (%0d/%0d)", j, k);
                    end
                endcase
            end
        end

        #(PERIOD);
        we_ext = 0; 
        dload_data = 0;
        //ram_mem_adr = 0;
        dload_addr = 0;
		// `endif
        
        
        $display( "starting pico" );
        
        #(PERIOD);
        res_n_controller = 1;
        res_n_nodes = 1;
        #(PERIOD);
        
        // f = $fopen("/home/sayandipde/snnap/hardware/src/mif/out_verilog.mif","w");
        // If the testbench hasn't completed by now, somthing went wrong...
        #(TIMEOUT)
        $display ("Simulation Timeout!");
        // $fclose(f);
        $finish;
    end

endmodule



