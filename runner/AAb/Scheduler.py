
from defines import *

class Scheduler:
    
    def __init__( self ):
        
        pass
        
    
    def each_loop( self, node, time ):
        
        # print prgs
        
        # ~ for pi in nodes[ni]["prgs"]: print( repr( prgs[pi] ) )
        
        # set_node_idle
        
        # ~ print( str( node.p() ) )
        
        if node.busy_until != None:
            if node.busy_until < time:
                
                # ~ print( str(time) + " n" + str(ni) + ": became idle" )
                node.busy_until = None
                
                # check if the deadline of the prg has been missed
                
                if node.prg_running is not None:
                    
                    prg_ran = node.prg_running
                    
                    node.prg_running = None
                    
                    time_until_d = time - prg_ran.d_next
                    
                    if ( time_until_d < 0 ):
                        
                        # missed deadline
                        pass
                        
                        
                
                # ~ print( "time to deadline: " + str( time_until_d ) )
        
        # set_prgs_ready
        
        for prg in node.prgs:
            
            if prg.ready ==  False:
                
                if prg.d_next < time:
                    
                    # ~ print( str(time) + " p" + str(pi) + ": became ready" )
                    prg.ready = True
        
        if (time%1000) == 0:
            
            node.record_charges( time )
            
            # ~ print( node.p() + ": " + str(node.charge) )
            
    
    def schedule( self, configuration, prgs ):
        
        for node in configuration.nodes:
            
            node.set_e_max()
            
        
        time = 0
        run_prgs = []
        while 1 == 1:
            
            for node in configuration.nodes:
                
                if ( len(node.prgs) == 0 ):
                    continue
                
                self.each_loop( node, time )
                
                prg = self.prg_to_run( node )
                
                if prg == None or prg == -1:
                    continue
                
                # there is a prg to run, but we do not know if we should yet
                
                # -----------------------------------------------------------------
                # 
                # ED-H rule 3
                # 
                # -----------------------------------------------------------------
                
                # idle if there are jobs, but no energy or no slack energy
                # -> empty battery
                
                # ~ print( node.p() )
                
                if node.charge < node.e_max:
                    
                    # ~ print( "n" + str(ni) + " wants to run p" + str(pi) + " but there is not enough charge left" )
                    # ~ print( "charge left: " + str(nodes[ni]["charge"]) + " but max is: " + str(nodes[ni]["e_max"]) )
                    
                    # ~ print( "c = 0: " + node.p() )
                    # print(run_prgs)
                    return time
                    
                
                # slack energy
                
                se = node.get_SE()
                
                # ~ print( "------------------" )
                # ~ print( "finished running SE: " + str(se) )
                
                if ( se < node.e_max ):
                    
                    # ~ print( "SE is empty" )
                    
                    # ~ print( "SE = 0: " + node.p() )
                    
                    return time
                
                
                node.run_prg( prg, time )
                run_prgs.append(prg.name)
            time += 1
            # print("time ",time )
        
    
    
    def prg_to_run( self, node ):
        
        # node still running
        
        if node.busy_until != None:
            
            return None
            
        else:
            
            # ~ # print( "get prg via EDF for n" + str(ni) )
            
            earliest_deadline = MAX;
            earliest_deadline_new = MAX;
            
            # iterating all the prgs assigned to the node
            # -----------------------------------------------------------------
            
            prg_earliest_deadline = -1
            
            for prg in node.prgs:
                
                if prg.ready == True:
                    
                    earliest_deadline_new = prg.d_next
                    
                    # ~ print( "p" + str(pi) + " d: " + str(earliest_deadline_new) )
                    
                    if ( earliest_deadline_new < earliest_deadline ):
                        
                        earliest_deadline = earliest_deadline_new
                        prg_earliest_deadline = prg
                        
                    
                
            
            # ~ if ( prg_earliest_deadline != -1 ):
                
                # ~ print( "" )
                # ~ print( "earliest deadline has " + "p" + str(prg_earliest_deadline) )
                # ~ print( "" )
                
            
            return prg_earliest_deadline
        
