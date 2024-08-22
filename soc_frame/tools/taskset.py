
import os
import shutil

import logging
import logging.handlers

import random

from constant import *

from software_program_task import *

class Taskset:
    
    # --------------------------------------------------------------------------
    # __init__
    # --------------------------------------------------------------------------
    
    def __init__( self ):
        
        pass
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def create( self, cnt_tasks, loop_cnt_min, loop_cnt_max, percent_mul_min, percent_mul_max ):
        
        prgs_lst = []
        
        for i in range( cnt_tasks ):
            
            loop_cnt = random.randint( loop_cnt_min, loop_cnt_max )
            percent_mul = random.randint( percent_mul_min, percent_mul_max )
            
            cnt_mul = int( ( percent_mul * loop_cnt ) / 100 )
            cnt_nop = loop_cnt - cnt_mul
            
            #~ print( "loop_cnt: " + str( loop_cnt ) )
            #~ print( "percent_mul: " + str( percent_mul ) )
            
            #~ print( "%: " + str( percent_mul ) )
            
            #~ print( "cnt_mul: " + str( cnt_mul ) )
            #~ print( "cnt_nop: " + str( cnt_nop ) )
            
            #~ print( "sum: " + str( cnt_mul + cnt_nop ) )
            
            task_name = "mul_" + str( cnt_mul ) + "_nop_" + str( cnt_nop )
            
            # check if there is already a task like that and increase the number
            # of nop iterations until a new one has been found.
            
            while task_name in prgs_lst:
                
                cnt_nop += 1
                task_name = "mul_" + str( cnt_mul ) + "_nop_" + str( cnt_nop )
            
            task = Task( task_name, "" ) # the arch does not matter at the moment
            task.create( cnt_mul, cnt_nop )
            
            prgs_lst.append( task_name )
        
        return prgs_lst
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    # remove every dir that does not start with "_". dirs starting with "_"
    # are e.g. the templates.
    
    def clear( self ):
        
        dirs = os.listdir( Task.path_base )
        
        for content in dirs:
            
            if os.path.isdir( os.path.join( Task.path_base, content ) ):
                
                if not content.startswith( "_" ):
                    
                    shutil.rmtree( os.path.join( Task.path_base, content ) )
                    
                    
                
            
        
    
