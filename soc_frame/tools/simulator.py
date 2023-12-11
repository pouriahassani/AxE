
import os
import subprocess

import logging
import logging.handlers

from system import *
from memory import *

from software_program import *
from software_controller import *

# os.environ['OMP_NUM_THREADS'] = '4'

class Simulator:
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def __init__( self ):
        
        pass
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def run( self, sys, what, args=None, prnt=False ):
        
        logging.debug( "run" )
        
        # check args
        
        assert( isinstance(sys, System) )
        
        if args is None: args = []
        
        call = [ "../systems/"+sys.name+"/obj_dir/Vtop" ]
        call.extend( args )
        
        #~ print( str( call ) )
        
        # create the necessary hex file and copy it to a place where the
        # memory can find it.
        
        if   isinstance( what, Program ):
            
            self.set_hex( what.get_path_hex() )
            
        elif isinstance( what, Memory ):
            
            # TODO pack mem file
            pass
            
            
        elif isinstance( what, str ): # str would be a path to a hex file
            
            self.set_hex( what )
            
        
        # if the output should be printed or returned
        
        if prnt:
            os.environ['OMP_NUM_THREADS'] = '4'
            os.system( " ".join(call) )
            # ../systems/2x2_16_priority_input_approx/obj_dir/Vtop
            
        else:
            proc = subprocess.run( call, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
            
            stdout = proc.stdout.decode("utf-8")
            stderr = proc.stderr.decode("utf-8")
            print(proc.returncode, proc.stderr)
            stdout_l = stdout.split("\n")
            del stdout_l[-1]
            
            return stdout_l
            
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def run_prog( self, sys, prg     , args=None ): return self.run( sys, prg     , args )
    def run_mem(  self, sys, mem     , args=None ): return self.run( sys, mem     , args )
    def run_hex(  self, sys, hex_path, args=None ): return self.run( sys, hex_path, args )
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def set_hex( self, src ):
        
        logging.debug( "set_hex" )
        
        dst = "../mem.hex"
        
        logging.debug( "src: " + src )
        logging.debug( "dst: " + dst )
        
        if os.path.isfile( dst ):
            os.system( "rm " + dst )
        
        os.system( "cp " + src + " " + dst )
        
    
