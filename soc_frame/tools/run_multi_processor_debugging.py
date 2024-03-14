
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
# test MPSoC controller by running each program alone
# ------------------------------------------------------------------------------

# this run can be used to test each program on the MP system.
# the controller is set up to execute only one program so if one of them causes
# issues it can be identified this way.

# PLEASE NOTE: there is no reporting system. you need to watch the output!

controller_name = "test_single_execution"

# controller estimates

controller_size_addr = 16380;
controller_size = controller_size_addr / 4

controller_size = int(controller_size)

# create memory file

mem = Memory()
sim = Simulator()
sys = System( "single_mem_packer" )

sys.compl()

prgs_lst = get_prgs_lst( PATH_PRGS )
arch_lst = ["rv32i"]

# this runs 

mem.pack_prgs( sim, sys, prgs_lst, arch_lst )

mem.save( "test_single_execution_prgs.json" )

# -> now we have the memory file containing all the progs we want to test one
# by one

del sys

# create define file for controller

index = controller_size-1

con = Controller( controller_name, "rv32i" )

con.create_prg_define( mem, index )

# compile controller with new define

con.clean()

# -> we don't need to delete the mem obj, but i want to

del mem

# -> now we change the prg that should be executed.

sys = System( "mult_noc_interface" )

# the controller software has to be compiled for every prg.
# this means, that the memory has to be packed as well each time.
# we saved the memory containing only the prgs before so we can use the file
# again here and only include the new controller on the fly.

for prg in prgs_lst:
    
    print( "---------------------------------------------------------- " + prg )
    
    # set the name of the next prg to be executed. this is done by changeing
    # a define in the controller software.
    
    prg_define_name = "PROG_" + prg.upper() + "_" + arch_lst[0].upper()
    
    con.clean()
    con.set_define( "execute", "EXECUTE", prg_define_name )
    con.compl( index_to_addr( controller_size ) )
    
    # controller dem memory hinzufuegen
    
    mem = Memory( "test_single_execution_prgs.json" )
    mem.include( con, index_to_addr( controller_size ) )
    mem.pack( "test.hex", controller_name )
    
    # TODO - try without deleting memory obj
    
    del mem
    
    sim.run( sys, "test.hex", SIM_NO_ARGS, SIM_PRINT_OUTPUT )
    
