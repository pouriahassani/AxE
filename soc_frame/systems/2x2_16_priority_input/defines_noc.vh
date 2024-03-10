
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// bit that is used to record if the request / response is either a read or
// a write. only used to calculate widths.

`define RW_INDICATOR ( 1 )

// TODO - NOC_NODE_WIDTH should be calculated.

`define NOC_DATA_WIDTH  ( 16 )
`define NOC_NODE_WIDTH  (  2 )

`define NUM_NODES  ( 4 )

// the controller and the memory controller are not processing nodes.

`define NUM_NODES_PROCESSING  ( `NUM_NODES - 2 )

// TODO - calculate
`define NUM_NODES_PROCESSING_WIDTH ( 1 )


// the max width of any AXI request or response.
// this is set to the write request as this requires the most data to be sent.
// the least data is sent during a write response, but to keep the system
// uniform the response is padded with zeros.

// TODO - change name as "request" is not 100% correct.

`define MERGED_REQUEST_WIDTH (                       \
                                   `AXI_AWPROT_WIDTH \
                                 + `AXI_WSTRB_WIDTH  \
                                 + `AXI_ADDR_WIDTH   \
                                 + `AXI_DATA_WIDTH   \
                                 + `RW_INDICATOR     \
                             )

// TODO - explain where the +3 comes from.

`define FLIT_HEADER_WIDTH  ( `NOC_NODE_WIDTH + 3 )
`define FLIT_BODY_WIDTH    ( `NOC_DATA_WIDTH     )

`define FLIT_WIDTH  ( `FLIT_HEADER_WIDTH + `FLIT_BODY_WIDTH )

// the NoC header does not contain the sender. however, the memory
// controller needs to know where an AXI request came from.
// therefore the sender is placed into the body part of a flit.
// the `define USEFUL_DATA_WIDTH is the width of the body that can
// actually be used for transmitting data.

`define USEFUL_DATA_WIDTH  ( `FLIT_BODY_WIDTH - `NOC_NODE_WIDTH )

// we assume, that the data cannot be placed into the flits without an
// additional flit with padding.
// even if this is possible an empty flit will still be sent to keep the
// code simple

`define FULL_FLITS_TO_SEND  ( `MERGED_REQUEST_WIDTH / `USEFUL_DATA_WIDTH )
`define FLITS_TO_SEND       ( `FULL_FLITS_TO_SEND + 1 )

`define MISSING  ( `MERGED_REQUEST_WIDTH - ( `FULL_FLITS_TO_SEND * `USEFUL_DATA_WIDTH ) )
`define PADDING  ( `USEFUL_DATA_WIDTH - `MISSING )
