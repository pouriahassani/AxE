
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module axi_mux
#()
(
     input selector
    
    ,if_axi_light.slave  s_axi_0
    ,if_axi_light.slave  s_axi_1
    
    ,if_axi_light.master m_axi_0
);

always_comb
begin
    
    if ( selector == 1'b0 )
    begin
        
        m_axi_0.awvalid = s_axi_0.awvalid ;
        s_axi_0.awready = m_axi_0.awready ;
        m_axi_0.awaddr  = s_axi_0.awaddr  ;
        m_axi_0.awprot  = s_axi_0.awprot  ;
        m_axi_0.wvalid  = s_axi_0.wvalid  ;
        s_axi_0.wready  = m_axi_0.wready  ;
        m_axi_0.wdata   = s_axi_0.wdata   ;
        m_axi_0.wstrb   = s_axi_0.wstrb   ;
        s_axi_0.bvalid  = m_axi_0.bvalid  ;
        m_axi_0.bready  = s_axi_0.bready  ;
        s_axi_0.bresp   = m_axi_0.bresp   ;
        m_axi_0.arvalid = s_axi_0.arvalid ;
        s_axi_0.arready = m_axi_0.arready ;
        m_axi_0.araddr  = s_axi_0.araddr  ;
        m_axi_0.arprot  = s_axi_0.arprot  ;
        s_axi_0.rvalid  = m_axi_0.rvalid  ;
        m_axi_0.rready  = s_axi_0.rready  ;
        s_axi_0.rdata   = m_axi_0.rdata   ;
        s_axi_0.rresp   = m_axi_0.rresp   ;
        
    end
    else
    begin
        
        m_axi_0.awvalid = s_axi_1.awvalid ;
        s_axi_1.awready = m_axi_0.awready ;
        m_axi_0.awaddr  = s_axi_1.awaddr  ;
        m_axi_0.awprot  = s_axi_1.awprot  ;
        m_axi_0.wvalid  = s_axi_1.wvalid  ;
        s_axi_1.wready  = m_axi_0.wready  ;
        m_axi_0.wdata   = s_axi_1.wdata   ;
        m_axi_0.wstrb   = s_axi_1.wstrb   ;
        s_axi_1.bvalid  = m_axi_0.bvalid  ;
        m_axi_0.bready  = s_axi_1.bready  ;
        s_axi_1.bresp   = m_axi_0.bresp   ;
        m_axi_0.arvalid = s_axi_1.arvalid ;
        s_axi_1.arready = m_axi_0.arready ;
        m_axi_0.araddr  = s_axi_1.araddr  ;
        m_axi_0.arprot  = s_axi_1.arprot  ;
        s_axi_1.rvalid  = m_axi_0.rvalid  ;
        m_axi_0.rready  = s_axi_1.rready  ;
        s_axi_1.rdata   = m_axi_0.rdata   ;
        s_axi_1.rresp   = m_axi_0.rresp   ;
        
    end
    
end

endmodule
