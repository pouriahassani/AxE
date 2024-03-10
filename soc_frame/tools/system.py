
import os

from defines import *
from func_files import *
from constant import *

class System:
    
    path_base = PATH_SYSS
    
    name = ""
    
    # --------------------------------------------------------------------------
    # _ _ I N I T _ _
    # --------------------------------------------------------------------------
    
    def __init__( self, name ):
        
        self.name = name
        
    
    # --------------------------------------------------------------------------
    # G E T _ P A T H _ D I R
    # --------------------------------------------------------------------------
    
    def get_path_dir( self ):
        
        return self.path_base  + self.name + "/"
    
    # DEPRECATED
    
    def get_dir_path( self ):
        
        return self.get_path_dir()
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def clean( self ):
        
        os.system( "make -C " + self.get_dir_path() + " clean" )
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def compl( self ):
        print(self.get_dir_path())
        os.system( "make -C " + self.get_dir_path() )
        
    
    def set_memory_file( self ):
        
        pass
    
    # --------------------------------------------------------------------------
    # G E T _ D E F I N E
    # --------------------------------------------------------------------------
    
    def get_define( self, define_file, var ):
        
        return get_constant( self.get_dir_path() + define_file + ".vh", var )
    
    # --------------------------------------------------------------------------
    # S E T _ D E F I N E
    # --------------------------------------------------------------------------
    
    def set_define( self, define_file, var, val ):
        
        set_constant( self.get_dir_path() + define_file + ".vh", var, val )
    
