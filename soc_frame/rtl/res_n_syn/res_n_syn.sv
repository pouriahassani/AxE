
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module res_n_syn
#()
(
     input clk
    ,input res_n
    
    ,output res_n_syn
);

reg shift_reg[ 8 ];

assign res_n_syn =  shift_reg[ 7 ] &&
                    shift_reg[ 6 ] &&
                    shift_reg[ 5 ] &&
                    shift_reg[ 4 ] &&
                    shift_reg[ 3 ] &&
                    shift_reg[ 2 ] &&
                    shift_reg[ 1 ] &&
                    shift_reg[ 0 ];

always @ ( posedge clk )
begin : res_n_syn_proc
    
    shift_reg[ 7 ] <= shift_reg[ 6 ];
    shift_reg[ 6 ] <= shift_reg[ 5 ];
    shift_reg[ 5 ] <= shift_reg[ 4 ];
    shift_reg[ 4 ] <= shift_reg[ 3 ];
    shift_reg[ 3 ] <= shift_reg[ 2 ];
    shift_reg[ 2 ] <= shift_reg[ 1 ];
    shift_reg[ 1 ] <= shift_reg[ 0 ];
    shift_reg[ 0 ] <= res_n;
    
end

endmodule
