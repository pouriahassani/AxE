
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module axi_arbiter #(
)
(
     input clk
    ,input res_n
    
    ,if_axi_light.slave  s_axi_0
    ,if_axi_light.slave  s_axi_1
    
    ,if_axi_light.master m_axi
);

enum
{
     IDLE
    ,AXI_WRITE
    ,AXI_READ
    ,AXI_WAIT
    ,AXI_WRITE_RESP
    ,AXI_READ_RESP
    ,SWITCH
}state;

// req

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_awaddr;
reg[                 2:0 ] latched_awprot;

reg[ `AXI_DATA_WIDTH-1:0 ] latched_wdata;
reg[`AXI_WSTRB_WIDTH-1:0 ] latched_wstrb;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_araddr;
reg[                 2:0 ] latched_arprot;

// resp

reg[                 1:0 ] latched_bresp;

reg[                 1:0 ] latched_rresp;
reg[ `AXI_DATA_WIDTH-1:0 ] latched_rdata;

reg done_s;
reg done_m;

reg selector;

always @ ( posedge clk )
begin : axi_arbiter_proc
    
    s_axi_0.s_default();
    s_axi_1.s_default();
    
    m_axi.m_default();
    
    done_s = 1'b0;
    done_m = 1'b0;
    
    if ( ! res_n )
    begin
        
        state = IDLE;
        
        latched_awaddr = 0;
        latched_awprot = 0;
        
        latched_wdata = 0;
        latched_wstrb = 0;
        
        latched_araddr = 0;
        latched_arprot = 0;
        
        // resp
        
        latched_bresp = 0;
        
        latched_rresp = 0;
        latched_rdata = 0;
        
        done_s = 1'b0;
        done_m = 1'b0;
        
        selector = 1'b0;
        
    end
    else
    begin
        
        case(state)
        
        // -------------------------------------------------------------------------
        // IDLE
        // -------------------------------------------------------------------------
        
        IDLE:
        begin
            
            //---------------------
            // write
            //---------------------
            
            if ( selector == 1'b0 )
                s_axi_0.write_req_wait( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done_s );
            else
                s_axi_1.write_req_wait( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done_s );
            
            if ( done_s == 1'b1 ) state = AXI_WRITE;
            
            //---------------------
            // read
            //---------------------
            
            if ( selector == 1'b0 )
                s_axi_0.read_req_wait( latched_araddr, latched_arprot, done_s );
            else
                s_axi_1.read_req_wait( latched_araddr, latched_arprot, done_s );
            
            if ( done_s == 1'b1 ) state = AXI_READ;
            
        end
        
        // -------------------------------------------------------------------------
        // AXI_WRITE
        // -------------------------------------------------------------------------
        
        AXI_WRITE:
            begin
                
                m_axi.write_req( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done_m );
                
                if ( done_m == 1'b1 ) state = AXI_WAIT;
                
            end
            
        
        // -------------------------------------------------------------------------
        // AXI_READ
        // -------------------------------------------------------------------------
        
        AXI_READ:
            begin
                
                m_axi.read_req( latched_araddr, latched_arprot, done_m );
                
                if ( done_m == 1'b1 ) state = AXI_WAIT;
                
            end
        
        // -------------------------------------------------------------------------
        // AXI_WAIT
        // -------------------------------------------------------------------------
        
        AXI_WAIT:
            begin
                
                m_axi.write_resp_wait( latched_bresp, done_m );
                if ( done_m == 1'b1 ) state = AXI_WRITE_RESP;
                
                m_axi.read_resp_wait( latched_rdata, latched_rresp, done_m );
                if ( done_m == 1'b1 ) state = AXI_READ_RESP;
                
            end
        
        // -------------------------------------------------------------------------
        // AXI_WRITE_RESP
        // -------------------------------------------------------------------------
        
        AXI_WRITE_RESP:
            begin
                
                if ( selector == 1'b0 )
                    s_axi_0.write_resp ( latched_bresp, done_s );
                else
                    s_axi_1.write_resp ( latched_bresp, done_s );
                
                if ( done_s == 1'b1 ) state = SWITCH;
                
            end
        
        // -------------------------------------------------------------------------
        // AXI_READ_RESP
        // -------------------------------------------------------------------------
        
        AXI_READ_RESP:
            begin
                
                if ( selector == 1'b0 )
                    s_axi_0.read_resp( latched_rdata, latched_rresp, done_s );
                else
                    s_axi_1.read_resp( latched_rdata, latched_rresp, done_s );
                
                if ( done_s == 1'b1 ) state = SWITCH;
                
            end
        
        SWITCH:
        begin
            
            selector = ~selector;
            
            state = IDLE;
            
        end
        
        // -------------------------------------------------------------------------
        // DEFAULT
        // -------------------------------------------------------------------------
        
        default : state = IDLE;
        
        endcase
    end
    
end

endmodule
