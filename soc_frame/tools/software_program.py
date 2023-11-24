
import os

import logging
import logging.handlers

from defines import *
from constant import *

from func_addr import *

from software import *

class Program( Software ):
    
    path_base = PATH_PRGS
    
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
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    # PITFALL:
    # this functions reads the memory file from the prog's dir.
    # if this prog has been compiled after the memory usage has been optained
    # the result can be invalid!
    
    def get_stack_pointer( self, memory_usage ):
        
        index_l = memory_usage
        mem_l = self.read()
        
        mem_highest_index = len( mem_l )
        
        # remove newline and convert to int
        
        for i,l in enumerate(index_l):
            
            index_l[ i ] = int( index_l[ i ] )
            
        
        # remove duplicates
        
        index_l = list(set(index_l))
        
        index_l.sort()
        
        new_l = []
        
        sp_min = 0
        bss_size = 0
        
        # check for bss or whatever
        
        has_bss = ( (mem_highest_index+1) in index_l ) or \
                  ( index_l[0] < mem_highest_index )
        
        if has_bss:
            
            print( "has_bss" )
            
            mem_highest_index_tmp = mem_highest_index
            mem_highest_index_tmp += 1
            
            # walk to end of the bss
            
            for i,l in enumerate(index_l):
                
                if ( l < mem_highest_index_tmp ):
                    
                    bss_size += 1
                    
                    
                elif ( l == mem_highest_index_tmp ):
                    
                    mem_highest_index_tmp += 1
                    
                    bss_size += 1
                    
                else:
                    
                    new_l.append( l )
                
            
            sp_min = min(new_l)
            
        else:
            
            sp_min = min(index_l)
            
        
        stack_size = max(index_l) - sp_min
        
        #~ logging.debug( "bss_size:   " + str(bss_size) )
        #~ logging.debug( "stack_size: " + str(stack_size) )
        
        stack_pointer = mem_highest_index + bss_size + stack_size + 1
        stack_pointer_byte_aligned = stack_pointer * 4
        stack_pointer_byte_aligned_hex = hex(stack_pointer_byte_aligned)
        
        return stack_pointer_byte_aligned_hex
        
    
