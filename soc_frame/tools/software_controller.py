
import os

import logging
import logging.handlers

from defines import *
from constant import *

from func_files import *
from func_addr import *

from software import *

class Controller( Software ):
    
    path_base = PATH_CONTROLLERS
    
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
    
    def create_controller_define( self, save_mode_at, start_charging_at, stop_charging_at ):
        
        define_lst = []
        
        define_lst.append( '/* This file has been automatically generated */' )
        
        define_lst.append( '' )
        define_lst.append( '#define SAVE_MODE_AT ( ' + str(save_mode_at) + ' )' )
        define_lst.append( '' )
        
        if ( (start_charging_at == -1) or (stop_charging_at == -1) ):
            
            pass
            
        else:
            
            define_lst.append( '#define EN_CHARGING' )
            
        
        define_lst.append( '#define START_CHARGING_AT ( ' + str(start_charging_at) + ' )' )
        define_lst.append( '#define STOP_CHARGING_AT  ( ' + str(stop_charging_at)  + ' )' )
        define_lst.append( '' )
        
        define_f = open( self.get_path_dir() + "controller.h", "w" )
        
        for line in define_lst:
            
            define_f.write( line + "\n" )
            
        define_f.close()
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    # mem has to be a memory file
    
    # this file is meant for the controller. therefore the software controlling
    # the execution is not included here.
    # the offset is used to make place for the controller software.
    
    # here we are concerned with the starting address of the programs i.e.
    # the index of their first instruction.
    
    # the intervals_dict was used to hold execution times of the prgs, but
    # was removed as simulating them took to much time. timing estimations
    # are better done by the controller software during some init phase.
    
    # TODO:
    # we could get the arch_lst from the memory object
    
    def create_prg_define( self, arch_lst, mem, offset = 0, intervals_dict = None, exec_interval_modifier = 1 ):
        
        define_lst = []
        
        index = offset
        index += 1
        
        # no idea why this is needed here
        # no idea what the above comment refers to
        
        prgs_lst = mem.get_prgs_lst()
        
        define_lst.append( '/* This file has been automatically generated */' )
        
        define_lst.append( '' )
        define_lst.append( '#define NUM_PRGS ( ' + str(len(prgs_lst)) + ' )' )
        define_lst.append( '' )
        
        define_lst.append( 'void init_prgs( prg_t *prgs )' )
        define_lst.append( '{' )
        
        for i, prg in enumerate( prgs_lst ):
            
            define_lst.append( '\tprgs[' + str(i) + '].name = "' + prg + '";' )
            
            for arch in arch_lst:
                
                prg_hex = mem.prgs[ prg ][ arch ][ "hex" ]
                
                # to following statement creates a line like:
                # prgs[ 0 ].addr[ RV32I ] = PROG_NORX_RV32I;
                
                define_lst.append( '\tprgs[' + str(i) + '].addr[ARCH_' + arch.upper() + '] = ' + str( index_to_addr( index ) ) + '; // index: ' + str(index) + ' size: ' + str( len(prg_hex) ) )
                
                index += addr_to_index( mem.prgs[ prg ][ arch ][ "sp" ] )
                
            
            for arch in arch_lst:
                
                define_lst.append( '\tprgs[' + str(i) + '].exec_t[ARCH_' + arch.upper() + '] = 0;' )
                
            
            for arch in arch_lst:
                
                define_lst.append( '\tprgs[' + str(i) + '].exec_inv[ARCH_' + arch.upper() + '] = 0;' )
                
            
            for arch in arch_lst:
                
                define_lst.append( '\tprgs[' + str(i) + '].exec_e[ARCH_' + arch.upper() + '] = 0;' )
                
            
            #~ if intervals_dict is None:
                
                #~ define_lst.append( '\tprgs[' + str(i) + '].exec_interval = 0;' )
                #~ define_lst.append( '\tprgs[' + str(i) + '].exec_again_at = 0;' )
                
            #~ else:
                
                #~ define_lst.append( '\tprgs[' + str(i) + '].exec_interval = ' + str( int(intervals_dict[ prg ] * exec_interval_modifier) ) + ';' )
                #~ define_lst.append( '\tprgs[' + str(i) + '].exec_again_at = ' + str( int(intervals_dict[ prg ] * exec_interval_modifier) ) + ';' )
                
            
            define_lst.append( '\tprgs[' + str(i) + '].skip_after    = ' + str( 5 ) + ';' )
            define_lst.append( '\tprgs[' + str(i) + '].skip_cnt_down = ' + str( 5 ) + ';' )
            define_lst.append( '\tprgs[' + str(i) + '].overflows = ' + str( 0 ) + ';' )
            
            define_lst.append( '' )
            
        
        define_lst.append( '}' )
        
        # TODO: use the func made for this.
        
        define_f = open( self.get_path_dir() + "prgs.h", "w" )
        
        for i,line in enumerate( define_lst ):
            
            define_f.write( line + "\n" )
            
        
        define_f.close()
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def create_node_define( self, node_arch_lst ):
        
        define_lst = []
        
        # the node masks are created later and are going to result in something
        # like this:
        
        # define_lst.append( '#define NODES_MASK        ( 0b00000000000000000000000001111111 )' )
        # define_lst.append( '#define NODES_MASK_RV32I  ( 0b00000000000000000000000001111000 )' )
        # define_lst.append( '#define NODES_MASK_RV32IM ( 0b00000000000000000000000000000111 )' )
        
        mask_lst = []
        mask_lst_i = []
        mask_lst_im = []
        
        define_lst.append( '/* This file has been automatically generated */' )
        
        define_lst.append( '' )
        define_lst.append( '#define NUM_NODES ( ' + str(len(node_arch_lst)) + ' )' )
        define_lst.append( '' )
        
        define_lst.append( 'void init_nodes( node_t *nodes )' )
        define_lst.append( '{' )
        
        for i, node_arch in enumerate(node_arch_lst):
            
            mask_lst.append( '1' )
            
            if ( node_arch == 'i' ):
                
                mask_lst_i.append( '1' )
                mask_lst_im.append( '0' )
                
            elif ( node_arch == 'im' ):
                
                mask_lst_i.append( '0' )
                mask_lst_im.append( '1' )
                
            
            define_lst.append( '\tnodes[' + str(i) + '].id          = ' + str(i) + ';' )
            define_lst.append( '\tnodes[' + str(i) + '].arch        = ' + 'ARCH_RV32' + node_arch.upper() + ';' )
            define_lst.append( '\tnodes[' + str(i) + '].id_flag     = ' + 'NODE_' + str(i) + '_ID;' )
            define_lst.append( '\tnodes[' + str(i) + '].addr_assign = ' + 'NODE_' + str(i) + '_ADDR_ASSIGN;' )
            define_lst.append( '\tnodes[' + str(i) + '].prg         = 0;' )
            #~ define_lst.append( '\tnodes[' + str(i) + '].charge      = MAX_HALF;' )
            define_lst.append( '\tnodes[' + str(i) + '].charge      = 500000;' )
            
            define_lst.append( '\t' )
            
        define_lst.append( '}' )
        
        # fill up mask_lsts
        
        for i in range( len(node_arch_lst), 31 ):
            
            mask_lst.append( '0' )
            mask_lst_i.append( '0' )
            mask_lst_im.append( '0' )
            
        
        # reverse the lists so they start with the filled zeros
        
        mask_lst.reverse()
        mask_lst_i.reverse()
        mask_lst_im.reverse()
        
        define_lst.append( '' )
        
        define_lst.append( '#define NODES_MASK        ( 0b' + ''.join( mask_lst ) + ' )' )
        define_lst.append( '#define NODES_MASK_RV32I  ( 0b' + ''.join( mask_lst_i ) + ' )' )
        define_lst.append( '#define NODES_MASK_RV32IM ( 0b' + ''.join( mask_lst_im ) + ' )' )
        
        define_f = open( self.get_path_dir() + "nodes.h", "w" )
        
        for line in define_lst:
            
            define_f.write( line + "\n" )
            
        define_f.close()
        
    
    # --------------------------------------------------------------------------
    # 
    # --------------------------------------------------------------------------
    
    def create_charging_define( self, charges_lst ):
        
        define_lst = []
        
        define_lst.append( '/* This file has been automatically generated */' )
        
        define_lst.append( '' )
        define_lst.append( '#define NUM_CHARGES ( ' + str(len(charges_lst)) + ' )' )
        define_lst.append( '' )
        
        define_lst.append( 'void init_charges( int *charges )' )
        define_lst.append( '{' )
        
        for i, charge in enumerate(charges_lst):
            
            define_lst.append( '\tcharges[' + str(i) + '] = ' + str(charge) + ';' )
            
        
        define_lst.append( '}' )
        
        define_f = open( self.get_path_dir() + "energy_harvester.h", "w" )
        
        for line in define_lst:
            
            define_f.write( line + "\n" )
            
        define_f.close()
        
    
