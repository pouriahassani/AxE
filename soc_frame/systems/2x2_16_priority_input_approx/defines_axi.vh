
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// used in the system to differentiate between requests. not part of the
// official AXI light interface.

`define AXI_WRITE ( 1'b0 )
`define AXI_READ  ( 1'b1 )

//---------------------
// AXI
//---------------------

`define AXI_DATA_WIDTH  ( 32 )
`define AXI_ADDR_WIDTH  ( 32 )

`define AXI_WSTRB_WIDTH (  4 )

// the following are mainly needed to calculate signal widths.

`define AXI_AWPROT_WIDTH ( 3 )
`define AXI_BRESP_WIDTH  ( 2 )
`define AXI_ARPROT_WIDTH ( 3 )
`define AXI_RRESP_WIDTH  ( 2 )

// axi responses

`define RESP_OKAY   ( 2'b00 )
`define RESP_EXOKAY ( 2'b01 )
`define RESP_SLVERR ( 2'b10 )
`define RESP_DECERR ( 2'b11 )

// OKAY - everything is working fine.
// EXOKAY - exclusive access. not available in axi light.
// SLVERR - something went wrong.
// DECERR - by interconnect if no slave available at addr.
