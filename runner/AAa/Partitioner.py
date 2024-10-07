
from defines import *

class Partitioner:
    
    def __init__(self):
        
        pass
        
    
    def partition_succ( self, configuration ):
        
        for node in configuration.nodes:
            
            if node.diff_p_e != None:
                
                return True
                
            
        
        return False
        
    
    def partition( self, configuration, prgs ):
        
        for prg in prgs:
            
            for node in configuration.nodes:
                
                node.try_partition( prg )
                
            
            succ = self.partition_succ( configuration )
            
            if succ == False:
                return 0
            
            selected = None
            
            for node in configuration.nodes:
                
                if node.diff_p_e != None:
                    
                    if selected == None:
                        selected = node
                    else:
                        if node.diff_p_e < selected.diff_p_e:
                            selected = node
                
            selected.do_partition( prg )
            
            # print history
            
        
        return 1
        
    
    def choice_available( self, nodes, prg, choice ):
        
        for node in nodes:
            if node.is_choice( prg, choice ):
                return True
        
        return False
    
    def assign_to_choice( self, nodes, prg, choice ):
        
        for node in nodes:
            if node.is_choice( prg, choice ):
                
                # ~ print( "assign to choice: " + choice )
                
                node.assign_prg( prg )
                return
        
        print( "assign to choice failed" )
        exit()
    
    def assign_to_emptiest( self, nodes, prg, choice ):
        
        candidate_nodes = []
        
        for node in nodes:
            
            if node.is_choice( prg, choice ):
                
                candidate_nodes.append( node )
                
            
        
        selected = candidate_nodes[0]
        
        for node in candidate_nodes:
            
            if node.acc_up < selected.acc_up:
                
                selected = node
                
            
        
        selected.assign_prg( prg )
        
    
    def partition_apprx_aware( self, configuration, prgs,bookie,per_min,last_prg ):
        
        for prg in prgs:
            # ~ print( "" )
            # ~ print( "partition: " + prg.p() )
            last_prg[0] = prg.name
            candidate_nodes = []
            
            for node in configuration.nodes:
                
                if node.check_fit( prg ) == True:
                    
                    candidate_nodes.append( node )
                    
            # str = prg.name + "\t"
            

            # ~ print( "candidate nodes: " + str( len( candidate_nodes ) ) )
            
            if len( candidate_nodes ) == 0:
                

                # for node in configuration.nodes:
                #     up = node.arch.get_up( prg )
                #     ue = node.arch.get_ue( prg )
                #     bookie.record_entry_2_deep( configuration.i, str(per_min) +"_" + (str(node.name))[1:] + "_E" , node.acc_ue+ue )
                #     bookie.record_entry_2_deep( configuration.i, str(per_min) +"_" + (str(node.name))[1:] + "_U"  , node.acc_up+up )

                
                return 0
            
            #aa1 aa2
            if self.choice_available( candidate_nodes, prg, "first" ):
              self.assign_to_choice( candidate_nodes, prg, "first" )
            elif self.choice_available( candidate_nodes, prg, "second" ):
              self.assign_to_choice( candidate_nodes, prg, "second" )
            elif self.choice_available( candidate_nodes, prg, "third" ):
              self.assign_to_choice( candidate_nodes, prg, "third" )
            elif self.choice_available( candidate_nodes, prg, "no" ):
              return -1
            else:
                pass
            
            #aa3
            # print(f"Program : {prg.name}")
            # if configuration.i == 0:
            #     selected = candidate_nodes[0]
                
            #     for node in candidate_nodes:
                    
            #         if node.acc_up < selected.acc_up:
                        
            #             selected = node
                
            #     selected.assign_prg( prg )
            
            # else:
            
            #     if self.choice_available( candidate_nodes, prg, "first" ):
            #         self.assign_to_choice( candidate_nodes, prg, "first" )

            #         Nodes = []
            #         for node in candidate_nodes:
            #             Nodes.append(node.get_arch() )
            #         # print(" first",prg.name, " Nodes: ",Nodes)
            #         list = [" first",prg.name,Nodes]
            #         records.append(list)

            #     elif self.choice_available( candidate_nodes, prg, "second" ):
            #         self.assign_to_emptiest( candidate_nodes, prg, "second") # assign_to_emptiest!!!
                    
            #         Nodes = []
            #         for node in candidate_nodes:
            #             Nodes.append(node.get_arch() )
            #         # print(" second",prg.name, " Nodes: ",Nodes)
            #         list = [" second",prg.name,Nodes]
            #         records.append(list)

            #     elif self.choice_available( candidate_nodes, prg, "third" ):
            #         self.assign_to_choice( candidate_nodes, prg, "third" )

            #         Nodes = []
            #         for node in candidate_nodes:
            #             Nodes.append(node.get_arch() )
            #         # print(" third",prg.name, " Nodes: ",Nodes)
            #         list = [" third",prg.name,Nodes]
            #         records.append(list)

            #     elif self.choice_available( candidate_nodes, prg, "no" ):
            #         Nodes = []
            #         for node in candidate_nodes:
            #             Nodes.append(node.get_arch() )
            #         # print(" no choice",prg.name, " Nodes: ",Nodes)
            #         list = [" no",prg.name,Nodes]
            #         records.append(list)
            #         return -1
            #     else:
            #         # pass
            # # str += n.name + "\t"
            # # print(str)
            #         selected = candidate_nodes[0]                
            #         for node in candidate_nodes:                
            #             if node.acc_up < selected.acc_up:                        
            #                 selected = node
            #         selected.assign_prg( prg )
        # for node in configuration.nodes:
        #     up = node.arch.get_up( prg )
        #     ue = node.arch.get_ue( prg )
        #     bookie.record_entry_2_deep( configuration.i, str(per_min) +"_" + (str(node.name))[1:] + "_E" , node.acc_ue+ue )
        #     bookie.record_entry_2_deep( configuration.i, str(per_min) +"_" + (str(node.name))[1:] + "_U"  , node.acc_up+up )

        return 1
        
    
    def report( self ):
        
        return ( self.configuration.report() )
        
