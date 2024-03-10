
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module if_wrapper_noc_4x4_16_eep
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
    ,if_connect.noc noc_9
    ,if_connect.noc noc_10
    ,if_connect.noc noc_11
    ,if_connect.noc noc_12
    ,if_connect.noc noc_13
    ,if_connect.noc noc_14
    ,if_connect.noc noc_15
    ,if_connect.noc noc_16
    ,if_connect.noc noc_17
    ,if_connect.noc noc_18
    ,if_connect.noc noc_19
    ,if_connect.noc noc_20
    ,if_connect.noc noc_21
    ,if_connect.noc noc_22
    ,if_connect.noc noc_23
    ,if_connect.noc noc_24
    ,if_connect.noc noc_25
    ,if_connect.noc noc_26
    ,if_connect.noc noc_27
    ,if_connect.noc noc_28
    ,if_connect.noc noc_29
    ,if_connect.noc noc_30
    ,if_connect.noc noc_31
    
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
    
    // 9
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_9_putFlit_flit_in          ; assign   w_send_ports_9_putFlit_flit_in          = noc_9.put_flit                    ;
    wire                         w_EN_send_ports_9_putFlit               ; assign   w_EN_send_ports_9_putFlit               = noc_9.en_put                      ;
    wire                         w_EN_send_ports_9_getNonFullVCs         ; assign   w_EN_send_ports_9_getNonFullVCs         = noc_9.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_9_getNonFullVCs            ; assign   noc_9.get_non_full_VCs                  = w_send_ports_9_getNonFullVCs      ;
    wire                         w_EN_recv_ports_9_getFlit               ; assign   w_EN_recv_ports_9_getFlit               = noc_9.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_9_getFlit                  ; assign   noc_9.get_flit                          = w_recv_ports_9_getFlit            ;
    wire [                1 : 0] w_recv_ports_9_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_9_putNonFullVCs_nonFullVCs = noc_9.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_9_putNonFullVCs         ; assign   w_EN_recv_ports_9_putNonFullVCs         = noc_9.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_9_getRecvPortID       ; assign   noc_9.this_id                           = w_recv_ports_info_9_getRecvPortID ;
    
    // 10
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_10_putFlit_flit_in          ; assign   w_send_ports_10_putFlit_flit_in          = noc_10.put_flit                    ;
    wire                         w_EN_send_ports_10_putFlit               ; assign   w_EN_send_ports_10_putFlit               = noc_10.en_put                      ;
    wire                         w_EN_send_ports_10_getNonFullVCs         ; assign   w_EN_send_ports_10_getNonFullVCs         = noc_10.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_10_getNonFullVCs            ; assign   noc_10.get_non_full_VCs                  = w_send_ports_10_getNonFullVCs      ;
    wire                         w_EN_recv_ports_10_getFlit               ; assign   w_EN_recv_ports_10_getFlit               = noc_10.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_10_getFlit                  ; assign   noc_10.get_flit                          = w_recv_ports_10_getFlit            ;
    wire [                1 : 0] w_recv_ports_10_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_10_putNonFullVCs_nonFullVCs = noc_10.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_10_putNonFullVCs         ; assign   w_EN_recv_ports_10_putNonFullVCs         = noc_10.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_10_getRecvPortID       ; assign   noc_10.this_id                           = w_recv_ports_info_10_getRecvPortID ;
    
    // 11
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_11_putFlit_flit_in          ; assign   w_send_ports_11_putFlit_flit_in          = noc_11.put_flit                    ;
    wire                         w_EN_send_ports_11_putFlit               ; assign   w_EN_send_ports_11_putFlit               = noc_11.en_put                      ;
    wire                         w_EN_send_ports_11_getNonFullVCs         ; assign   w_EN_send_ports_11_getNonFullVCs         = noc_11.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_11_getNonFullVCs            ; assign   noc_11.get_non_full_VCs                  = w_send_ports_11_getNonFullVCs      ;
    wire                         w_EN_recv_ports_11_getFlit               ; assign   w_EN_recv_ports_11_getFlit               = noc_11.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_11_getFlit                  ; assign   noc_11.get_flit                          = w_recv_ports_11_getFlit            ;
    wire [                1 : 0] w_recv_ports_11_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_11_putNonFullVCs_nonFullVCs = noc_11.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_11_putNonFullVCs         ; assign   w_EN_recv_ports_11_putNonFullVCs         = noc_11.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_11_getRecvPortID       ; assign   noc_11.this_id                           = w_recv_ports_info_11_getRecvPortID ;
    
    // 12
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_12_putFlit_flit_in          ; assign   w_send_ports_12_putFlit_flit_in          = noc_12.put_flit                    ;
    wire                         w_EN_send_ports_12_putFlit               ; assign   w_EN_send_ports_12_putFlit               = noc_12.en_put                      ;
    wire                         w_EN_send_ports_12_getNonFullVCs         ; assign   w_EN_send_ports_12_getNonFullVCs         = noc_12.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_12_getNonFullVCs            ; assign   noc_12.get_non_full_VCs                  = w_send_ports_12_getNonFullVCs      ;
    wire                         w_EN_recv_ports_12_getFlit               ; assign   w_EN_recv_ports_12_getFlit               = noc_12.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_12_getFlit                  ; assign   noc_12.get_flit                          = w_recv_ports_12_getFlit            ;
    wire [                1 : 0] w_recv_ports_12_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_12_putNonFullVCs_nonFullVCs = noc_12.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_12_putNonFullVCs         ; assign   w_EN_recv_ports_12_putNonFullVCs         = noc_12.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_12_getRecvPortID       ; assign   noc_12.this_id                           = w_recv_ports_info_12_getRecvPortID ;
    
    // 13
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_13_putFlit_flit_in          ; assign   w_send_ports_13_putFlit_flit_in          = noc_13.put_flit                    ;
    wire                         w_EN_send_ports_13_putFlit               ; assign   w_EN_send_ports_13_putFlit               = noc_13.en_put                      ;
    wire                         w_EN_send_ports_13_getNonFullVCs         ; assign   w_EN_send_ports_13_getNonFullVCs         = noc_13.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_13_getNonFullVCs            ; assign   noc_13.get_non_full_VCs                  = w_send_ports_13_getNonFullVCs      ;
    wire                         w_EN_recv_ports_13_getFlit               ; assign   w_EN_recv_ports_13_getFlit               = noc_13.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_13_getFlit                  ; assign   noc_13.get_flit                          = w_recv_ports_13_getFlit            ;
    wire [                1 : 0] w_recv_ports_13_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_13_putNonFullVCs_nonFullVCs = noc_13.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_13_putNonFullVCs         ; assign   w_EN_recv_ports_13_putNonFullVCs         = noc_13.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_13_getRecvPortID       ; assign   noc_13.this_id                           = w_recv_ports_info_13_getRecvPortID ;
    
    // 14
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_14_putFlit_flit_in          ; assign   w_send_ports_14_putFlit_flit_in          = noc_14.put_flit                    ;
    wire                         w_EN_send_ports_14_putFlit               ; assign   w_EN_send_ports_14_putFlit               = noc_14.en_put                      ;
    wire                         w_EN_send_ports_14_getNonFullVCs         ; assign   w_EN_send_ports_14_getNonFullVCs         = noc_14.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_14_getNonFullVCs            ; assign   noc_14.get_non_full_VCs                  = w_send_ports_14_getNonFullVCs      ;
    wire                         w_EN_recv_ports_14_getFlit               ; assign   w_EN_recv_ports_14_getFlit               = noc_14.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_14_getFlit                  ; assign   noc_14.get_flit                          = w_recv_ports_14_getFlit            ;
    wire [                1 : 0] w_recv_ports_14_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_14_putNonFullVCs_nonFullVCs = noc_14.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_14_putNonFullVCs         ; assign   w_EN_recv_ports_14_putNonFullVCs         = noc_14.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_14_getRecvPortID       ; assign   noc_14.this_id                           = w_recv_ports_info_14_getRecvPortID ;
    
    // 15
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_15_putFlit_flit_in          ; assign   w_send_ports_15_putFlit_flit_in          = noc_15.put_flit                    ;
    wire                         w_EN_send_ports_15_putFlit               ; assign   w_EN_send_ports_15_putFlit               = noc_15.en_put                      ;
    wire                         w_EN_send_ports_15_getNonFullVCs         ; assign   w_EN_send_ports_15_getNonFullVCs         = noc_15.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_15_getNonFullVCs            ; assign   noc_15.get_non_full_VCs                  = w_send_ports_15_getNonFullVCs      ;
    wire                         w_EN_recv_ports_15_getFlit               ; assign   w_EN_recv_ports_15_getFlit               = noc_15.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_15_getFlit                  ; assign   noc_15.get_flit                          = w_recv_ports_15_getFlit            ;
    wire [                1 : 0] w_recv_ports_15_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_15_putNonFullVCs_nonFullVCs = noc_15.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_15_putNonFullVCs         ; assign   w_EN_recv_ports_15_putNonFullVCs         = noc_15.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_15_getRecvPortID       ; assign   noc_15.this_id                           = w_recv_ports_info_15_getRecvPortID ;
    
    // 16
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_16_putFlit_flit_in          ; assign   w_send_ports_16_putFlit_flit_in          = noc_16.put_flit                    ;
    wire                         w_EN_send_ports_16_putFlit               ; assign   w_EN_send_ports_16_putFlit               = noc_16.en_put                      ;
    wire                         w_EN_send_ports_16_getNonFullVCs         ; assign   w_EN_send_ports_16_getNonFullVCs         = noc_16.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_16_getNonFullVCs            ; assign   noc_16.get_non_full_VCs                  = w_send_ports_16_getNonFullVCs      ;
    wire                         w_EN_recv_ports_16_getFlit               ; assign   w_EN_recv_ports_16_getFlit               = noc_16.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_16_getFlit                  ; assign   noc_16.get_flit                          = w_recv_ports_16_getFlit            ;
    wire [                1 : 0] w_recv_ports_16_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_16_putNonFullVCs_nonFullVCs = noc_16.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_16_putNonFullVCs         ; assign   w_EN_recv_ports_16_putNonFullVCs         = noc_16.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_16_getRecvPortID       ; assign   noc_16.this_id                           = w_recv_ports_info_16_getRecvPortID ;
    
    // 17
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_17_putFlit_flit_in          ; assign   w_send_ports_17_putFlit_flit_in          = noc_17.put_flit                    ;
    wire                         w_EN_send_ports_17_putFlit               ; assign   w_EN_send_ports_17_putFlit               = noc_17.en_put                      ;
    wire                         w_EN_send_ports_17_getNonFullVCs         ; assign   w_EN_send_ports_17_getNonFullVCs         = noc_17.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_17_getNonFullVCs            ; assign   noc_17.get_non_full_VCs                  = w_send_ports_17_getNonFullVCs      ;
    wire                         w_EN_recv_ports_17_getFlit               ; assign   w_EN_recv_ports_17_getFlit               = noc_17.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_17_getFlit                  ; assign   noc_17.get_flit                          = w_recv_ports_17_getFlit            ;
    wire [                1 : 0] w_recv_ports_17_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_17_putNonFullVCs_nonFullVCs = noc_17.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_17_putNonFullVCs         ; assign   w_EN_recv_ports_17_putNonFullVCs         = noc_17.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_17_getRecvPortID       ; assign   noc_17.this_id                           = w_recv_ports_info_17_getRecvPortID ;
    
    // 18
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_18_putFlit_flit_in          ; assign   w_send_ports_18_putFlit_flit_in          = noc_18.put_flit                    ;
    wire                         w_EN_send_ports_18_putFlit               ; assign   w_EN_send_ports_18_putFlit               = noc_18.en_put                      ;
    wire                         w_EN_send_ports_18_getNonFullVCs         ; assign   w_EN_send_ports_18_getNonFullVCs         = noc_18.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_18_getNonFullVCs            ; assign   noc_18.get_non_full_VCs                  = w_send_ports_18_getNonFullVCs      ;
    wire                         w_EN_recv_ports_18_getFlit               ; assign   w_EN_recv_ports_18_getFlit               = noc_18.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_18_getFlit                  ; assign   noc_18.get_flit                          = w_recv_ports_18_getFlit            ;
    wire [                1 : 0] w_recv_ports_18_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_18_putNonFullVCs_nonFullVCs = noc_18.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_18_putNonFullVCs         ; assign   w_EN_recv_ports_18_putNonFullVCs         = noc_18.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_18_getRecvPortID       ; assign   noc_18.this_id                           = w_recv_ports_info_18_getRecvPortID ;
    
    // 19
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_19_putFlit_flit_in          ; assign   w_send_ports_19_putFlit_flit_in          = noc_19.put_flit                    ;
    wire                         w_EN_send_ports_19_putFlit               ; assign   w_EN_send_ports_19_putFlit               = noc_19.en_put                      ;
    wire                         w_EN_send_ports_19_getNonFullVCs         ; assign   w_EN_send_ports_19_getNonFullVCs         = noc_19.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_19_getNonFullVCs            ; assign   noc_19.get_non_full_VCs                  = w_send_ports_19_getNonFullVCs      ;
    wire                         w_EN_recv_ports_19_getFlit               ; assign   w_EN_recv_ports_19_getFlit               = noc_19.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_19_getFlit                  ; assign   noc_19.get_flit                          = w_recv_ports_19_getFlit            ;
    wire [                1 : 0] w_recv_ports_19_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_19_putNonFullVCs_nonFullVCs = noc_19.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_19_putNonFullVCs         ; assign   w_EN_recv_ports_19_putNonFullVCs         = noc_19.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_19_getRecvPortID       ; assign   noc_19.this_id                           = w_recv_ports_info_19_getRecvPortID ;
    
    // 20
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_20_putFlit_flit_in          ; assign   w_send_ports_20_putFlit_flit_in          = noc_20.put_flit                    ;
    wire                         w_EN_send_ports_20_putFlit               ; assign   w_EN_send_ports_20_putFlit               = noc_20.en_put                      ;
    wire                         w_EN_send_ports_20_getNonFullVCs         ; assign   w_EN_send_ports_20_getNonFullVCs         = noc_20.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_20_getNonFullVCs            ; assign   noc_20.get_non_full_VCs                  = w_send_ports_20_getNonFullVCs      ;
    wire                         w_EN_recv_ports_20_getFlit               ; assign   w_EN_recv_ports_20_getFlit               = noc_20.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_20_getFlit                  ; assign   noc_20.get_flit                          = w_recv_ports_20_getFlit            ;
    wire [                1 : 0] w_recv_ports_20_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_20_putNonFullVCs_nonFullVCs = noc_20.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_20_putNonFullVCs         ; assign   w_EN_recv_ports_20_putNonFullVCs         = noc_20.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_20_getRecvPortID       ; assign   noc_20.this_id                           = w_recv_ports_info_20_getRecvPortID ;
    
    // 21
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_21_putFlit_flit_in          ; assign   w_send_ports_21_putFlit_flit_in          = noc_21.put_flit                    ;
    wire                         w_EN_send_ports_21_putFlit               ; assign   w_EN_send_ports_21_putFlit               = noc_21.en_put                      ;
    wire                         w_EN_send_ports_21_getNonFullVCs         ; assign   w_EN_send_ports_21_getNonFullVCs         = noc_21.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_21_getNonFullVCs            ; assign   noc_21.get_non_full_VCs                  = w_send_ports_21_getNonFullVCs      ;
    wire                         w_EN_recv_ports_21_getFlit               ; assign   w_EN_recv_ports_21_getFlit               = noc_21.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_21_getFlit                  ; assign   noc_21.get_flit                          = w_recv_ports_21_getFlit            ;
    wire [                1 : 0] w_recv_ports_21_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_21_putNonFullVCs_nonFullVCs = noc_21.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_21_putNonFullVCs         ; assign   w_EN_recv_ports_21_putNonFullVCs         = noc_21.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_21_getRecvPortID       ; assign   noc_21.this_id                           = w_recv_ports_info_21_getRecvPortID ;
    
    // 22
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_22_putFlit_flit_in          ; assign   w_send_ports_22_putFlit_flit_in          = noc_22.put_flit                    ;
    wire                         w_EN_send_ports_22_putFlit               ; assign   w_EN_send_ports_22_putFlit               = noc_22.en_put                      ;
    wire                         w_EN_send_ports_22_getNonFullVCs         ; assign   w_EN_send_ports_22_getNonFullVCs         = noc_22.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_22_getNonFullVCs            ; assign   noc_22.get_non_full_VCs                  = w_send_ports_22_getNonFullVCs      ;
    wire                         w_EN_recv_ports_22_getFlit               ; assign   w_EN_recv_ports_22_getFlit               = noc_22.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_22_getFlit                  ; assign   noc_22.get_flit                          = w_recv_ports_22_getFlit            ;
    wire [                1 : 0] w_recv_ports_22_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_22_putNonFullVCs_nonFullVCs = noc_22.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_22_putNonFullVCs         ; assign   w_EN_recv_ports_22_putNonFullVCs         = noc_22.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_22_getRecvPortID       ; assign   noc_22.this_id                           = w_recv_ports_info_22_getRecvPortID ;
    
    // 23
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_23_putFlit_flit_in          ; assign   w_send_ports_23_putFlit_flit_in          = noc_23.put_flit                    ;
    wire                         w_EN_send_ports_23_putFlit               ; assign   w_EN_send_ports_23_putFlit               = noc_23.en_put                      ;
    wire                         w_EN_send_ports_23_getNonFullVCs         ; assign   w_EN_send_ports_23_getNonFullVCs         = noc_23.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_23_getNonFullVCs            ; assign   noc_23.get_non_full_VCs                  = w_send_ports_23_getNonFullVCs      ;
    wire                         w_EN_recv_ports_23_getFlit               ; assign   w_EN_recv_ports_23_getFlit               = noc_23.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_23_getFlit                  ; assign   noc_23.get_flit                          = w_recv_ports_23_getFlit            ;
    wire [                1 : 0] w_recv_ports_23_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_23_putNonFullVCs_nonFullVCs = noc_23.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_23_putNonFullVCs         ; assign   w_EN_recv_ports_23_putNonFullVCs         = noc_23.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_23_getRecvPortID       ; assign   noc_23.this_id                           = w_recv_ports_info_23_getRecvPortID ;
    
    // 24
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_24_putFlit_flit_in          ; assign   w_send_ports_24_putFlit_flit_in          = noc_24.put_flit                    ;
    wire                         w_EN_send_ports_24_putFlit               ; assign   w_EN_send_ports_24_putFlit               = noc_24.en_put                      ;
    wire                         w_EN_send_ports_24_getNonFullVCs         ; assign   w_EN_send_ports_24_getNonFullVCs         = noc_24.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_24_getNonFullVCs            ; assign   noc_24.get_non_full_VCs                  = w_send_ports_24_getNonFullVCs      ;
    wire                         w_EN_recv_ports_24_getFlit               ; assign   w_EN_recv_ports_24_getFlit               = noc_24.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_24_getFlit                  ; assign   noc_24.get_flit                          = w_recv_ports_24_getFlit            ;
    wire [                1 : 0] w_recv_ports_24_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_24_putNonFullVCs_nonFullVCs = noc_24.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_24_putNonFullVCs         ; assign   w_EN_recv_ports_24_putNonFullVCs         = noc_24.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_24_getRecvPortID       ; assign   noc_24.this_id                           = w_recv_ports_info_24_getRecvPortID ;
    
    // 25
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_25_putFlit_flit_in          ; assign   w_send_ports_25_putFlit_flit_in          = noc_25.put_flit                    ;
    wire                         w_EN_send_ports_25_putFlit               ; assign   w_EN_send_ports_25_putFlit               = noc_25.en_put                      ;
    wire                         w_EN_send_ports_25_getNonFullVCs         ; assign   w_EN_send_ports_25_getNonFullVCs         = noc_25.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_25_getNonFullVCs            ; assign   noc_25.get_non_full_VCs                  = w_send_ports_25_getNonFullVCs      ;
    wire                         w_EN_recv_ports_25_getFlit               ; assign   w_EN_recv_ports_25_getFlit               = noc_25.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_25_getFlit                  ; assign   noc_25.get_flit                          = w_recv_ports_25_getFlit            ;
    wire [                1 : 0] w_recv_ports_25_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_25_putNonFullVCs_nonFullVCs = noc_25.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_25_putNonFullVCs         ; assign   w_EN_recv_ports_25_putNonFullVCs         = noc_25.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_25_getRecvPortID       ; assign   noc_25.this_id                           = w_recv_ports_info_25_getRecvPortID ;
    
    // 26
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_26_putFlit_flit_in          ; assign   w_send_ports_26_putFlit_flit_in          = noc_26.put_flit                    ;
    wire                         w_EN_send_ports_26_putFlit               ; assign   w_EN_send_ports_26_putFlit               = noc_26.en_put                      ;
    wire                         w_EN_send_ports_26_getNonFullVCs         ; assign   w_EN_send_ports_26_getNonFullVCs         = noc_26.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_26_getNonFullVCs            ; assign   noc_26.get_non_full_VCs                  = w_send_ports_26_getNonFullVCs      ;
    wire                         w_EN_recv_ports_26_getFlit               ; assign   w_EN_recv_ports_26_getFlit               = noc_26.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_26_getFlit                  ; assign   noc_26.get_flit                          = w_recv_ports_26_getFlit            ;
    wire [                1 : 0] w_recv_ports_26_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_26_putNonFullVCs_nonFullVCs = noc_26.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_26_putNonFullVCs         ; assign   w_EN_recv_ports_26_putNonFullVCs         = noc_26.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_26_getRecvPortID       ; assign   noc_26.this_id                           = w_recv_ports_info_26_getRecvPortID ;
    
    // 27
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_27_putFlit_flit_in          ; assign   w_send_ports_27_putFlit_flit_in          = noc_27.put_flit                    ;
    wire                         w_EN_send_ports_27_putFlit               ; assign   w_EN_send_ports_27_putFlit               = noc_27.en_put                      ;
    wire                         w_EN_send_ports_27_getNonFullVCs         ; assign   w_EN_send_ports_27_getNonFullVCs         = noc_27.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_27_getNonFullVCs            ; assign   noc_27.get_non_full_VCs                  = w_send_ports_27_getNonFullVCs      ;
    wire                         w_EN_recv_ports_27_getFlit               ; assign   w_EN_recv_ports_27_getFlit               = noc_27.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_27_getFlit                  ; assign   noc_27.get_flit                          = w_recv_ports_27_getFlit            ;
    wire [                1 : 0] w_recv_ports_27_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_27_putNonFullVCs_nonFullVCs = noc_27.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_27_putNonFullVCs         ; assign   w_EN_recv_ports_27_putNonFullVCs         = noc_27.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_27_getRecvPortID       ; assign   noc_27.this_id                           = w_recv_ports_info_27_getRecvPortID ;
    
    // 28
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_28_putFlit_flit_in          ; assign   w_send_ports_28_putFlit_flit_in          = noc_28.put_flit                    ;
    wire                         w_EN_send_ports_28_putFlit               ; assign   w_EN_send_ports_28_putFlit               = noc_28.en_put                      ;
    wire                         w_EN_send_ports_28_getNonFullVCs         ; assign   w_EN_send_ports_28_getNonFullVCs         = noc_28.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_28_getNonFullVCs            ; assign   noc_28.get_non_full_VCs                  = w_send_ports_28_getNonFullVCs      ;
    wire                         w_EN_recv_ports_28_getFlit               ; assign   w_EN_recv_ports_28_getFlit               = noc_28.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_28_getFlit                  ; assign   noc_28.get_flit                          = w_recv_ports_28_getFlit            ;
    wire [                1 : 0] w_recv_ports_28_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_28_putNonFullVCs_nonFullVCs = noc_28.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_28_putNonFullVCs         ; assign   w_EN_recv_ports_28_putNonFullVCs         = noc_28.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_28_getRecvPortID       ; assign   noc_28.this_id                           = w_recv_ports_info_28_getRecvPortID ;
    
    // 29
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_29_putFlit_flit_in          ; assign   w_send_ports_29_putFlit_flit_in          = noc_29.put_flit                    ;
    wire                         w_EN_send_ports_29_putFlit               ; assign   w_EN_send_ports_29_putFlit               = noc_29.en_put                      ;
    wire                         w_EN_send_ports_29_getNonFullVCs         ; assign   w_EN_send_ports_29_getNonFullVCs         = noc_29.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_29_getNonFullVCs            ; assign   noc_29.get_non_full_VCs                  = w_send_ports_29_getNonFullVCs      ;
    wire                         w_EN_recv_ports_29_getFlit               ; assign   w_EN_recv_ports_29_getFlit               = noc_29.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_29_getFlit                  ; assign   noc_29.get_flit                          = w_recv_ports_29_getFlit            ;
    wire [                1 : 0] w_recv_ports_29_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_29_putNonFullVCs_nonFullVCs = noc_29.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_29_putNonFullVCs         ; assign   w_EN_recv_ports_29_putNonFullVCs         = noc_29.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_29_getRecvPortID       ; assign   noc_29.this_id                           = w_recv_ports_info_29_getRecvPortID ;
    
    // 30
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_30_putFlit_flit_in          ; assign   w_send_ports_30_putFlit_flit_in          = noc_30.put_flit                    ;
    wire                         w_EN_send_ports_30_putFlit               ; assign   w_EN_send_ports_30_putFlit               = noc_30.en_put                      ;
    wire                         w_EN_send_ports_30_getNonFullVCs         ; assign   w_EN_send_ports_30_getNonFullVCs         = noc_30.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_30_getNonFullVCs            ; assign   noc_30.get_non_full_VCs                  = w_send_ports_30_getNonFullVCs      ;
    wire                         w_EN_recv_ports_30_getFlit               ; assign   w_EN_recv_ports_30_getFlit               = noc_30.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_30_getFlit                  ; assign   noc_30.get_flit                          = w_recv_ports_30_getFlit            ;
    wire [                1 : 0] w_recv_ports_30_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_30_putNonFullVCs_nonFullVCs = noc_30.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_30_putNonFullVCs         ; assign   w_EN_recv_ports_30_putNonFullVCs         = noc_30.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_30_getRecvPortID       ; assign   noc_30.this_id                           = w_recv_ports_info_30_getRecvPortID ;
    
    // 31
    
    wire [    `FLIT_WIDTH-1 : 0] w_send_ports_31_putFlit_flit_in          ; assign   w_send_ports_31_putFlit_flit_in          = noc_31.put_flit                    ;
    wire                         w_EN_send_ports_31_putFlit               ; assign   w_EN_send_ports_31_putFlit               = noc_31.en_put                      ;
    wire                         w_EN_send_ports_31_getNonFullVCs         ; assign   w_EN_send_ports_31_getNonFullVCs         = noc_31.en_get_non_full_VCs         ;
    wire [                1 : 0] w_send_ports_31_getNonFullVCs            ; assign   noc_31.get_non_full_VCs                  = w_send_ports_31_getNonFullVCs      ;
    wire                         w_EN_recv_ports_31_getFlit               ; assign   w_EN_recv_ports_31_getFlit               = noc_31.en_get                      ;
    wire [    `FLIT_WIDTH-1 : 0] w_recv_ports_31_getFlit                  ; assign   noc_31.get_flit                          = w_recv_ports_31_getFlit            ;
    wire [                1 : 0] w_recv_ports_31_putNonFullVCs_nonFullVCs ; assign   w_recv_ports_31_putNonFullVCs_nonFullVCs = noc_31.put_non_full_VCs            ;
    wire                         w_EN_recv_ports_31_putNonFullVCs         ; assign   w_EN_recv_ports_31_putNonFullVCs         = noc_31.en_put_non_full_VCs         ;
    wire [`NOC_NODE_WIDTH-1 : 0] w_recv_ports_info_31_getRecvPortID       ; assign   noc_31.this_id                           = w_recv_ports_info_31_getRecvPortID ;
    
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
        
        // 9
        
        ,.EN_recv_ports_9_getFlit               ( w_EN_recv_ports_9_getFlit               )
        ,.recv_ports_9_getFlit                  ( w_recv_ports_9_getFlit                  )
        ,.recv_ports_9_putNonFullVCs_nonFullVCs ( w_recv_ports_9_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_9_putNonFullVCs         ( w_EN_recv_ports_9_putNonFullVCs         )
        ,.send_ports_9_putFlit_flit_in          ( w_send_ports_9_putFlit_flit_in          )
        ,.EN_send_ports_9_putFlit               ( w_EN_send_ports_9_putFlit               )
        ,.EN_send_ports_9_getNonFullVCs         ( w_EN_send_ports_9_getNonFullVCs         )
        ,.send_ports_9_getNonFullVCs            ( w_send_ports_9_getNonFullVCs            )
        ,.recv_ports_info_9_getRecvPortID       ( w_recv_ports_info_9_getRecvPortID       )
        
        // 10
        
        ,.EN_recv_ports_10_getFlit               ( w_EN_recv_ports_10_getFlit               )
        ,.recv_ports_10_getFlit                  ( w_recv_ports_10_getFlit                  )
        ,.recv_ports_10_putNonFullVCs_nonFullVCs ( w_recv_ports_10_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_10_putNonFullVCs         ( w_EN_recv_ports_10_putNonFullVCs         )
        ,.send_ports_10_putFlit_flit_in          ( w_send_ports_10_putFlit_flit_in          )
        ,.EN_send_ports_10_putFlit               ( w_EN_send_ports_10_putFlit               )
        ,.EN_send_ports_10_getNonFullVCs         ( w_EN_send_ports_10_getNonFullVCs         )
        ,.send_ports_10_getNonFullVCs            ( w_send_ports_10_getNonFullVCs            )
        ,.recv_ports_info_10_getRecvPortID       ( w_recv_ports_info_10_getRecvPortID       )
        
        // 11
        
        ,.EN_recv_ports_11_getFlit               ( w_EN_recv_ports_11_getFlit               )
        ,.recv_ports_11_getFlit                  ( w_recv_ports_11_getFlit                  )
        ,.recv_ports_11_putNonFullVCs_nonFullVCs ( w_recv_ports_11_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_11_putNonFullVCs         ( w_EN_recv_ports_11_putNonFullVCs         )
        ,.send_ports_11_putFlit_flit_in          ( w_send_ports_11_putFlit_flit_in          )
        ,.EN_send_ports_11_putFlit               ( w_EN_send_ports_11_putFlit               )
        ,.EN_send_ports_11_getNonFullVCs         ( w_EN_send_ports_11_getNonFullVCs         )
        ,.send_ports_11_getNonFullVCs            ( w_send_ports_11_getNonFullVCs            )
        ,.recv_ports_info_11_getRecvPortID       ( w_recv_ports_info_11_getRecvPortID       )
        
        // 12
        
        ,.EN_recv_ports_12_getFlit               ( w_EN_recv_ports_12_getFlit               )
        ,.recv_ports_12_getFlit                  ( w_recv_ports_12_getFlit                  )
        ,.recv_ports_12_putNonFullVCs_nonFullVCs ( w_recv_ports_12_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_12_putNonFullVCs         ( w_EN_recv_ports_12_putNonFullVCs         )
        ,.send_ports_12_putFlit_flit_in          ( w_send_ports_12_putFlit_flit_in          )
        ,.EN_send_ports_12_putFlit               ( w_EN_send_ports_12_putFlit               )
        ,.EN_send_ports_12_getNonFullVCs         ( w_EN_send_ports_12_getNonFullVCs         )
        ,.send_ports_12_getNonFullVCs            ( w_send_ports_12_getNonFullVCs            )
        ,.recv_ports_info_12_getRecvPortID       ( w_recv_ports_info_12_getRecvPortID       )
        
        // 13
        
        ,.EN_recv_ports_13_getFlit               ( w_EN_recv_ports_13_getFlit               )
        ,.recv_ports_13_getFlit                  ( w_recv_ports_13_getFlit                  )
        ,.recv_ports_13_putNonFullVCs_nonFullVCs ( w_recv_ports_13_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_13_putNonFullVCs         ( w_EN_recv_ports_13_putNonFullVCs         )
        ,.send_ports_13_putFlit_flit_in          ( w_send_ports_13_putFlit_flit_in          )
        ,.EN_send_ports_13_putFlit               ( w_EN_send_ports_13_putFlit               )
        ,.EN_send_ports_13_getNonFullVCs         ( w_EN_send_ports_13_getNonFullVCs         )
        ,.send_ports_13_getNonFullVCs            ( w_send_ports_13_getNonFullVCs            )
        ,.recv_ports_info_13_getRecvPortID       ( w_recv_ports_info_13_getRecvPortID       )
        
        // 14
        
        ,.EN_recv_ports_14_getFlit               ( w_EN_recv_ports_14_getFlit               )
        ,.recv_ports_14_getFlit                  ( w_recv_ports_14_getFlit                  )
        ,.recv_ports_14_putNonFullVCs_nonFullVCs ( w_recv_ports_14_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_14_putNonFullVCs         ( w_EN_recv_ports_14_putNonFullVCs         )
        ,.send_ports_14_putFlit_flit_in          ( w_send_ports_14_putFlit_flit_in          )
        ,.EN_send_ports_14_putFlit               ( w_EN_send_ports_14_putFlit               )
        ,.EN_send_ports_14_getNonFullVCs         ( w_EN_send_ports_14_getNonFullVCs         )
        ,.send_ports_14_getNonFullVCs            ( w_send_ports_14_getNonFullVCs            )
        ,.recv_ports_info_14_getRecvPortID       ( w_recv_ports_info_14_getRecvPortID       )
        
        // 15
        
        ,.EN_recv_ports_15_getFlit               ( w_EN_recv_ports_15_getFlit               )
        ,.recv_ports_15_getFlit                  ( w_recv_ports_15_getFlit                  )
        ,.recv_ports_15_putNonFullVCs_nonFullVCs ( w_recv_ports_15_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_15_putNonFullVCs         ( w_EN_recv_ports_15_putNonFullVCs         )
        ,.send_ports_15_putFlit_flit_in          ( w_send_ports_15_putFlit_flit_in          )
        ,.EN_send_ports_15_putFlit               ( w_EN_send_ports_15_putFlit               )
        ,.EN_send_ports_15_getNonFullVCs         ( w_EN_send_ports_15_getNonFullVCs         )
        ,.send_ports_15_getNonFullVCs            ( w_send_ports_15_getNonFullVCs            )
        ,.recv_ports_info_15_getRecvPortID       ( w_recv_ports_info_15_getRecvPortID       )
        
        // 16
        
        ,.EN_recv_ports_16_getFlit               ( w_EN_recv_ports_16_getFlit               )
        ,.recv_ports_16_getFlit                  ( w_recv_ports_16_getFlit                  )
        ,.recv_ports_16_putNonFullVCs_nonFullVCs ( w_recv_ports_16_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_16_putNonFullVCs         ( w_EN_recv_ports_16_putNonFullVCs         )
        ,.send_ports_16_putFlit_flit_in          ( w_send_ports_16_putFlit_flit_in          )
        ,.EN_send_ports_16_putFlit               ( w_EN_send_ports_16_putFlit               )
        ,.EN_send_ports_16_getNonFullVCs         ( w_EN_send_ports_16_getNonFullVCs         )
        ,.send_ports_16_getNonFullVCs            ( w_send_ports_16_getNonFullVCs            )
        ,.recv_ports_info_16_getRecvPortID       ( w_recv_ports_info_16_getRecvPortID       )
        
        // 17
        
        ,.EN_recv_ports_17_getFlit               ( w_EN_recv_ports_17_getFlit               )
        ,.recv_ports_17_getFlit                  ( w_recv_ports_17_getFlit                  )
        ,.recv_ports_17_putNonFullVCs_nonFullVCs ( w_recv_ports_17_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_17_putNonFullVCs         ( w_EN_recv_ports_17_putNonFullVCs         )
        ,.send_ports_17_putFlit_flit_in          ( w_send_ports_17_putFlit_flit_in          )
        ,.EN_send_ports_17_putFlit               ( w_EN_send_ports_17_putFlit               )
        ,.EN_send_ports_17_getNonFullVCs         ( w_EN_send_ports_17_getNonFullVCs         )
        ,.send_ports_17_getNonFullVCs            ( w_send_ports_17_getNonFullVCs            )
        ,.recv_ports_info_17_getRecvPortID       ( w_recv_ports_info_17_getRecvPortID       )
        
        // 18
        
        ,.EN_recv_ports_18_getFlit               ( w_EN_recv_ports_18_getFlit               )
        ,.recv_ports_18_getFlit                  ( w_recv_ports_18_getFlit                  )
        ,.recv_ports_18_putNonFullVCs_nonFullVCs ( w_recv_ports_18_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_18_putNonFullVCs         ( w_EN_recv_ports_18_putNonFullVCs         )
        ,.send_ports_18_putFlit_flit_in          ( w_send_ports_18_putFlit_flit_in          )
        ,.EN_send_ports_18_putFlit               ( w_EN_send_ports_18_putFlit               )
        ,.EN_send_ports_18_getNonFullVCs         ( w_EN_send_ports_18_getNonFullVCs         )
        ,.send_ports_18_getNonFullVCs            ( w_send_ports_18_getNonFullVCs            )
        ,.recv_ports_info_18_getRecvPortID       ( w_recv_ports_info_18_getRecvPortID       )
        
        // 19
        
        ,.EN_recv_ports_19_getFlit               ( w_EN_recv_ports_19_getFlit               )
        ,.recv_ports_19_getFlit                  ( w_recv_ports_19_getFlit                  )
        ,.recv_ports_19_putNonFullVCs_nonFullVCs ( w_recv_ports_19_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_19_putNonFullVCs         ( w_EN_recv_ports_19_putNonFullVCs         )
        ,.send_ports_19_putFlit_flit_in          ( w_send_ports_19_putFlit_flit_in          )
        ,.EN_send_ports_19_putFlit               ( w_EN_send_ports_19_putFlit               )
        ,.EN_send_ports_19_getNonFullVCs         ( w_EN_send_ports_19_getNonFullVCs         )
        ,.send_ports_19_getNonFullVCs            ( w_send_ports_19_getNonFullVCs            )
        ,.recv_ports_info_19_getRecvPortID       ( w_recv_ports_info_19_getRecvPortID       )
        
        // 20
        
        ,.EN_recv_ports_20_getFlit               ( w_EN_recv_ports_20_getFlit               )
        ,.recv_ports_20_getFlit                  ( w_recv_ports_20_getFlit                  )
        ,.recv_ports_20_putNonFullVCs_nonFullVCs ( w_recv_ports_20_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_20_putNonFullVCs         ( w_EN_recv_ports_20_putNonFullVCs         )
        ,.send_ports_20_putFlit_flit_in          ( w_send_ports_20_putFlit_flit_in          )
        ,.EN_send_ports_20_putFlit               ( w_EN_send_ports_20_putFlit               )
        ,.EN_send_ports_20_getNonFullVCs         ( w_EN_send_ports_20_getNonFullVCs         )
        ,.send_ports_20_getNonFullVCs            ( w_send_ports_20_getNonFullVCs            )
        ,.recv_ports_info_20_getRecvPortID       ( w_recv_ports_info_20_getRecvPortID       )
        
        // 21
        
        ,.EN_recv_ports_21_getFlit               ( w_EN_recv_ports_21_getFlit               )
        ,.recv_ports_21_getFlit                  ( w_recv_ports_21_getFlit                  )
        ,.recv_ports_21_putNonFullVCs_nonFullVCs ( w_recv_ports_21_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_21_putNonFullVCs         ( w_EN_recv_ports_21_putNonFullVCs         )
        ,.send_ports_21_putFlit_flit_in          ( w_send_ports_21_putFlit_flit_in          )
        ,.EN_send_ports_21_putFlit               ( w_EN_send_ports_21_putFlit               )
        ,.EN_send_ports_21_getNonFullVCs         ( w_EN_send_ports_21_getNonFullVCs         )
        ,.send_ports_21_getNonFullVCs            ( w_send_ports_21_getNonFullVCs            )
        ,.recv_ports_info_21_getRecvPortID       ( w_recv_ports_info_21_getRecvPortID       )
        
        // 22
        
        ,.EN_recv_ports_22_getFlit               ( w_EN_recv_ports_22_getFlit               )
        ,.recv_ports_22_getFlit                  ( w_recv_ports_22_getFlit                  )
        ,.recv_ports_22_putNonFullVCs_nonFullVCs ( w_recv_ports_22_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_22_putNonFullVCs         ( w_EN_recv_ports_22_putNonFullVCs         )
        ,.send_ports_22_putFlit_flit_in          ( w_send_ports_22_putFlit_flit_in          )
        ,.EN_send_ports_22_putFlit               ( w_EN_send_ports_22_putFlit               )
        ,.EN_send_ports_22_getNonFullVCs         ( w_EN_send_ports_22_getNonFullVCs         )
        ,.send_ports_22_getNonFullVCs            ( w_send_ports_22_getNonFullVCs            )
        ,.recv_ports_info_22_getRecvPortID       ( w_recv_ports_info_22_getRecvPortID       )
        
        // 23
        
        ,.EN_recv_ports_23_getFlit               ( w_EN_recv_ports_23_getFlit               )
        ,.recv_ports_23_getFlit                  ( w_recv_ports_23_getFlit                  )
        ,.recv_ports_23_putNonFullVCs_nonFullVCs ( w_recv_ports_23_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_23_putNonFullVCs         ( w_EN_recv_ports_23_putNonFullVCs         )
        ,.send_ports_23_putFlit_flit_in          ( w_send_ports_23_putFlit_flit_in          )
        ,.EN_send_ports_23_putFlit               ( w_EN_send_ports_23_putFlit               )
        ,.EN_send_ports_23_getNonFullVCs         ( w_EN_send_ports_23_getNonFullVCs         )
        ,.send_ports_23_getNonFullVCs            ( w_send_ports_23_getNonFullVCs            )
        ,.recv_ports_info_23_getRecvPortID       ( w_recv_ports_info_23_getRecvPortID       )
        
        // 24
        
        ,.EN_recv_ports_24_getFlit               ( w_EN_recv_ports_24_getFlit               )
        ,.recv_ports_24_getFlit                  ( w_recv_ports_24_getFlit                  )
        ,.recv_ports_24_putNonFullVCs_nonFullVCs ( w_recv_ports_24_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_24_putNonFullVCs         ( w_EN_recv_ports_24_putNonFullVCs         )
        ,.send_ports_24_putFlit_flit_in          ( w_send_ports_24_putFlit_flit_in          )
        ,.EN_send_ports_24_putFlit               ( w_EN_send_ports_24_putFlit               )
        ,.EN_send_ports_24_getNonFullVCs         ( w_EN_send_ports_24_getNonFullVCs         )
        ,.send_ports_24_getNonFullVCs            ( w_send_ports_24_getNonFullVCs            )
        ,.recv_ports_info_24_getRecvPortID       ( w_recv_ports_info_24_getRecvPortID       )
        
        // 25
        
        ,.EN_recv_ports_25_getFlit               ( w_EN_recv_ports_25_getFlit               )
        ,.recv_ports_25_getFlit                  ( w_recv_ports_25_getFlit                  )
        ,.recv_ports_25_putNonFullVCs_nonFullVCs ( w_recv_ports_25_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_25_putNonFullVCs         ( w_EN_recv_ports_25_putNonFullVCs         )
        ,.send_ports_25_putFlit_flit_in          ( w_send_ports_25_putFlit_flit_in          )
        ,.EN_send_ports_25_putFlit               ( w_EN_send_ports_25_putFlit               )
        ,.EN_send_ports_25_getNonFullVCs         ( w_EN_send_ports_25_getNonFullVCs         )
        ,.send_ports_25_getNonFullVCs            ( w_send_ports_25_getNonFullVCs            )
        ,.recv_ports_info_25_getRecvPortID       ( w_recv_ports_info_25_getRecvPortID       )
        
        // 26
        
        ,.EN_recv_ports_26_getFlit               ( w_EN_recv_ports_26_getFlit               )
        ,.recv_ports_26_getFlit                  ( w_recv_ports_26_getFlit                  )
        ,.recv_ports_26_putNonFullVCs_nonFullVCs ( w_recv_ports_26_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_26_putNonFullVCs         ( w_EN_recv_ports_26_putNonFullVCs         )
        ,.send_ports_26_putFlit_flit_in          ( w_send_ports_26_putFlit_flit_in          )
        ,.EN_send_ports_26_putFlit               ( w_EN_send_ports_26_putFlit               )
        ,.EN_send_ports_26_getNonFullVCs         ( w_EN_send_ports_26_getNonFullVCs         )
        ,.send_ports_26_getNonFullVCs            ( w_send_ports_26_getNonFullVCs            )
        ,.recv_ports_info_26_getRecvPortID       ( w_recv_ports_info_26_getRecvPortID       )
        
        // 27
        
        ,.EN_recv_ports_27_getFlit               ( w_EN_recv_ports_27_getFlit               )
        ,.recv_ports_27_getFlit                  ( w_recv_ports_27_getFlit                  )
        ,.recv_ports_27_putNonFullVCs_nonFullVCs ( w_recv_ports_27_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_27_putNonFullVCs         ( w_EN_recv_ports_27_putNonFullVCs         )
        ,.send_ports_27_putFlit_flit_in          ( w_send_ports_27_putFlit_flit_in          )
        ,.EN_send_ports_27_putFlit               ( w_EN_send_ports_27_putFlit               )
        ,.EN_send_ports_27_getNonFullVCs         ( w_EN_send_ports_27_getNonFullVCs         )
        ,.send_ports_27_getNonFullVCs            ( w_send_ports_27_getNonFullVCs            )
        ,.recv_ports_info_27_getRecvPortID       ( w_recv_ports_info_27_getRecvPortID       )
        
        // 28
        
        ,.EN_recv_ports_28_getFlit               ( w_EN_recv_ports_28_getFlit               )
        ,.recv_ports_28_getFlit                  ( w_recv_ports_28_getFlit                  )
        ,.recv_ports_28_putNonFullVCs_nonFullVCs ( w_recv_ports_28_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_28_putNonFullVCs         ( w_EN_recv_ports_28_putNonFullVCs         )
        ,.send_ports_28_putFlit_flit_in          ( w_send_ports_28_putFlit_flit_in          )
        ,.EN_send_ports_28_putFlit               ( w_EN_send_ports_28_putFlit               )
        ,.EN_send_ports_28_getNonFullVCs         ( w_EN_send_ports_28_getNonFullVCs         )
        ,.send_ports_28_getNonFullVCs            ( w_send_ports_28_getNonFullVCs            )
        ,.recv_ports_info_28_getRecvPortID       ( w_recv_ports_info_28_getRecvPortID       )
        
        // 29
        
        ,.EN_recv_ports_29_getFlit               ( w_EN_recv_ports_29_getFlit               )
        ,.recv_ports_29_getFlit                  ( w_recv_ports_29_getFlit                  )
        ,.recv_ports_29_putNonFullVCs_nonFullVCs ( w_recv_ports_29_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_29_putNonFullVCs         ( w_EN_recv_ports_29_putNonFullVCs         )
        ,.send_ports_29_putFlit_flit_in          ( w_send_ports_29_putFlit_flit_in          )
        ,.EN_send_ports_29_putFlit               ( w_EN_send_ports_29_putFlit               )
        ,.EN_send_ports_29_getNonFullVCs         ( w_EN_send_ports_29_getNonFullVCs         )
        ,.send_ports_29_getNonFullVCs            ( w_send_ports_29_getNonFullVCs            )
        ,.recv_ports_info_29_getRecvPortID       ( w_recv_ports_info_29_getRecvPortID       )
        
        // 30
        
        ,.EN_recv_ports_30_getFlit               ( w_EN_recv_ports_30_getFlit               )
        ,.recv_ports_30_getFlit                  ( w_recv_ports_30_getFlit                  )
        ,.recv_ports_30_putNonFullVCs_nonFullVCs ( w_recv_ports_30_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_30_putNonFullVCs         ( w_EN_recv_ports_30_putNonFullVCs         )
        ,.send_ports_30_putFlit_flit_in          ( w_send_ports_30_putFlit_flit_in          )
        ,.EN_send_ports_30_putFlit               ( w_EN_send_ports_30_putFlit               )
        ,.EN_send_ports_30_getNonFullVCs         ( w_EN_send_ports_30_getNonFullVCs         )
        ,.send_ports_30_getNonFullVCs            ( w_send_ports_30_getNonFullVCs            )
        ,.recv_ports_info_30_getRecvPortID       ( w_recv_ports_info_30_getRecvPortID       )
        
        // 31
        
        ,.EN_recv_ports_31_getFlit               ( w_EN_recv_ports_31_getFlit               )
        ,.recv_ports_31_getFlit                  ( w_recv_ports_31_getFlit                  )
        ,.recv_ports_31_putNonFullVCs_nonFullVCs ( w_recv_ports_31_putNonFullVCs_nonFullVCs )
        ,.EN_recv_ports_31_putNonFullVCs         ( w_EN_recv_ports_31_putNonFullVCs         )
        ,.send_ports_31_putFlit_flit_in          ( w_send_ports_31_putFlit_flit_in          )
        ,.EN_send_ports_31_putFlit               ( w_EN_send_ports_31_putFlit               )
        ,.EN_send_ports_31_getNonFullVCs         ( w_EN_send_ports_31_getNonFullVCs         )
        ,.send_ports_31_getNonFullVCs            ( w_send_ports_31_getNonFullVCs            )
        ,.recv_ports_info_31_getRecvPortID       ( w_recv_ports_info_31_getRecvPortID       )
        
    );
    
endmodule
