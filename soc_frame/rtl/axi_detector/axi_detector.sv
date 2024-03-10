
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */



// zu beachten
// der detector geht in den idle state auch wenn die antwort noch nicht ganz
// durch gegangen ist. z.b. gleich nach einem AXI_READ.
// der detector legt dann gleich die request wait signale an und schickt
// die eigentlichen response signale weiter.
// so kann es aussehen als waere der detector schon fertig, aber die anderen
// module noch nicht.
// es sind dann diese ganzen ready signale 1 und auch noch ein valid.
// z.b. ist rvalid 1 was bedeutet, dass daten gelesen wurden, aber
// gleichzeitig ist arready, awready und wready gesetzt.




// once a certain WDATA and AWADDR combination is detected the output signal is
// asserted for 1 clk cycle.

// if the response is coming from the outside or from this module

`define RESP_FROM_OUTSIDE ( 1'b0 )
`define RESP_FROM_THIS    ( 1'b1 )

//`include "defines_axi.vh"

// parameters:

// ADDR_DETECT
// which address to detect. Note that the 2 lsb should not be used
// as they are removed by the PicoRV32 (byte addressing)

// DETECT_READ / DETECT_WRITE
// if reads or writes should be detected. both is also possible.

// GREATER_THAN
// if this is 1 then addresses greater than the set one are detected.
// otherwise the address has to equal.

// SIGNAL_PULSE
// if this is 1 then detect output is only asserted for 1 clk cycle.
// otherwise the signal is asserted until an address is present that does not
// fit the detection criteria.

// FORWARD
// if the detected AXI-request should be forwarded or answered directly.
// in the case of a detected read rdata is set to 0.

module axi_detector
#(
     parameter ADDR_DETECT = 32'h 00FF_FFFC
    
    ,parameter DETECT_READ  = 0
    ,parameter DETECT_WRITE = 0
    
    ,parameter GREATER_THAN = 0
    
    ,parameter SIGNAL_PULSE = 0
    ,parameter FORWARD      = 0
)
(
     input clk
    ,input res_n
    
    //~ ,(* mark_debug = "true" *) output reg sig
    ,output reg sig
    ,output reg [ `AXI_DATA_WIDTH-1:0 ] data
    
    ,if_axi_light.slave  s_axi
    ,if_axi_light.master m_axi
);

enum
{
     IDLE
    ,DETECT
    ,AXI_WRITE
    ,AXI_READ
    ,AXI_WRITE_RESP
    ,AXI_READ_RESP
}state;

// req

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_awaddr;
reg[                 2:0 ] latched_awprot;

reg[ `AXI_DATA_WIDTH-1:0 ] latched_wdata;
reg[`AXI_WSTRB_WIDTH-1:0 ] latched_wstrb;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_araddr;
reg[                 2:0 ] latched_arprot;

reg[ `AXI_ADDR_WIDTH-1:0 ] addr_to_check;

reg done;

reg resp_from;

reg r_bvalid;
reg r_rvalid;

reg detected;

reg write;

always @ ( posedge clk )
begin : axi_detector_proc
    
    // wir legen nur die default axi signale an fuer das was uns interessiert
    // sonst werden diese einfach durch geleitet.
    
    if ( DETECT_WRITE == 1 )
    begin
        s_axi.s_default_write_req();
        m_axi.m_default_write_req();
    end
    
    if ( DETECT_READ == 1 )
    begin
        s_axi.s_default_read_req();
        m_axi.m_default_read_req();
    end
    
    // if the signal should be a pulse it is set back here
    
    if ( SIGNAL_PULSE == 1 ) sig = 0;
    
    if ( ! res_n )
    begin
        
        state = IDLE;
        
        latched_awaddr = 0;
        latched_araddr = 0;
        
        if ( DETECT_WRITE == 1 )
        begin
            
            latched_awprot = 0;
            latched_wdata  = 0;
            latched_wstrb  = 0;
            
        end
        
        if ( DETECT_READ == 1 )
        begin
            
            latched_arprot = 0;
            
        end
        
        sig = 0;
        
        done = 0;
        resp_from = 0;
        
        r_bvalid = 0;
        r_rvalid = 0;
        
        detected = 0;
        
        write = 0;
        
    end
    else
    begin
        
        case(state)
        
        // ---------------------------------------------------------------------
        // IDLE
        // ---------------------------------------------------------------------
        
        IDLE :
            begin
                
                resp_from = `RESP_FROM_OUTSIDE;
                
                r_bvalid = 1'b0;
                r_rvalid = 1'b0;
                
                //---------------------
                // write
                //---------------------
                
                if ( DETECT_WRITE == 1 )
                begin
                    
                    s_axi.write_req_wait( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done );
                    if ( done == 1'b1 )
                    begin
                        
                        write = 1;
                        state = DETECT;
                        
                    end
                    
                end
                
                //---------------------
                // read
                //---------------------
                
                if ( DETECT_READ == 1 )
                begin
                    
                    s_axi.read_req_wait( latched_araddr, latched_arprot, done );
                    if ( done == 1'b1 )
                    begin
                        
                        write = 0;
                        state = DETECT;
                        
                    end
                    
                end
                
            end
        
        // ---------------------------------------------------------------------
        // DETECT
        // ---------------------------------------------------------------------
        
        DETECT:
        begin
            
            detected = 0;
            
            if ( write == 1 ) addr_to_check = latched_awaddr;
            else              addr_to_check = latched_araddr;
            
            if ( ( GREATER_THAN == 1 ) && ( ADDR_DETECT <  addr_to_check ) ) detected = 1;
            if ( ( GREATER_THAN == 0 ) && ( ADDR_DETECT == addr_to_check ) ) detected = 1;
            
            if ( detected == 1 )
            begin
                
                sig = 1;
                
                if ( write == 1) data = latched_wdata;
                
            end
            else                 sig = 0;
            
            if (
                ( detected == 1 ) &&
                ( FORWARD == 0 )
            )
            begin
                
                resp_from = `RESP_FROM_THIS;
                
                if ( write == 1 )
                begin
                    r_bvalid = 1'b1;
                    state = AXI_WRITE_RESP;
                end
                else
                begin
                    r_rvalid = 1'b1;
                    state = AXI_READ_RESP;
                end
                
            end
            else
            begin
                
                if ( write == 1 ) state = AXI_WRITE;
                else              state = AXI_READ;
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_WRITE
        // ---------------------------------------------------------------------
        
        AXI_WRITE:
        begin
            
            // we can return to the idle state right away as the response
            // signals are just passed along and not read by this module.
            // this is also true for a read.
            
            // this is needed by vivado
            
            if ( DETECT_WRITE == 1 )
            begin
                m_axi.write_req( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done );
                if ( done == 1'b1 ) state = IDLE;
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_READ
        // ---------------------------------------------------------------------
        
        AXI_READ:
        begin
            
            // this is needed by vivado
            
            if ( DETECT_READ == 1 )
            begin
                m_axi.read_req( latched_araddr, latched_arprot, done );
                if ( done == 1'b1 ) state = IDLE;
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_WRITE_RESP
        // ---------------------------------------------------------------------
        
        AXI_WRITE_RESP:
        begin
            
            // once bready came from the master change the state to IDLE
            
            if ( DETECT_WRITE == 1 )
            begin
                if ( m_axi.bready == 1'b1 )
                begin
                    
                    r_bvalid = 1'b0;
                    state = IDLE;
                    
                end
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_READ_RESP
        // ---------------------------------------------------------------------
        
        AXI_READ_RESP:
        begin
            
            // once rready came from the master change the state to IDLE
            
            // wenn das rready vom master kommt, weiss ich, dass der master
            // das resultat genommen hat. wenn ich nur auf das valid achte
            // weiss ich nur, dass der slave das richtige zurueck geschickt
            // hat.
            
            if ( DETECT_READ == 1 )
            begin
                if ( m_axi.rready == 1'b1 )
                begin
                    
                    r_rvalid = 1'b0;
                    state = IDLE;
                    
                end
            end
            
        end
        
        // ---------------------------------------------------------------------
        // DEFAULT
        // ---------------------------------------------------------------------
        
        default : state = IDLE;
        
        endcase
    end
    
end

// wire resp_from_outside;

// assign resp_from_outside =
// (
    // ( DETECT_WRITE == 0 ) ||
    // ( ( DETECT_WRITE == 1 ) && ( FORWARD == 1 ) ) ||
    // (
        // ( DETECT_WRITE == 1 ) &&
        // ( FORWARD      == 0 ) &&
        // ( resp_from    == `RESP_FROM_OUTSIDE )
    // )
// );

// mux deciding which response to forward.

// was wir als antwort zurueck schicken

// these are all the response signals

always_comb
begin
    
    // if ( resp_from_outside == 1 )
    // begin
        
        // s_axi.bvalid = m_axi.bvalid;
        // m_axi.bready = s_axi.bready;
        // s_axi.bresp  = m_axi.bresp;
        
    // end
    // else
    // begin
        
        // s_axi.bvalid = r_bvalid;
        // // bready is checked in the fsm
        // s_axi.bresp  = `RESP_OKAY;
        
    // end
    
    if ( ( DETECT_WRITE == 1 ) && ( write == 1 ) && ( resp_from == `RESP_FROM_THIS ) )
    begin
        
        s_axi.bvalid = r_bvalid;
        // bready is checked in the fsm
        s_axi.bresp  = `RESP_OKAY;
        
    end
    else
    begin
        
        s_axi.bvalid = m_axi.bvalid;
        m_axi.bready = s_axi.bready;
        s_axi.bresp  = m_axi.bresp;
        
    end
    
    if ( ( DETECT_READ == 1 ) && ( write == 0 ) && ( resp_from == `RESP_FROM_THIS ) )
    begin
        
        s_axi.rvalid = r_rvalid;
        // rready is checked in the fsm
        s_axi.rdata = 0;
        s_axi.rresp = `RESP_OKAY;
        
    end
    else
    begin
        
        s_axi.rvalid = m_axi.rvalid;
        m_axi.rready = s_axi.rready;
        s_axi.rdata  = m_axi.rdata;
        s_axi.rresp  = m_axi.rresp;
        
    end
    
end

// was wir einfach durchleiten

// this are all the request signals

always_comb
begin
    
    // pass through the signals we are not concerned with.
    
    if ( DETECT_WRITE == 0 )
    begin
        m_axi.awvalid = s_axi.awvalid;
        s_axi.awready = m_axi.awready;
        m_axi.awaddr  = s_axi.awaddr;
        m_axi.awprot  = s_axi.awprot;
        
        m_axi.wvalid  = s_axi.wvalid;
        s_axi.wready  = m_axi.wready;
        m_axi.wdata   = s_axi.wdata;
        m_axi.wstrb   = s_axi.wstrb;
    end
    
    if ( DETECT_READ == 0 )
    begin
        m_axi.arvalid = s_axi.arvalid;
        s_axi.arready = m_axi.arready;
        m_axi.araddr  = s_axi.araddr;
        m_axi.arprot  = s_axi.arprot;
    end
    
end


endmodule
