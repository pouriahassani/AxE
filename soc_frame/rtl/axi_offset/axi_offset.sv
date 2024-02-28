
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// this module simply changes the AXI address.
`define  axi_offset_DBG
module axi_offset
#(
     parameter OFFSET = 0
    ,parameter USE_PARAMETER = 0
)
(
     if_axi_light.slave  s_axi
    ,if_axi_light.master m_axi
    
    ,input [ `AXI_ADDR_WIDTH-1:0 ] offset
);
logic self_awareness_node_flag;
always_comb
begin : axi_offset_proc
    
    m_axi.awvalid = s_axi.awvalid;
    s_axi.awready = m_axi.awready;
    
    if ( USE_PARAMETER == 1 ) m_axi.awaddr  = s_axi.awaddr + OFFSET;
    else                      m_axi.awaddr  = s_axi.awaddr + offset;

 // Set a flag to indicate SELF_AWARENESS Node condition
    if ( USE_PARAMETER != 1 )
     self_awareness_node_flag = (m_axi.awaddr == offset);
    else 
      self_awareness_node_flag = 0;
    if(m_axi.awaddr  == offset) 
      m_axi.awaddr  = s_axi.awaddr - offset;
    m_axi.awprot  = s_axi.awprot ;
    
    m_axi.wvalid  = s_axi.wvalid ;
    s_axi.wready  = m_axi.wready ;
    m_axi.wdata   = s_axi.wdata  ;
    m_axi.wstrb   = s_axi.wstrb  ;
    
    s_axi.bvalid  = m_axi.bvalid ;
    m_axi.bready  = s_axi.bready ;
    s_axi.bresp   = m_axi.bresp  ;
    
    m_axi.arvalid = s_axi.arvalid;
    s_axi.arready = m_axi.arready;
    
    
    if ( USE_PARAMETER == 1 ) m_axi.araddr  = s_axi.araddr + OFFSET;
    else                      m_axi.araddr  = s_axi.araddr + offset;
    
    m_axi.arprot  = s_axi.arprot ;
    
    s_axi.rvalid  = m_axi.rvalid ;
    m_axi.rready  = s_axi.rready ;
    s_axi.rdata   = m_axi.rdata  ;
    s_axi.rresp   = m_axi.rresp  ;
    
end

// `ifdef axi_offset_DBG
//   // Procedural block to display debug information
//   always begin
//       if (self_awareness_node_flag) begin

//               // $display("SELF_AWARENESS set address");
//                $display("Selfaware address 0x%08x is being written with data %c transfered to address 0x%08x\n",m_axi.awaddr,s_axi.wdata,m_axi.awaddr);
//               // Additional debug information if needed

//       end
//   end
// `endif

endmodule
