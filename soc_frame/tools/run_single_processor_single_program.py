
import json

import logging
import logging.handlers

from defines import *

from func_files import *

from memory import *
from simulator import *

from system import *
from system_spsoc import *
from system_mpsoc import *

from software import *
from software_program import *
from software_controller import *

# ------------------------------------------------------------------------------
# single processor
# ------------------------------------------------------------------------------

# This is used to run a single program on a CPU

sim = Simulator()
sys = System( "test_single_vivado" )
#~ sys = System( "single_mem_packer" )

sys.clean()
sys.compl()

#~ prg = Program( "mul", "rv32i" )
prg = Program( "loop_0000000F_nop_0000000F", "rv32im" )

prg.clean()
prg.compl( "0x00010000" )

#~ sim.run( sys, prg, [MEM_PACKER_OUTPUT_DEBUG], SIM_PRINT_OUTPUT )
sim.run( sys, prg, ["+trace"], SIM_PRINT_OUTPUT )
