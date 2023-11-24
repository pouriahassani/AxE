
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// AXI Light interface.

interface if_axi_light
#(
     AXI_DATA_WIDTH = 0
    ,AXI_ADDR_WIDTH = 0
    ,AXI_WSTRB_WIDTH = 0
)
();
    
    logic                         awvalid;
    logic                         awready;
    logic [ `AXI_ADDR_WIDTH-1:0 ] awaddr;
    logic [                 2:0 ] awprot;
    
    logic                         wvalid;
    logic                         wready;
    logic [ `AXI_DATA_WIDTH-1:0 ] wdata;
    logic [`AXI_WSTRB_WIDTH-1:0 ] wstrb;
    
    logic                         bvalid;
    logic                         bready;
    logic [                 1:0 ] bresp;
    
    logic                         arvalid;
    logic                         arready;
    logic [ `AXI_ADDR_WIDTH-1:0 ] araddr;
    logic [                 2:0 ] arprot;
    
    logic                         rvalid;
    logic                         rready;
    logic [ `AXI_DATA_WIDTH-1:0 ] rdata;
    logic [                 1:0 ] rresp;
    
    // local variables used internally.
    
    logic w_addr_collected = 1'b0;
    logic w_data_collected = 1'b0;
    
    logic w_addr_sent = 1'b0;
    logic w_data_sent = 1'b0;
    
    //--------------------------------------------------------------------------
    // tasks - master
    //--------------------------------------------------------------------------
    
    // the following task are called by the AXI master.
    
    //---------------------
    // m_default
    //---------------------
    
    // the default signals applied each clk.
    // they are meant to be overwritten by other tasks.
    
    task m_default();
        
        awvalid = 1'b0;
        wvalid  = 1'b0;
        arvalid = 1'b0;
        
        bready = 1'b0;
        rready = 1'b0;
        
    endtask
    
    task m_default_write();
        
        awvalid = 1'b0;
        wvalid  = 1'b0;
        bready = 1'b0;
        
    endtask
    
    task m_default_write_req();
        
        awvalid = 1'b0;
        wvalid  = 1'b0;
        
    endtask
    
    task m_default_read_req();
        
        arvalid = 1'b0;
        
    endtask
    
    //---------------------
    // write_resp_wait
    //---------------------
    
    // wait for the write response
    
    task write_resp_wait
    (
         output [                1:0 ] t_bresp
        ,output done
    );
        
        done = 1'b0;
        
        if ( bvalid == 1'b1 )
        begin
            bready = 1'b1;
            
            t_bresp = bresp;
            
            done = 1'b1;
        end
        
    endtask
    
    //---------------------
    // read_resp_wait
    //---------------------
    
    // wait for the read response
    
    task read_resp_wait
    (
         output [ `AXI_DATA_WIDTH-1:0 ] t_rdata
        ,output [                 1:0 ] t_rresp
        ,output done
    );
        
        done = 1'b0;
        
        // wenn die daten valid sind, dann sagt der master, dass er die
        // daten genommen hat (mit rready)
        
        if ( rvalid == 1'b1 )
        begin
            rready = 1'b1;
            
            t_rdata = rdata;
            t_rresp = rresp;
            
            done = 1'b1;
        end
        
    endtask
    
    //---------------------
    // write_req
    //---------------------
    
    // send a write request
    
    task write_req
    (
         input [ `AXI_ADDR_WIDTH-1:0 ] t_awaddr
        ,input [                 2:0 ] t_awprot
        ,input [ `AXI_DATA_WIDTH-1:0 ] t_wdata
        ,input [`AXI_WSTRB_WIDTH-1:0 ] t_wstrb
        ,output done
    );
        
        done = 1'b0;
        
        if ( w_addr_sent == 1'b0 ) awvalid = 1'b1; // master: "i have a valid write address"
        if ( w_data_sent == 1'b0 ) wvalid  = 1'b1; // master: "i have valid write data"
        
        awaddr = t_awaddr;
        awprot = t_awprot;
        
        wdata  = t_wdata;
        wstrb  = t_wstrb;
        
        if ( awready == 1'b1 ) // slave: "i am ready to receive the write address"
            w_addr_sent = 1'b1;
        
        if ( wready == 1'b1 ) // slave: "i am ready to receive the write data"
            w_data_sent = 1'b1;
        
        if ( ( w_addr_sent == 1'b1 ) && ( w_data_sent == 1'b1 ) )
        begin
            
            w_addr_sent = 1'b0;
            w_data_sent = 1'b0;
            
            done = 1'b1;
            
        end
        
    endtask
    
    //---------------------
    // read_req
    //---------------------
    
    // send a read request
    
    task read_req
    (
         input [ `AXI_ADDR_WIDTH-1:0 ] t_araddr
        ,input [                 2:0 ] t_arprot
        ,output done
    );
        done = 1'b0;
        
        arvalid = 1'b1;
        
        araddr = t_araddr;
        arprot = t_arprot;
        
        if ( arready == 1'b1 ) done = 1'b1;
        
    endtask
    
    //--------------------------------------------------------------------------
    // tasks - slave
    //--------------------------------------------------------------------------
    
    //---------------------
    // s_default
    //---------------------
    
    task s_default();
        
        awready = 1'b0;
        wready  = 1'b0;
        arready = 1'b0;
        
        bvalid = 1'b0;
        rvalid = 1'b0;
        
    endtask
    
    task s_default_write();
        
        awready = 1'b0;
        wready  = 1'b0;
        bvalid = 1'b0;
        
    endtask
    
    task s_default_write_req();
        
        awready = 1'b0;
        wready  = 1'b0;
        
    endtask
    
    task s_default_read_req();
        
        arready = 1'b0;
        
    endtask
    
    //---------------------
    // write_req_wait
    //---------------------
    
    task write_req_wait
    (
         output [ `AXI_ADDR_WIDTH-1:0 ] t_awaddr
        ,output [                 2:0 ] t_awprot
        ,output [ `AXI_DATA_WIDTH-1:0 ] t_wdata
        ,output [`AXI_WSTRB_WIDTH-1:0 ] t_wstrb
        ,output done
    );
        
        done = 1'b0;
        
        if ( w_addr_collected == 1'b0 ) awready = 1'b1;
        if ( w_data_collected == 1'b0 ) wready  = 1'b1;
        
        // addr
        
        if ( awvalid == 1'b1 )
        begin
            
            t_awaddr = awaddr;
            t_awprot = awprot;
            
            w_addr_collected = 1'b1;
            
        end
        
        // data
        
        if ( wvalid == 1'b1 )
        begin
            
            t_wdata = wdata;
            t_wstrb = wstrb;
            
            w_data_collected = 1'b1;
            
        end
        
        // both available
        
        if ( ( w_addr_collected == 1'b1 ) && ( w_data_collected == 1'b1 ) )
        begin
            
            w_addr_collected = 1'b0;
            w_data_collected = 1'b0;
            
            done = 1'b1;
            
        end
        
    endtask
    
    //---------------------
    // read_req_wait
    //---------------------
    
    task read_req_wait
    (
         output [ `AXI_ADDR_WIDTH-1:0 ] t_araddr
        ,output [                 2:0 ] t_arprot
        ,output done
    );
        
        done = 1'b0;
        
        arready = 1'b1;
        
        if ( arvalid == 1'b1 )
        begin
            
            t_araddr = araddr;
            t_arprot = arprot;
            
            done = 1'b1;
            
        end
        
    endtask
    
    //---------------------
    // write_resp
    //---------------------
    
    task write_resp
    (
         input [ 1:0 ] t_bresp
        ,output done
    );
        
        done = 1'b0;
        
        bvalid = 1'b1;
        bresp = t_bresp;
        
        if ( bready == 1'b1 ) done = 1'b1;
        
    endtask
    
    //---------------------
    // read_resp
    //---------------------
    
    task read_resp
    (
         input [ `AXI_DATA_WIDTH-1:0 ] t_rdata
        ,input [                 1:0 ] t_rresp
        ,output done
    );
        
        done = 1'b0;
        
        rvalid = 1'b1;
        rresp  = t_rresp;
        rdata  = t_rdata;
        
        if ( rready == 1'b1 ) done = 1'b1;
        
    endtask
    
    //--------------------------------------------------------------------------
    // modports
    //--------------------------------------------------------------------------
    
    modport master
    (
         output awvalid
        ,input  awready
        ,output awaddr
        ,output awprot
        
        ,output wvalid
        ,input  wready
        ,output wdata
        ,output wstrb
        
        ,input  bvalid
        ,output bready
        ,input  bresp
        
        ,output arvalid
        ,input  arready
        ,output araddr
        ,output arprot
        
        ,input  rvalid
        ,output rready
        ,input  rdata
        ,input  rresp
        
        ,import m_default
        ,import m_default_write
        ,import m_default_write_req
        ,import m_default_read_req
        
        ,import read_resp_wait
        ,import write_resp_wait
        
        ,import write_req
        ,import read_req
    );
    
    modport slave
    (
         input  awvalid
        ,output awready
        ,input  awaddr
        ,input  awprot
        
        ,input  wvalid
        ,output wready
        ,input  wdata
        ,input  wstrb
        
        ,output bvalid
        ,input  bready
        ,output bresp
        
        ,input  arvalid
        ,output arready
        ,input  araddr
        ,input  arprot
        
        ,output rvalid
        ,input  rready
        ,output rdata
        ,output rresp
        
        ,import s_default
        ,import s_default_write
        ,import s_default_write_req
        ,import s_default_read_req
        
        ,import write_req_wait
        ,import read_req_wait
        
        ,import write_resp
        ,import read_resp
    );
    
endinterface
