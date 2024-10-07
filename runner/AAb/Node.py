
from defines import *

import math

class Node:
    
    def __init__(self, i, name, arch ):
        
        self.i = i
        self.name = name
        self.arch = arch
        
        self.charge = CHARGE_INITIAL
        self.charges = []
        
        self.acc_up = 0
        self.acc_ue = 0
        
        self.diff_p_e = 0
        
        # self.wccr = 1000
        self.wccr = 2
        
        self.prgs = []
        self.hist = []
        
        self.ups = []
        self.ues = []
        
        self.busy_until = 0
        self.prg_running = None
        self.e_max = 0
        
    
    def reset( self ):
        
        self.charge = CHARGE_INITIAL
        self.charges = []
        
        self.acc_up = 0
        self.acc_ue = 0
        
        self.diff_p_e = 0
        
        self.prgs = []
        self.hist = []
        
        self.busy_until = 0
        self.prg_running = None
        self.e_max = 0
        
    
    def get_arch( self ):
        
        return self.arch.i
        
    
    def is_choice( self, prg, choice ):
        
        if   ( choice == "first"  ): return self.is_first_choice( prg )
        elif ( choice == "second" ): return self.is_second_choice( prg )
        elif ( choice == "third"  ): return self.is_third_choice( prg )
        elif ( choice == "no"     ): return self.is_no_choice( prg )
        else: exit()
    
    def is_first_choice( self, prg ):
        
        if   ( ( prg.pref == PREF_APPROX ) and ( self.get_arch() == ARCH_APPRX ) ): return True
        elif ( ( prg.pref == PREF_EXACT  ) and ( self.get_arch() == ARCH_EXACT ) ): return True
        else: return False
    
    def is_second_choice( self, prg ):
        
        #aa1
        # ~ if ( ( prg.pref == PREF_ANY ) and ( self.get_arch() == ARCH_EXACT ) ): return True
        # ~ else: return False
        
        #aa2
        # ~ if ( ( prg.pref == PREF_ANY ) and ( self.get_arch() == ARCH_APPRX ) ): return True
        # ~ else: return False
        
        #aa3
        if ( ( prg.pref == PREF_ANY ) and ( self.get_arch() == ARCH_APPRX ) ): return True
        if ( ( prg.pref == PREF_ANY ) and ( self.get_arch() == ARCH_EXACT ) ): return True
        else: return False
    
    def is_third_choice( self, prg ):
        
        #aa1
        # ~ if ( ( prg.pref == PREF_ANY ) and ( self.get_arch() == ARCH_APPRX ) ): return True
        # ~ elif ( ( prg.pref == PREF_APPROX ) and ( self.get_arch() == ARCH_EXACT ) ): return True
        # ~ else: return False
        
        #aa2
        # ~ if ( ( prg.pref == PREF_ANY ) and ( self.get_arch() == ARCH_EXACT ) ): return True
        # ~ elif ( ( prg.pref == PREF_APPROX ) and ( self.get_arch() == ARCH_EXACT ) ): return True
        # ~ else: return False
        
        #aa3
        return False
    
    def is_no_choice( self, prg ):
        
        if ( ( prg.pref == PREF_EXACT ) and ( self.get_arch() == ARCH_APPRX ) ): return True
        else: return False
        
    def get_up(self):
        return self.acc_up
    
    def check_fit( self, prg ):
        
        up = self.arch.get_up( prg )
        ue = self.arch.get_ue( prg )
        
        if (
            ( ( self.acc_up + up ) < 1 )
        and ( ( self.acc_ue + ue ) < self.wccr )
        ):
            return True
        else:
            return False
        
    
    def assign_prg( self, prg ):
        
        # ~ print( "assign: " + prg.p() )
        
        up = self.arch.get_up( prg )
        ue = self.arch.get_ue( prg )
        
        self.acc_up += up
        self.acc_ue += ue
        
        self.prgs.append( prg )
        
        self.hist.append( prg.pn() + "\t" + str(self.i) + "\t" + str(self.arch.i) + "\t" + str(up) + "\t" + str(ue) + "\t" + str(self.acc_up) + "\t" + str(self.acc_ue) + "\t" + str(self.diff_p_e) )
        
    
    def do_partition( self, prg ):
        self.assign_prg( prg )
    
    def try_partition( self, prg ):
        
        up = self.arch.get_up( prg )
        ue = self.arch.get_ue( prg )
        
        if (
            ( ( self.acc_up + up ) < 1 )
        and ( ( self.acc_ue + ue ) < self.wccr )
        ):
            self.diff_p_e = self.wccr - (self.acc_ue + ue)
        else:
            self.diff_p_e = None
        
    
    def p( self ):
        
        return ( "node" + str(self.i) + " " + self.name + " arch: " + self.arch.p() )
        
    
    def report( self ):
        
        return ( "node" + str(self.i) + ": arch: " + str(self.arch.i) + ": up: " + str(self.acc_up) + " ue: " + str(self.acc_ue) )
        
    
    def record_charges( self, time ):
        
        self.charges.append( str(time) + ";" + str(self.charge) )
        
    
    def report_history( self ):
        
        s = ""
        for h in self.hist:
            s += h + "\n"
        
        return s
    
    def set_e_max( self ):
        
        self.e_max = 0
        
        for prg in self.prgs:
            
            if self.e_max < self.arch.get_e( prg ):
                
                self.e_max = self.arch.get_e( prg )
                
            
        
    
    # ------------------------------------------------------------------
    # 
    # get_SE
    #
    # ------------------------------------------------------------------
    
    def get_SE( self ):
        
        if 1 == DEBUG: print( "\nSE for n" + str(ni) )
        
        smallest_SE_tau = MAX
        smallest_SE_tau_new = MAX
        
        for prg in self.prgs:
            
            d = 0
            
            # iterating over all instances of a prg that fit into the time
            # until the clairvoyance ends.
            
            if 1 == DEBUG: print( "\nin SE for " + prg.p() )
            
            instances = math.floor( CLAIR / prg.t )
            
            if 1 == DEBUG: print( "checking clairvoyance: " + str(CLAIR) )
            if 1 == DEBUG: print( "instances: " + str(instances) + " with t: " + str(prg.t) )
            
            j = 0
            
            while ( j < instances ):
                
                d += prg.t
                
                if 1 == DEBUG: print( "checking instance: " + str(j) + " until it's deadline: " + str(d) )
                smallest_SE_tau_new = self.get_SE_tau( prg, d )
                if 1 == DEBUG: print( "\n=> back in SE smalles_SE_tau_new: " + str(smallest_SE_tau_new) )
                
                if ( smallest_SE_tau_new < smallest_SE_tau ):
                    
                    if 1 == DEBUG: print( "new SE tau is smaller -> old SE tau was: " + str(smallest_SE_tau) )
                    smallest_SE_tau = smallest_SE_tau_new
                    
                
                j += 1
                
            
            if 1 == DEBUG: print( "\nfinished checking instances of " + prg.p() )
            
        
        return smallest_SE_tau
    
    # ------------------------------------------------------------------
    # 
    # get_SE_tau
    #
    # ------------------------------------------------------------------
    
    def get_SE_tau( self, prg, d ):
        
        if 1 == DEBUG: print( "\n# SE_tau for " + prg.p() + "\n" )
        
        SE_tau = self.charge
        if 1 == DEBUG: print( "SE_tau = E: " + str(SE_tau) )
        
        SE_tau += self.get_Es( prg, d )
        if 1 == DEBUG: print( "SE_tau += Es: " + str(SE_tau) )
        
        SE_tau -= self.get_g( prg, d )
        
        if ( SE_tau < 0 ):
            SE_tau = 0
        
        if 1 == DEBUG: print("\nSE_tau -= g: " + str(SE_tau) + "\n")
        
        return SE_tau
    
    # ------------------------------------------------------------------
    # 
    # get_Es
    #
    # ------------------------------------------------------------------
    
    def get_Es( self, prg, d ):
        
        if 1 == DEBUG: print( "\n## ES\n" )
        
        Es = 0
        
        # number of charges = deadline / interval
        
        num_of_charges = math.floor( d / EH_CHARGING_INTV )
        
        if 1 == DEBUG: print("num_of_charges: " + str(num_of_charges))
        if 1 == DEBUG: print("based on di: " + str(d))
        if 1 == DEBUG: print("and interval: " + str(EH_CHARGING_INTV))
        
        Es += ( num_of_charges * CHARGE )
        
        if 1 == DEBUG: print( "ES: " + str(Es) )
        if 1 == DEBUG: print( "\n## ES - end\n" )
        
        return Es
    
    # ------------------------------------------------------------------
    # 
    # get_g
    #
    # ------------------------------------------------------------------
    
    def get_g( self, prg_tau, d ):
        
        if 1 == DEBUG: print( "\n## g for deadline: " + str( d ) )
        
        g = 0
        
        for prg in self.prgs:
            
            # figure out how many times the task can be executed during
            # the period defined by d.
            
            if 1 == DEBUG: print( "looking at " + prg.p() + " having period t of: " + str( prg.t ) )
            
            # any prg with a period that is larger than the period of the
            # prg to be run can be ignored.
            
            if ( prg.t <= d ):
                
                executions = d / prg.t
                
                g += ( executions * self.arch.get_e( prg ) )
                
                if 1 == DEBUG: print( "possible executions: " + str(executions) )
                if 1 == DEBUG: print( "considering di: " + str(d) )
                if 1 == DEBUG: print( "and the prg's period: " + str( prg.t ) )
                if 1 == DEBUG: print( "g is now: " + str(g) )
                if 1 == DEBUG: print( "considering e of: " + str(self.arch.get_e( prg )) )
                
            else:
                
                if 1 == DEBUG: print( "t_clk_cnt is greater than d -> ignoring" )
                
            
        
        if 1 == DEBUG: print( "\n## g - end\n" )
        
        return g
    
    def run_prg( self, prg, time ):
        
        # ~ print( "assign n" + str(ni) + " p" + str(pi) )  
        
        prg.d_next += prg.t
        
        
        if prg.s == 100:
            
            prg.s = 0
            
        else:
            
            self.charge -= self.arch.get_e( prg )
            prg.s += 1
            
        
        self.busy_until = time + self.arch.get_c( prg )
        self.prg_running = prg
        
        
        # ~ print( "charge: " + str( nodes[ni]["charge"] ) )
        
    
