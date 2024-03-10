
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

interface if_connect
#()
();
    
    logic [`FLIT_WIDTH-1 : 0] put_flit;
    logic                     en_put;
    
    logic                     en_get_non_full_VCs;
    logic [            1 : 0] get_non_full_VCs;
    
    logic                     en_get;
    logic [`FLIT_WIDTH-1 : 0] get_flit;
    
    logic [            1 : 0] put_non_full_VCs;
    logic                     en_put_non_full_VCs;
    
    logic [`NOC_NODE_WIDTH-1 : 0] this_id;
    
    modport noc
    (
         input  put_flit
        ,input  en_put
        
        ,input  en_get_non_full_VCs
        ,output get_non_full_VCs
        
        ,input  en_get
        ,output get_flit
        
        ,input  put_non_full_VCs
        ,input  en_put_non_full_VCs
        
        ,output this_id
    );
    
    modport bridge
    (
         output put_flit
        ,output en_put
        
        ,output en_get_non_full_VCs
        ,input  get_non_full_VCs
        
        ,output en_get
        ,input  get_flit
        
        ,output put_non_full_VCs
        ,output en_put_non_full_VCs
        
        ,input  this_id
    );
    
endinterface
