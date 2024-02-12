
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// this module is just a wrapper to enable a pico to be connected via the
// AXI interface.

module picorv32_if_wrapper
#(
    parameter NODE_ID = 0,
     parameter ENABLE_MUL = 0
    ,parameter ENABLE_DIV = 0
    
    ,parameter STACKADDR = 32'h 0000_9C40
    //~ ,parameter STACKADDR = 32'h 0000_1800
)
(
     input clk
    ,input res_n
    
    ,output trap
    
    ,if_axi_light.master  m_axi
);
    
//    assign trap = 1'b0;
    
    picorv32_axi
    #(
        .NODE_ID( NODE_ID ),
         .PROGADDR_RESET( 32'h 0000_0000 ) // just to be sure
        ,.STACKADDR( STACKADDR )
        
        ,.ENABLE_MUL ( ENABLE_MUL )
        ,.ENABLE_DIV ( ENABLE_DIV )
    )
    picorv32_axi_inst
    (
         .clk( clk )
        ,.resetn( res_n )
        
        // TODO - decide how to best use the trap output.
        
        ,.trap( trap )
        
        // AXI4-lite master memory interface
        ,.mem_axi_awvalid( m_axi.awvalid )
        ,.mem_axi_awready( m_axi.awready )
        ,.mem_axi_awaddr(  m_axi.awaddr  )
        ,.mem_axi_awprot(  m_axi.awprot  )
        
        ,.mem_axi_wvalid(  m_axi.wvalid   )
        ,.mem_axi_wready(  m_axi.wready   )
        ,.mem_axi_wdata(   m_axi.wdata    )
        ,.mem_axi_wstrb(   m_axi.wstrb    )
        
        ,.mem_axi_bvalid(  m_axi.bvalid   )
        ,.mem_axi_bready(  m_axi.bready   )
        
        ,.mem_axi_arvalid( m_axi.arvalid )
        ,.mem_axi_arready( m_axi.arready )
        ,.mem_axi_araddr(  m_axi.araddr  )
        ,.mem_axi_arprot(  m_axi.arprot  )
        
        ,.mem_axi_rvalid(  m_axi.rvalid   )
        ,.mem_axi_rready(  m_axi.rready   )
        ,.mem_axi_rdata(   m_axi.rdata    )
        
        // Pico Co-Processor Interface (PCPI)
        ,.pcpi_valid()
        ,.pcpi_insn()
        ,.pcpi_rs1()
        ,.pcpi_rs2()
        ,.pcpi_wr()
        ,.pcpi_rd()
        ,.pcpi_wait()
        ,.pcpi_ready()
        
        // IRQ interface
        ,.irq()
        ,.eoi()
        
        // here was the riscv formal stuff.
        
        // Trace Interface
        ,.trace_valid()
        ,.trace_data()
    );
    
endmodule
