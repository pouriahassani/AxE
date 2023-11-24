
import json

from func_files import *
from func_addr import *

from software_program import *

class Memory:
    
    # the memory object has a dict, that holds all the programs/tasks.
    # 
    # {
    #     "task1" :                         <- the name of the program/task
    #     {
    #         "arch_32_i" :                 <- the architecture
    #         {
    #             "sp"  : 12                <- the stack pointer
    #             "hex" : [...]             <- array of all instructions
    #         }
    #     }
    # }
    
    prgs = {}
    
    # --------------------------------------------------------------------------
    # __init__
    # --------------------------------------------------------------------------
    
    def __init__( self, memory_file_path = None ):
        
        if ( memory_file_path != None ):
            self.load( memory_file_path )
        
    
    # --------------------------------------------------------------------------
    # load
    # --------------------------------------------------------------------------
    
    def load( self, memory_file_path ):
        
        self.prgs = read_dict_from_json( memory_file_path )
        
    
    # --------------------------------------------------------------------------
    # save
    # --------------------------------------------------------------------------
    
    def save( self, memory_file_path ):
        
        write_dict_to_json( self.prgs, memory_file_path )
        
    
    # --------------------------------------------------------------------------
    # include
    # --------------------------------------------------------------------------
    
    # including (adding) a prog to the memory
    
    def include( self, prg, sp ):
        
        self.prgs[ prg.name ] = {}
        self.prgs[ prg.name ][ prg.arch ] = {}
        
        self.prgs[ prg.name ][ prg.arch ][ "sp" ] = sp
        self.prgs[ prg.name ][ prg.arch ][ "hex" ] = prg.read()
    
    # --------------------------------------------------------------------------
    # info
    # --------------------------------------------------------------------------
    
    # MIGHT NOT WORK
    
    # print some debug info
    
    def info( self ):
        
        print( "-------------------------------------------------------- info" )
        print( "" )
        
        prgs_lst = self.get_prgs_lst()
        
        for prg in prgs_lst:
            
            print( "--- " + prg + " ---" )
            print( "arch \t\t size \t\t sp" )
            
            for arch in self.prgs[prg]:
                
                size = len(self.prgs[prg][arch]["hex"])
                sp = self.prgs[prg][arch]["sp"]
                
                print( arch + "\t\t" + str(size) + "\t\t" + sp )
                
            
            print( "" )
        
        print( "---------------------------------------------------- info end" )
        
    
    # --------------------------------------------------------------------------
    # get_prgs_lst
    # --------------------------------------------------------------------------
    
    # this is a list of programs stored in this object
    
    def get_prgs_lst( self ):
        
        prg_list = []
        
        for prg in self.prgs:
            
            prg_list.append( prg )
            
        
        prg_list.sort()
        
        return prg_list
        
    
    # --------------------------------------------------------------------------
    # pack_prgs
    # --------------------------------------------------------------------------
    
    # here the memory usage of every prg is analyzed and the stack pointer set
    # accordingly, instead of guessing or distributing them equally. this allows
    # the memory file to become smaller which can be important if the system
    # should run on a board.
    
    # after running this method all the prgs stored in the dict have a stack
    # pointer set that is not wasting any memory.
    
    def pack_prgs( self, sim, prgs_lst, arch_dict ):
        
        # we iterate over every prg and for each prg every arch
        
        for prg_name in prgs_lst:
            
            self.prgs[ prg_name ] = {}
            
            for arch, sys in arch_dict.items():
                
                self.prgs[ prg_name ][ arch ] = {}
                
                # here we are using software objects. this means, that the
                # program is read from the filesystem and not the dict of
                # the memory object!
                
                prg = Program( prg_name, arch )
                
                # clean the output and compile with some default stack pointer
                # that should be high enough
                
                prg.clean()
                prg.compl( "0x00010000" )
                
                # a simulation is run with an arg that outputs the memory usage
                
                memory_usage = sim.run( sys, prg, [MEM_PACKER_OUTPUT_MEMORY] )
                
                sp = prg.get_stack_pointer( memory_usage )
                
                # the program has to be compiled again using the new stack
                # pointer. this is the program that is then read and stored in
                # the dict of the memory.
                
                prg.clean()
                prg.compl( sp )
                
                self.prgs[ prg_name ][ arch ][ "sp" ] = sp
                self.prgs[ prg_name ][ arch ][ "hex" ] = prg.read()
            
        
    
    # --------------------------------------------------------------------------
    # pack
    # --------------------------------------------------------------------------
    
    # here the actual memory file is created. the result is a .hex file where
    # all the instructions of all the prgs are included.
    
    def pack( self, arch_lst, dst, first = "" ):
        
        filler = "00000000"
        filler_arr = [ filler ]
        
        mem = []
        
        prgs_lst = self.get_prgs_lst()
        
        # it might be necessary to put a prg at the beginning like the
        # controller software.
        
        if ( first != "" ):
            
            prgs_lst.insert( 0, prgs_lst.pop( prgs_lst.index(first) ) )
            
        
        for prg in prgs_lst:
            
            for arch in arch_lst:
                
                # this is a somewhat dirty fix for prgs that only have one arch.
                # this is true for the controller software.
                
                try:
                    
                    prg_hex = self.prgs[ prg ][ arch ][ "hex" ]
                    
                except KeyError: continue
                
                # 1. add the instructions of the prg
                # 2. find the number of words needed to fill up the gap to
                #    the stack pointer
                # 3. fill the gap with "00000000"
                
                # PITFALL:
                # if you debug the created memory you might get confused by
                # the line numbers of your text editor. if you look at the
                # generated memory file and see an instruciton at line 200, but
                # you know it should be at line 199, then this is not wrong as
                # the text editor starts counting at 1 and not 0.
                
                #~ print( "---" )
                #~ print( "current length of mem: " + str( len(mem) ) )
                #~ print( "adding n lines of prg: " + str( len(prg_hex) ) )
                
                mem.extend( prg_hex )
                
                #~ print( "new length of mem: " + str( len(mem) ) )
                
                missing = ( addr_to_index( self.prgs[ prg ][ arch ][ "sp" ] ) ) - len( prg_hex )
                
                #~ print( "n lines to fill until the stack pointer is reached: " + str( missing ) )
                
                mem.extend( filler_arr * int(missing) )
                
                #~ print( "new length of mem: " + str( len(mem) ) )
                
            
        
        mem_f = open( dst, "w" )
        
        for i,l in enumerate( mem ):
            
            mem_f.write( l + "\n" )
            #~ mem_f.write( str(i) + ": " + l + "\n" )
            
        
        mem_f.close()
        
    
