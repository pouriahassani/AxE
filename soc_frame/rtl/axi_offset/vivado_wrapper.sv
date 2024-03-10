
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// this is an example of a wrapper that can be used to create an IP core in
// vivado. it might be possible that the axi_offset changed a bit and this
// wrapper needs to be adapted.

module axi_offset_external_vivado_wrapper
#()
(
     input clk
    ,input res_n
    
    ,input [ `AXI_ADDR_WIDTH-1:0 ] offset
    
    ,input                          if_axi_light_s_awvalid
    ,output                         if_axi_light_s_awready
    ,input [ `AXI_ADDR_WIDTH-1:0 ]  if_axi_light_s_awaddr
    ,input [                 2:0 ]  if_axi_light_s_awprot
    ,input                          if_axi_light_s_wvalid
    ,output                         if_axi_light_s_wready
    ,input [ `AXI_DATA_WIDTH-1:0 ]  if_axi_light_s_wdata
    ,input [`AXI_WSTRB_WIDTH-1:0 ]  if_axi_light_s_wstrb
    ,output                         if_axi_light_s_bvalid
    ,input                          if_axi_light_s_bready
    ,output [                 1:0 ] if_axi_light_s_bresp
    ,input                          if_axi_light_s_arvalid
    ,output                         if_axi_light_s_arready
    ,input [ `AXI_ADDR_WIDTH-1:0 ]  if_axi_light_s_araddr
    ,input [                 2:0 ]  if_axi_light_s_arprot
    ,output                         if_axi_light_s_rvalid
    ,input                          if_axi_light_s_rready
    ,output [ `AXI_DATA_WIDTH-1:0 ] if_axi_light_s_rdata
    ,output [                 1:0 ] if_axi_light_s_rresp
    
    ,output                         if_axi_light_m_awvalid
    ,input                          if_axi_light_m_awready
    ,output [ `AXI_ADDR_WIDTH-1:0 ] if_axi_light_m_awaddr
    ,output [                 2:0 ] if_axi_light_m_awprot
    ,output                         if_axi_light_m_wvalid
    ,input                          if_axi_light_m_wready
    ,output [ `AXI_DATA_WIDTH-1:0 ] if_axi_light_m_wdata
    ,output [`AXI_WSTRB_WIDTH-1:0 ] if_axi_light_m_wstrb
    ,input                          if_axi_light_m_bvalid
    ,output                         if_axi_light_m_bready
    ,input  [                 1:0 ] if_axi_light_m_bresp
    ,output                         if_axi_light_m_arvalid
    ,input                          if_axi_light_m_arready
    ,output [ `AXI_ADDR_WIDTH-1:0 ] if_axi_light_m_araddr
    ,output [                 2:0 ] if_axi_light_m_arprot
    ,input                          if_axi_light_m_rvalid
    ,output                         if_axi_light_m_rready
    ,input  [ `AXI_DATA_WIDTH-1:0 ] if_axi_light_m_rdata
    ,input  [                 1:0 ] if_axi_light_m_rresp
);
    
    if_axi_light #() if_axi_light_s();
    if_axi_light #() if_axi_light_m();
    
    assign if_axi_light_s.awvalid = if_axi_light_s_awvalid ;
    assign if_axi_light_s.awready = if_axi_light_s_awready ;
    assign if_axi_light_s.awaddr  = if_axi_light_s_awaddr  ;
    assign if_axi_light_s.awprot  = if_axi_light_s_awprot  ;
    assign if_axi_light_s.wvalid  = if_axi_light_s_wvalid  ;
    assign if_axi_light_s.wready  = if_axi_light_s_wready  ;
    assign if_axi_light_s.wdata   = if_axi_light_s_wdata   ;
    assign if_axi_light_s.wstrb   = if_axi_light_s_wstrb   ;
    assign if_axi_light_s.bvalid  = if_axi_light_s_bvalid  ;
    assign if_axi_light_s.bready  = if_axi_light_s_bready  ;
    assign if_axi_light_s.bresp   = if_axi_light_s_bresp   ;
    assign if_axi_light_s.arvalid = if_axi_light_s_arvalid ;
    assign if_axi_light_s.arready = if_axi_light_s_arready ;
    assign if_axi_light_s.araddr  = if_axi_light_s_araddr  ;
    assign if_axi_light_s.arprot  = if_axi_light_s_arprot  ;
    assign if_axi_light_s.rvalid  = if_axi_light_s_rvalid  ;
    assign if_axi_light_s.rready  = if_axi_light_s_rready  ;
    assign if_axi_light_s.rdata   = if_axi_light_s_rdata   ;
    assign if_axi_light_s.rresp   = if_axi_light_s_rresp   ;
    
    assign if_axi_light_m.awvalid = if_axi_light_m_awvalid ;
    assign if_axi_light_m.awready = if_axi_light_m_awready ;
    assign if_axi_light_m.awaddr  = if_axi_light_m_awaddr  ;
    assign if_axi_light_m.awprot  = if_axi_light_m_awprot  ;
    assign if_axi_light_m.wvalid  = if_axi_light_m_wvalid  ;
    assign if_axi_light_m.wready  = if_axi_light_m_wready  ;
    assign if_axi_light_m.wdata   = if_axi_light_m_wdata   ;
    assign if_axi_light_m.wstrb   = if_axi_light_m_wstrb   ;
    assign if_axi_light_m.bvalid  = if_axi_light_m_bvalid  ;
    assign if_axi_light_m.bready  = if_axi_light_m_bready  ;
    assign if_axi_light_m.bresp   = if_axi_light_m_bresp   ;
    assign if_axi_light_m.arvalid = if_axi_light_m_arvalid ;
    assign if_axi_light_m.arready = if_axi_light_m_arready ;
    assign if_axi_light_m.araddr  = if_axi_light_m_araddr  ;
    assign if_axi_light_m.arprot  = if_axi_light_m_arprot  ;
    assign if_axi_light_m.rvalid  = if_axi_light_m_rvalid  ;
    assign if_axi_light_m.rready  = if_axi_light_m_rready  ;
    assign if_axi_light_m.rdata   = if_axi_light_m_rdata   ;
    assign if_axi_light_m.rresp   = if_axi_light_m_rresp   ;
    
    axi_offset_external #() axi_offset_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( if_axi_light_s.slave )
        ,.m_axi( if_axi_light_m.master )
        
        ,.offset( offset )
    );

endmodule

