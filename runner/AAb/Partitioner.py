
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
    
    def Correct_Nodes(self,available_nodes,prg):
        Correct_nodes = []
        # Prg doesn't have Integer multiplication
        if prg.Int_pref == 0:
            # prg dosn't have float multiplication
            if prg.Float_pref == 0:
                Correct_nodes = available_nodes
                return Correct_nodes
            
            # Prg requires exact Float multiplication
            if prg.Float_pref == 1:
                for node in available_nodes:
                    if node.arch.Float_Type == 1:
                        Correct_nodes.append(node)
                return Correct_nodes
            
            # Prg has Float multiplication and it can be approximate
            if prg.Float_pref == 2:
                for node in available_nodes:
                    if node.arch.Float_Type != 0:
                        Correct_nodes.append(node)
                return Correct_nodes
            
        # Prg requires exact Integer multiplication
        if prg.Int_pref == 1:
            # prg dosn't have float multiplication
            if prg.Float_pref == 0:
                for node in available_nodes:
                    if node.arch.Int_Type == 1:
                        Correct_nodes.append(node)
                return Correct_nodes
            
            # Prg requires exact Float multiplication
            if prg.Float_pref == 1:
                for node in available_nodes:
                    if node.arch.Int_Type == 1 and node.arch.Float_Type == 1:
                        Correct_nodes.append(node)
                return Correct_nodes
            
            # Prg has Float multiplication and it can be approximate
            if prg.Float_pref == 2:
                for node in available_nodes:
                    if node.arch.Int_Type == 1 and node.arch.Float_Type != 0:
                            Correct_nodes.append(node)
                return Correct_nodes
        # Prg has Integer multiplication and it can be approximate
        if prg.Int_pref == 2:
            # prg dosn't have float multiplication
            if prg.Float_pref == 0:
                for node in available_nodes:
                    if node.arch.Int_Type != 0:
                        Correct_nodes.append(node)
                return Correct_nodes
            
            # Prg requires exact Float multiplication
            if prg.Float_pref == 1:
                for node in available_nodes:
                    if node.arch.Int_Type != 0 and node.arch.Float_Type == 1:
                        Correct_nodes.append(node)
                return Correct_nodes
            
            # Prg has Float multiplication and it can be approximate
            if prg.Float_pref == 2:
                for node in available_nodes:
                    if node.arch.Int_Type != 0 and node.arch.Float_Type != 0:
                            Correct_nodes.append(node)
                return Correct_nodes
        return Correct_nodes

    def FF(self,Nodes, prg):
        for node in Nodes:
            node.assign_prg(prg)
            return

    def BF(self,Nodes,prg):
        Min_Up = Nodes[0].get_up()
        idx = 0
        for i,node in enumerate(Nodes):
            if node.get_up() <= Min_Up:
                Min_Up = node.get_up() 
                idx = i
        Nodes[idx].assign_prg
    
    def WF(self,Nodes,prg):
        Max_Up = Nodes[0].get_up()
        idx = 0
        for i,node in enumerate(Nodes):
            if node.get_up() >= Max_Up:
                Max_Up = node.get_up() 
                idx = i
        Nodes[idx].assign_prg



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
        
    def Policy_Asgn_Prg(self,Nodes,prg,policy):
        if policy == "FF":
            self.FF(Nodes,prg)
        if policy == "BF": 
            self.BF(Nodes,prg)
        if policy == "WF":
            self.WF(Nodes,prg)
    

    def partition_apprx_aware( self, configuration, prgs,bookie,per_min,last_prg,policy ): 
        #Start from the first program    
        for prg in prgs:
            last_prg[0] = prg.name
            candidate_nodes = []
            # For each program check the nodes that the program can fit on interms of Up and Ue
            for node in configuration.nodes:                
                if node.check_fit( prg ) == True:                    
                    candidate_nodes.append( node )
            # If there is no nodes partition failed
            if len( candidate_nodes ) == 0:
                return 0
            
            # This is for the exact comfiguration
            if configuration.i == 0:
                selected = candidate_nodes[0]
                
                for node in candidate_nodes:
                    
                    if node.acc_up < selected.acc_up:
                        
                        selected = node
                
                selected.assign_prg( prg )
            
            
            else:
            # Check if the nodes can execute the program correctly (E.x: If program needs exact it mulptiply and node doesn't have it, ignore this node)
                Correct_nodes =  self.Correct_Nodes( candidate_nodes, prg )
                if len(Correct_nodes) == 0:
                    return 0
                self.Policy_Asgn_Prg(Correct_nodes,prg,"FF")
        return 1
        
    
    def report( self ):
        
        return ( self.configuration.report() )
        
