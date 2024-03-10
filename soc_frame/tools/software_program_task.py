
import os

import logging
import logging.handlers

from defines import *
from constant import *

from software import *
from software_program import *

class Task( Program ):
    
    path_base = PATH_TASKS
    
    # class Software
    
    # name = ""
    # arch = ""
    
    # def __init__( self, name, arch ):
    # def get_path( self ):
    # def get_path_hex( self ):
    # def get_path_dir( self ):
    # def clean( self ):
    # def compl( self, stack_pointer ):
    # def read( self ):
    # def get_define( self, define_file, var ):
    # def set_define( self, define_file, var, val ):
    
    # class Program
    
    # def get_stack_pointer( self, memory_usage ):
    
    def create( self, num_mul, num_nop ):
        
        # copy template to dir with new name
        
        os.system( "cp -r " + self.path_base + "_template/ " + self.get_path_dir() )
        
        # set defines
        
        self.set_define( "defines", "CNT_MUL", str(num_mul) )
        self.set_define( "defines", "CNT_NOP", str(num_nop) )
        
    
