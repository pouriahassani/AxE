
from defines import *

from Node import *

class Configuration:
    
    def __init__( self, i, name = None, node_archs = [] ):
        
        self.i = i
        self.name = name
        self.nodes = []
        
        self.part_failed = 0
        self.part_no_choice = 0
        self.succ_partitions = 0
        
        if len(node_archs) > 0:
            for node_arch in node_archs:
                self.create_add_node( node_arch )
    
    def reset( self ):
        
        self.part_failed = 0
        self.part_no_choice = 0
        self.succ_partitions = 0
        
    
    def reset_nodes( self ):
        
        for node in self.nodes:
            node.reset()
        
    
    def create_add_node( self, arch ):
        
        ni_next = len( self.nodes )
        
        self.nodes.append( Node( ni_next, (str(ni_next) + arch.name), arch ) )
        
    
    def partition_succ( self ):
        
        self.succ_partitions += 1
        
    
    def p( self ):
        
        s = ""
        for node in self.nodes:
            s += node.p() + "\n"
        
        return ( "configuration" + str(self.i) + "\n" + s )
    
    def p_charges( self ):
        
        for node in self.nodes:
            
            start = len( node.charges )-1
            end = len( node.charges )
            # print(start, " end ",end)
            for charge in node.charges[ start : end ]:
                
                print( charge )
                
            
        
    
    def report( self ):
        
        s = ""
        for node in self.nodes:
            s += node.report() + "\n"
        
        return ( self.result() + "\n" + s )
        
    
    def result( self ):
        
        return ( "configuration" + str(self.i) + ": " + str(self.succ_partitions) )
        
