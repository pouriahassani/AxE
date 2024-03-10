
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module if_wrapper_noc_3x3_16
#()
(
     input clk
    ,input res_n
    
    ,if_connect.noc noc_0
    ,if_connect.noc noc_1
    ,if_connect.noc noc_2
    ,if_connect.noc noc_3
    ,if_connect.noc noc_4
    ,if_connect.noc noc_5
    ,if_connect.noc noc_6
    ,if_connect.noc noc_7
    ,if_connect.noc noc_8
);
    
    // 0
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_0_putFlit_flit_in          ; assign   w_send_ports_0_putFlit_flit_in          = noc_0.put_flit                    ;
    wire                         w_EN_send_ports_0_putFlit               ; assign   w_EN_send_ports_0_putFlit               = noc_0.en_put                      ;
    wire                         w_EN_send_ports_0_getNonFullVCs         ; assign   w_EN_send_ports_0_getNonFullVCs         = noc_0.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_0_getNonFullVCs            ; assign   noc_0.get_non_full_VCs                  = w_send_ports_0_getNonFullVCs      ;
    wire                         w_EN_recv_ports_0_getFlit               ; assign   w_EN_recv_ports_0_getFlit               = noc_0.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_0_getFlit                  ; assign   noc_0.get_flit                          = w_recv_ports_0_getFlit            ;
    wire [                1 : 0] w_recv_ports_0_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_0_putNonFullVCs_nonFullVCs = noc_0.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_0_putNonFullVCs         ; assign   w_EN_recv_ports_0_putNonFullVCs         = noc_0.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_0_getRecvPortID       ; assign   noc_0.this_id                           = w_recv_ports_info_0_getRecvPortID ;
    
    // 1
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_1_putFlit_flit_in          ; assign   w_send_ports_1_putFlit_flit_in          = noc_1.put_flit                    ;
    wire                         w_EN_send_ports_1_putFlit               ; assign   w_EN_send_ports_1_putFlit               = noc_1.en_put                      ;
    wire                         w_EN_send_ports_1_getNonFullVCs         ; assign   w_EN_send_ports_1_getNonFullVCs         = noc_1.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_1_getNonFullVCs            ; assign   noc_1.get_non_full_VCs                  = w_send_ports_1_getNonFullVCs      ;
    wire                         w_EN_recv_ports_1_getFlit               ; assign   w_EN_recv_ports_1_getFlit               = noc_1.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_1_getFlit                  ; assign   noc_1.get_flit                          = w_recv_ports_1_getFlit            ;
    wire [                1 : 0] w_recv_ports_1_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_1_putNonFullVCs_nonFullVCs = noc_1.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_1_putNonFullVCs         ; assign   w_EN_recv_ports_1_putNonFullVCs         = noc_1.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_1_getRecvPortID       ; assign   noc_1.this_id                           = w_recv_ports_info_1_getRecvPortID ;
    
    // 2
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_2_putFlit_flit_in          ; assign   w_send_ports_2_putFlit_flit_in          = noc_2.put_flit                    ;
    wire                         w_EN_send_ports_2_putFlit               ; assign   w_EN_send_ports_2_putFlit               = noc_2.en_put                      ;
    wire                         w_EN_send_ports_2_getNonFullVCs         ; assign   w_EN_send_ports_2_getNonFullVCs         = noc_2.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_2_getNonFullVCs            ; assign   noc_2.get_non_full_VCs                  = w_send_ports_2_getNonFullVCs      ;
    wire                         w_EN_recv_ports_2_getFlit               ; assign   w_EN_recv_ports_2_getFlit               = noc_2.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_2_getFlit                  ; assign   noc_2.get_flit                          = w_recv_ports_2_getFlit            ;
    wire [                1 : 0] w_recv_ports_2_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_2_putNonFullVCs_nonFullVCs = noc_2.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_2_putNonFullVCs         ; assign   w_EN_recv_ports_2_putNonFullVCs         = noc_2.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_2_getRecvPortID       ; assign   noc_2.this_id                           = w_recv_ports_info_2_getRecvPortID ;
    
    // 3
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_3_putFlit_flit_in          ; assign   w_send_ports_3_putFlit_flit_in          = noc_3.put_flit                    ;
    wire                         w_EN_send_ports_3_putFlit               ; assign   w_EN_send_ports_3_putFlit               = noc_3.en_put                      ;
    wire                         w_EN_send_ports_3_getNonFullVCs         ; assign   w_EN_send_ports_3_getNonFullVCs         = noc_3.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_3_getNonFullVCs            ; assign   noc_3.get_non_full_VCs                  = w_send_ports_3_getNonFullVCs      ;
    wire                         w_EN_recv_ports_3_getFlit               ; assign   w_EN_recv_ports_3_getFlit               = noc_3.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_3_getFlit                  ; assign   noc_3.get_flit                          = w_recv_ports_3_getFlit            ;
    wire [                1 : 0] w_recv_ports_3_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_3_putNonFullVCs_nonFullVCs = noc_3.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_3_putNonFullVCs         ; assign   w_EN_recv_ports_3_putNonFullVCs         = noc_3.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_3_getRecvPortID       ; assign   noc_3.this_id                           = w_recv_ports_info_3_getRecvPortID ;
    
    // 4
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_4_putFlit_flit_in          ; assign   w_send_ports_4_putFlit_flit_in          = noc_4.put_flit                    ;
    wire                         w_EN_send_ports_4_putFlit               ; assign   w_EN_send_ports_4_putFlit               = noc_4.en_put                      ;
    wire                         w_EN_send_ports_4_getNonFullVCs         ; assign   w_EN_send_ports_4_getNonFullVCs         = noc_4.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_4_getNonFullVCs            ; assign   noc_4.get_non_full_VCs                  = w_send_ports_4_getNonFullVCs      ;
    wire                         w_EN_recv_ports_4_getFlit               ; assign   w_EN_recv_ports_4_getFlit               = noc_4.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_4_getFlit                  ; assign   noc_4.get_flit                          = w_recv_ports_4_getFlit            ;
    wire [                1 : 0] w_recv_ports_4_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_4_putNonFullVCs_nonFullVCs = noc_4.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_4_putNonFullVCs         ; assign   w_EN_recv_ports_4_putNonFullVCs         = noc_4.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_4_getRecvPortID       ; assign   noc_4.this_id                           = w_recv_ports_info_4_getRecvPortID ;
    
    // 5
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_5_putFlit_flit_in          ; assign   w_send_ports_5_putFlit_flit_in          = noc_5.put_flit                    ;
    wire                         w_EN_send_ports_5_putFlit               ; assign   w_EN_send_ports_5_putFlit               = noc_5.en_put                      ;
    wire                         w_EN_send_ports_5_getNonFullVCs         ; assign   w_EN_send_ports_5_getNonFullVCs         = noc_5.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_5_getNonFullVCs            ; assign   noc_5.get_non_full_VCs                  = w_send_ports_5_getNonFullVCs      ;
    wire                         w_EN_recv_ports_5_getFlit               ; assign   w_EN_recv_ports_5_getFlit               = noc_5.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_5_getFlit                  ; assign   noc_5.get_flit                          = w_recv_ports_5_getFlit            ;
    wire [                1 : 0] w_recv_ports_5_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_5_putNonFullVCs_nonFullVCs = noc_5.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_5_putNonFullVCs         ; assign   w_EN_recv_ports_5_putNonFullVCs         = noc_5.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_5_getRecvPortID       ; assign   noc_5.this_id                           = w_recv_ports_info_5_getRecvPortID ;
    
    // 6
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_6_putFlit_flit_in          ; assign   w_send_ports_6_putFlit_flit_in          = noc_6.put_flit                    ;
    wire                         w_EN_send_ports_6_putFlit               ; assign   w_EN_send_ports_6_putFlit               = noc_6.en_put                      ;
    wire                         w_EN_send_ports_6_getNonFullVCs         ; assign   w_EN_send_ports_6_getNonFullVCs         = noc_6.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_6_getNonFullVCs            ; assign   noc_6.get_non_full_VCs                  = w_send_ports_6_getNonFullVCs      ;
    wire                         w_EN_recv_ports_6_getFlit               ; assign   w_EN_recv_ports_6_getFlit               = noc_6.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_6_getFlit                  ; assign   noc_6.get_flit                          = w_recv_ports_6_getFlit            ;
    wire [                1 : 0] w_recv_ports_6_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_6_putNonFullVCs_nonFullVCs = noc_6.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_6_putNonFullVCs         ; assign   w_EN_recv_ports_6_putNonFullVCs         = noc_6.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_6_getRecvPortID       ; assign   noc_6.this_id                           = w_recv_ports_info_6_getRecvPortID ;
    
    // 7
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_7_putFlit_flit_in          ; assign   w_send_ports_7_putFlit_flit_in          = noc_7.put_flit                    ;
    wire                         w_EN_send_ports_7_putFlit               ; assign   w_EN_send_ports_7_putFlit               = noc_7.en_put                      ;
    wire                         w_EN_send_ports_7_getNonFullVCs         ; assign   w_EN_send_ports_7_getNonFullVCs         = noc_7.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_7_getNonFullVCs            ; assign   noc_7.get_non_full_VCs                  = w_send_ports_7_getNonFullVCs      ;
    wire                         w_EN_recv_ports_7_getFlit               ; assign   w_EN_recv_ports_7_getFlit               = noc_7.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_7_getFlit                  ; assign   noc_7.get_flit                          = w_recv_ports_7_getFlit            ;
    wire [                1 : 0] w_recv_ports_7_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_7_putNonFullVCs_nonFullVCs = noc_7.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_7_putNonFullVCs         ; assign   w_EN_recv_ports_7_putNonFullVCs         = noc_7.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_7_getRecvPortID       ; assign   noc_7.this_id                           = w_recv_ports_info_7_getRecvPortID ;
    
    // 8
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_8_putFlit_flit_in          ; assign   w_send_ports_8_putFlit_flit_in          = noc_8.put_flit                    ;
    wire                         w_EN_send_ports_8_putFlit               ; assign   w_EN_send_ports_8_putFlit               = noc_8.en_put                      ;
    wire                         w_EN_send_ports_8_getNonFullVCs         ; assign   w_EN_send_ports_8_getNonFullVCs         = noc_8.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_8_getNonFullVCs            ; assign   noc_8.get_non_full_VCs                  = w_send_ports_8_getNonFullVCs      ;
    wire                         w_EN_recv_ports_8_getFlit               ; assign   w_EN_recv_ports_8_getFlit               = noc_8.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_8_getFlit                  ; assign   noc_8.get_flit                          = w_recv_ports_8_getFlit            ;
    wire [                1 : 0] w_recv_ports_8_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_8_putNonFullVCs_nonFullVCs = noc_8.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_8_putNonFullVCs         ; assign   w_EN_recv_ports_8_putNonFullVCs         = noc_8.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_8_getRecvPortID       ; assign   noc_8.this_id                           = w_recv_ports_info_8_getRecvPortID ;
    
    mkNetworkSimple #() mkNetworkSimple_inst
    (
         .CLK( clk )
        ,.RST_N( res_n )
        
        // 0
        
        ,.EN_recv_ports_0_getFlit               ( w_EN_recv_ports_0_getFlit               )
        ,.recv_ports_0_getFlit                  ( w_recv_ports_0_getFlit                  )
        ,.recv_ports_0_putNonFullVCs_nonFullVCs ( w_recv_ports_0_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_0_putNonFullVCs         ( w_EN_recv_ports_0_putNonFullVCs         )
        ,.send_ports_0_putFlit_flit_in          ( w_send_ports_0_putFlit_flit_in          )
        ,.EN_send_ports_0_putFlit               ( w_EN_send_ports_0_putFlit               )
        ,.EN_send_ports_0_getNonFullVCs         ( w_EN_send_ports_0_getNonFullVCs         )
        ,.send_ports_0_getNonFullVCs            ( w_send_ports_0_getNonFullVCs            )
        ,.recv_ports_info_0_getRecvPortID       ( w_recv_ports_info_0_getRecvPortID       )
        
        // 1
        
        ,.EN_recv_ports_1_getFlit               ( w_EN_recv_ports_1_getFlit               )
        ,.recv_ports_1_getFlit                  ( w_recv_ports_1_getFlit                  )
        ,.recv_ports_1_putNonFullVCs_nonFullVCs ( w_recv_ports_1_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_1_putNonFullVCs         ( w_EN_recv_ports_1_putNonFullVCs         )
        ,.send_ports_1_putFlit_flit_in          ( w_send_ports_1_putFlit_flit_in          )
        ,.EN_send_ports_1_putFlit               ( w_EN_send_ports_1_putFlit               )
        ,.EN_send_ports_1_getNonFullVCs         ( w_EN_send_ports_1_getNonFullVCs         )
        ,.send_ports_1_getNonFullVCs            ( w_send_ports_1_getNonFullVCs            )
        ,.recv_ports_info_1_getRecvPortID       ( w_recv_ports_info_1_getRecvPortID       )
        
        // 2
        
        ,.EN_recv_ports_2_getFlit               ( w_EN_recv_ports_2_getFlit               )
        ,.recv_ports_2_getFlit                  ( w_recv_ports_2_getFlit                  )
        ,.recv_ports_2_putNonFullVCs_nonFullVCs ( w_recv_ports_2_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_2_putNonFullVCs         ( w_EN_recv_ports_2_putNonFullVCs         )
        ,.send_ports_2_putFlit_flit_in          ( w_send_ports_2_putFlit_flit_in          )
        ,.EN_send_ports_2_putFlit               ( w_EN_send_ports_2_putFlit               )
        ,.EN_send_ports_2_getNonFullVCs         ( w_EN_send_ports_2_getNonFullVCs         )
        ,.send_ports_2_getNonFullVCs            ( w_send_ports_2_getNonFullVCs            )
        ,.recv_ports_info_2_getRecvPortID       ( w_recv_ports_info_2_getRecvPortID       )
        
        // 3
        
        ,.EN_recv_ports_3_getFlit               ( w_EN_recv_ports_3_getFlit               )
        ,.recv_ports_3_getFlit                  ( w_recv_ports_3_getFlit                  )
        ,.recv_ports_3_putNonFullVCs_nonFullVCs ( w_recv_ports_3_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_3_putNonFullVCs         ( w_EN_recv_ports_3_putNonFullVCs         )
        ,.send_ports_3_putFlit_flit_in          ( w_send_ports_3_putFlit_flit_in          )
        ,.EN_send_ports_3_putFlit               ( w_EN_send_ports_3_putFlit               )
        ,.EN_send_ports_3_getNonFullVCs         ( w_EN_send_ports_3_getNonFullVCs         )
        ,.send_ports_3_getNonFullVCs            ( w_send_ports_3_getNonFullVCs            )
        ,.recv_ports_info_3_getRecvPortID       ( w_recv_ports_info_3_getRecvPortID       )
        
        // 4
        
        ,.EN_recv_ports_4_getFlit               ( w_EN_recv_ports_4_getFlit               )
        ,.recv_ports_4_getFlit                  ( w_recv_ports_4_getFlit                  )
        ,.recv_ports_4_putNonFullVCs_nonFullVCs ( w_recv_ports_4_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_4_putNonFullVCs         ( w_EN_recv_ports_4_putNonFullVCs         )
        ,.send_ports_4_putFlit_flit_in          ( w_send_ports_4_putFlit_flit_in          )
        ,.EN_send_ports_4_putFlit               ( w_EN_send_ports_4_putFlit               )
        ,.EN_send_ports_4_getNonFullVCs         ( w_EN_send_ports_4_getNonFullVCs         )
        ,.send_ports_4_getNonFullVCs            ( w_send_ports_4_getNonFullVCs            )
        ,.recv_ports_info_4_getRecvPortID       ( w_recv_ports_info_4_getRecvPortID       )
        
        // 5
        
        ,.EN_recv_ports_5_getFlit               ( w_EN_recv_ports_5_getFlit               )
        ,.recv_ports_5_getFlit                  ( w_recv_ports_5_getFlit                  )
        ,.recv_ports_5_putNonFullVCs_nonFullVCs ( w_recv_ports_5_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_5_putNonFullVCs         ( w_EN_recv_ports_5_putNonFullVCs         )
        ,.send_ports_5_putFlit_flit_in          ( w_send_ports_5_putFlit_flit_in          )
        ,.EN_send_ports_5_putFlit               ( w_EN_send_ports_5_putFlit               )
        ,.EN_send_ports_5_getNonFullVCs         ( w_EN_send_ports_5_getNonFullVCs         )
        ,.send_ports_5_getNonFullVCs            ( w_send_ports_5_getNonFullVCs            )
        ,.recv_ports_info_5_getRecvPortID       ( w_recv_ports_info_5_getRecvPortID       )
        
        // 6
        
        ,.EN_recv_ports_6_getFlit               ( w_EN_recv_ports_6_getFlit               )
        ,.recv_ports_6_getFlit                  ( w_recv_ports_6_getFlit                  )
        ,.recv_ports_6_putNonFullVCs_nonFullVCs ( w_recv_ports_6_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_6_putNonFullVCs         ( w_EN_recv_ports_6_putNonFullVCs         )
        ,.send_ports_6_putFlit_flit_in          ( w_send_ports_6_putFlit_flit_in          )
        ,.EN_send_ports_6_putFlit               ( w_EN_send_ports_6_putFlit               )
        ,.EN_send_ports_6_getNonFullVCs         ( w_EN_send_ports_6_getNonFullVCs         )
        ,.send_ports_6_getNonFullVCs            ( w_send_ports_6_getNonFullVCs            )
        ,.recv_ports_info_6_getRecvPortID       ( w_recv_ports_info_6_getRecvPortID       )
        
        // 7
        
        ,.EN_recv_ports_7_getFlit               ( w_EN_recv_ports_7_getFlit               )
        ,.recv_ports_7_getFlit                  ( w_recv_ports_7_getFlit                  )
        ,.recv_ports_7_putNonFullVCs_nonFullVCs ( w_recv_ports_7_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_7_putNonFullVCs         ( w_EN_recv_ports_7_putNonFullVCs         )
        ,.send_ports_7_putFlit_flit_in          ( w_send_ports_7_putFlit_flit_in          )
        ,.EN_send_ports_7_putFlit               ( w_EN_send_ports_7_putFlit               )
        ,.EN_send_ports_7_getNonFullVCs         ( w_EN_send_ports_7_getNonFullVCs         )
        ,.send_ports_7_getNonFullVCs            ( w_send_ports_7_getNonFullVCs            )
        ,.recv_ports_info_7_getRecvPortID       ( w_recv_ports_info_7_getRecvPortID       )
        
        // 8
        
        ,.EN_recv_ports_8_getFlit               ( w_EN_recv_ports_8_getFlit               )
        ,.recv_ports_8_getFlit                  ( w_recv_ports_8_getFlit                  )
        ,.recv_ports_8_putNonFullVCs_nonFullVCs ( w_recv_ports_8_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_8_putNonFullVCs         ( w_EN_recv_ports_8_putNonFullVCs         )
        ,.send_ports_8_putFlit_flit_in          ( w_send_ports_8_putFlit_flit_in          )
        ,.EN_send_ports_8_putFlit               ( w_EN_send_ports_8_putFlit               )
        ,.EN_send_ports_8_getNonFullVCs         ( w_EN_send_ports_8_getNonFullVCs         )
        ,.send_ports_8_getNonFullVCs            ( w_send_ports_8_getNonFullVCs            )
        ,.recv_ports_info_8_getRecvPortID       ( w_recv_ports_info_8_getRecvPortID       )
        
    );
    
endmodule
