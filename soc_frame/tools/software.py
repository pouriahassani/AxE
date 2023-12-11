
# das hat make mal ausgespuckt
#~ make: warning:  Clock skew detected.  Your build may be incomplete.

import os

import logging
import logging.handlers

from constant import *

class Software:
    
    # path base is set in the child classes
    
    path_base = ""
    
    name = ""
    arch = ""
    
    # --------------------------------------------------------------------------
    # __init__
    # --------------------------------------------------------------------------
    
    def __init__( self, name, arch ):
        
        self.name = name
        self.arch = arch
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def get_path( self ):
        
        return self.get_path_hex()
        
    
    def get_path_hex( self ):
        
        return ( self.path_base + self.name + "/" + self.arch + "_main.hex" )
        
    
    def get_path_dir( self ):
        
        return ( self.path_base + self.name + "/" )
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def clean( self ):
        
        os.system( "make -C " + self.path_base + self.name + "/ " + " clean" )
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def compl( self, stack_pointer ):
        
        # if (self.name != 'SobelFilter-master'):
        os.system( "make -C " + self.path_base + self.name + "/ " + " " + self.arch + " STACK_POINTER=" + stack_pointer + " > /dev/null" )
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    # return list
    
    def read( self ):
        
        prog_f = open( self.path_base + self.name + "/" + self.arch + "_main.hex", "r" )
        prog_l = prog_f.readlines()
        prog_f.close()
        
        # remove newlines
        
        for i,l in enumerate( prog_l ):
            prog_l[i] = l[:-1]
        
        return prog_l
        
    
    # --------------------------------------------------------------------------
    # G E T _ D E F I N E
    # --------------------------------------------------------------------------
    
    def get_define( self, define_file, var ):
        
        return get_constant( self.get_path_dir() + define_file + ".h", var )
    
    # --------------------------------------------------------------------------
    # S E T _ D E F I N E
    # --------------------------------------------------------------------------
    
    def set_define( self, define_file, var, val ):
        
        set_constant( self.get_path_dir() + define_file + ".h", var, val )
    
