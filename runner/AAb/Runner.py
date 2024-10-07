
from defines import *

import random

from Partitioner import *
from Scheduler import *
from Bookie import *

class Runner:
    
    def __init__(self):
        
        pass
        
    
    def prepare_prgs( self, prgs, per_min, per_max ):
        
        prgs[ 0].t = 259.78
        prgs[ 1].t = 202.71
        prgs[ 2].t = 431.58
        prgs[ 3].t = 18.8
        prgs[ 4].t = 439.64
        prgs[ 5].t = 94.53
        prgs[ 6].t = 3331.48
        prgs[ 7].t = 12056.3
        prgs[ 8].t = 610.66
        prgs[ 9].t = 221.2
        prgs[10].t = 757.43
        # ~ prgs[ 6].t = 610.66
        # ~ prgs[ 7].t = 221.2
        # ~ prgs[ 8].t = 757.43
        
        for prg in prgs:
            prg.set_t( random.uniform(per_min, per_max) )
            
        
    
    #
    # run
    #
    
    def run( self, configurations, prgs, per_min, per_max,i, ignore_fails = True, bookie = None ):
        
        self.prepare_prgs( prgs, per_min, per_max )
        
        # ~ for prg in prgs:
            # ~ print( prg.p() )
        
        partitioner = Partitioner()
        
        for configuration in configurations:
            
            configuration.reset_nodes()
            records = []
            print(configuration.i)
            # ~ res = partitioner.partition( configuration, prgs )
            prg_name = ["m"]
            res = partitioner.partition_apprx_aware( configuration, prgs,bookie,per_min,prg_name,configuration.name )
            filename = "Arch_asign_prg_data_" + configuration.name
            if res:
                with open(filename, 'a') as file:
                    # Write to the file
                    file.write(f"\nper_min: {per_min}\t i: {i}\n")
                    for node in configuration.nodes:
                        file.write(f"\nNode[{node.arch.name}]: ")
                        for prg in node.prgs:
                            file.write(f"{prg.name}, ")
            for PRG in prgs:
                if prg_name[0] == PRG.name:
                    last_prg = PRG
                    break

            # if configuration.i == 0:
            #     for node in configuration.nodes:
            #         up = node.arch.get_up( last_prg )
            #         ue = node.arch.get_ue( last_prg )
            #         up = 0
            #         ue = 0
            #         bookie.record_entry_2_deep( configuration.i, str(per_min) +"_XE_" +  str(node.i) + "_E" , node.acc_ue + ue )
            #         bookie.record_entry_2_deep( configuration.i, str(per_min) +"_XE_" +  str(node.i) + "_U"  , node.acc_up + up )
            # else:
            #     for node in configuration.nodes:
            #         up = node.arch.get_up( last_prg )
            #         ue = node.arch.get_ue( last_prg )
            #         up = 0
            #         ue = 0
            #         bookie.record_entry_2_deep( configuration.i, str(per_min) +"_" + (str(node.name))[1:]  + "_E" , node.acc_ue + ue)
            #         bookie.record_entry_2_deep( configuration.i, str(per_min) +"_" + (str(node.name))[1:]  + "_U"  , node.acc_up + up )
            # for i in records:
            #     print(i)
            if (res != 1) and (ignore_fails == False):
                print( "try again" )
                return False
            
            if res == 0:
                configuration.part_failed += 1;
                bookie.record_entry_2_deep( configuration.i, str(per_min)+"_fail", i )
            elif res == -1:
                configuration.part_no_choice += 1;
                bookie.record_entry_2_deep( configuration.i, str(per_min)+"_no", i )
            else:
                configuration.partition_succ()
                bookie.record_entry_2_deep( configuration.i, str(per_min) + "_success" , i )
                print("successful")
                print("node 0")
                # for i in configuration.nodes[0].prgs:
                #     print(i.name, end=" ")
                # print("node 1")
                # for i in configuration.nodes[1].prgs:
                #     print(i.name, end=" ")
                
                # print( configuration.p() )
                # print( "sched" )
                
                # scheduler = Scheduler()
                # time = scheduler.schedule( configuration, prgs )
                
                # print( configuration.p_charges() )
                
                # print( "time: ", str( time ) )
                
                # if bookie is not None:
                bookie.record_entry_2_deep( configuration.i, str(per_min) + "_run_idx", i )
                    # bookie.record_entry_2_deep( configuration.i, str(per_min)+"_0_up", configuration.nodes[0].acc_up )
                    # bookie.record_entry_2_deep( configuration.i, str(per_min)+"_1_up", configuration.nodes[1].acc_up )
                # bookie.record_entry_2_deep( configuration.i, str(per_min)+"_sched", time )
                # bookie.record_entry_2_deep( configuration.i, str(per_min)+"charge_0", configuration.nodes[0].charges )
                # bookie.record_entry_2_deep( configuration.i, str(per_min)+"charge_1", configuration.nodes[1].charges )
                    
                
            
        return True
        
    
    #
    # run multi ranges
    #
    
    def run_multi_ranges( self, configurations, prgs, per_start, per_step, per_end, per_range, multi_runs, bookie = None ):
        
        i = 0
        
        while i < multi_runs:
            
            self.run_ranges( configurations, prgs, per_start, per_step, per_end, per_range, bookie )
            
            i += 1
            
        
    
    #
    # run ranges
    #
    
    def run_ranges( self, configurations, prgs, per_start, per_step, per_end, per_range, bookie = None ):
        
        per = per_start
        k = -1
        while( per <= per_end ):
            k+=1
            # print( str( per ) )
            
            self.run_100( configurations, prgs, per, per + per_range, bookie )
            
            for configuration in configurations:
                # print( configuration.result() )
                
                # bookie.record_entry_2_deep( configuration.i, str(per) + "_success" , configuration.succ_partitions )
                # bookie.record_entry_2_deep( configuration.i, str(per)+"_fail", configuration.part_failed )
                # bookie.record_entry_2_deep( configuration.i, str(per)+"_no", configuration.part_no_choice )
                
                configuration.reset()
                
            
            per += per_step
        # print(k)
        
    
    #
    # run 100
    #
    
    def run_100( self, configurations, prgs, per_min, per_max, bookie = None ):
        
        i = 0
        
        while( i < 100 ):
            print(f"range {per_min} itr: {i}")
            self.run( configurations, prgs, per_min, per_max,i, True, bookie )
            
            i += 1
            
        
        # ~ for configuration in configurations:
            # ~ print( configuration.result() )
        
    
    #
    # run once
    #
    
    def run_once( self, configurations, prgs, per_min, per_max, bookie = None ):
        i= 0
        succ_run = self.run( configurations, prgs, per_min, per_max,i, True, bookie )
        
        for configuration in configurations:
            for node in configuration.nodes:
                print( node.report_history() )
    
    #
    # run until succ
    #
    
    def run_until_succ( self, configurations, prgs, per_min, per_max, bookie = None ):
        
        succ_run = False
        
        while succ_run == False:
            
            for configuration in configurations:
                configuration.reset()
            
            succ_run = self.run( configurations, prgs, per_min, per_max,i, False, bookie )
            
        
        for configuration in configurations:
            for node in configuration.nodes:
                print( node.report_history() )
        
        for prg in prgs:
            
            print( prg.p() )
            
