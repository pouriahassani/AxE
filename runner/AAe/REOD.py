
import random

emulc = 0.13
amulc = 0.03
xnopc = 0.02

e_mw = 5.07
a_mw = 4.93

wccr = 42000




def get_prg( per ):
    
    loop_cnt = random.randint( 1000, 10000 )
    percent_mul = random.randint( 0, per )
    
    cnt_mul = int( ( percent_mul * loop_cnt ) / 100 )
    cnt_nop = loop_cnt - cnt_mul
    
    ec = round( (emulc * cnt_mul) + (xnopc * cnt_nop) , 2 )
    ac = round( (amulc * cnt_mul) + (xnopc * cnt_nop) , 2 )
    
    # [0.0, 1.0)
    # ~ t = round( ec * (random.random() + 1.75) , 2 )
    # ~ t = round( ec * (random.uniform(0.0, 1.0) + 2) , 2 )
    t = round( ec * random.uniform(3, 13) , 2 )
    
    prg = {
        
         "name" : str( cnt_mul ) + "_" + str( cnt_nop )
        ,"arch" : [
            {
                 "c" : ec
                ,"e" : round( ( ec * e_mw ) , 2 )
            }
            ,{
                 "c" : ac
                ,"e" : round( ( ac * a_mw ) , 2 )
            }
        ]
        
        ,"t" : t
        ,"next_d" : t
        ,"ready" : False
        
    }
    
    # ~ print( prg["name"] + ";" + str(prg["ec"]) + ";" + str(prg["ac"]) )
    
    return prg
    

def get_pprg( data, mn, mx ):
    
    ec = data["e"]
    ac = data["a"]
    
    # [5 * ec, ec * 5 * (1.99
    
    # [0.0, 1.0)
    # ~ t = round( ec * (random.random() + 1.75) , 2 )
    # ~ t = round( ec * ( (4*random.random()) + 6) , 2 )
    t = round( ec * random.uniform(mn, mx) , 2 )
    
    prg = {
        
         "name" : data["name"]
        ,"arch" : [
            {
                 "c" : ec
                ,"e" : round( ( ec * e_mw ) , 2 )
            }
            ,{
                 "c" : ac
                ,"e" : round( ( ac * a_mw ) , 2 )
            }
        ]
        
        ,"t" : t
        ,"next_d" : t
        ,"ready" : False
        
    }
    
    # ~ print( prg["name"] + ";" + str(prg["ec"]) + ";" + str(prg["ac"]) )
    
    return prg
    

def get_node( arch ):
    
    node = {
        
         "acc_up" : 0
        ,"acc_ue" : 0
        ,"diff_p_e" : 0
        ,"arch" : arch
        ,"prgs" : []
        ,"charge" : 200000
        ,"busy_until" : None
        ,"running" : None
        ,"e_max" : 0
        
    }
    
    return node
    

def partition( prgs, nodes ):
    
    for pi, prg in enumerate(prgs):
        
        # ~ print( prg["name"] + ";" + str(upi) + ";" + str(uei) )
        
        # loop over nodes to find a fitting one
        
        for ni, node in enumerate(nodes):
            
            nodes[ni]["diff_p_e"] = None
            
        
        for ni, node in enumerate(nodes):
            
            node_arch = node["arch"]
            
            # calc ci / ti
            
            upi = prg["arch"][ node_arch ]["c"] / prg["t"]
            uei = prg["arch"][ node_arch ]["e"] / prg["t"]
            
            # ~ print( "n" + str( ni ) )
            
            # we add the load of the prg to the node to see if the
            # accumulated load with the current one is smaller than 1
            
            # prg is used to keep track of the accumulated load
            
            tmp = nodes[ni]["acc_up"] + upi
            
            if tmp < 1:
                
                # timing utilization is ok -> only looking at timing
                # this means, that we can allocate the current prg
                
                # ~ print( "load check has passed" )
                
                # next we check the energy utilization
                
                tmp_e = nodes[ni]["acc_ue"] + uei
                
                if ( tmp_e < wccr ):
                    
                    # charging utilization ok -> timing and energy is
                    # covered
                    
                    # ~ print( "energy check has passed" );
                    
                    # remember node as possible choice and record
                    # Prj - Uej. later we will search all the nodes
                    # to find the smallest result.
                    
                    nodes[ni]["diff_p_e"] = wccr - tmp_e;
                    
                
            
        
        # ~ print( repr( nodes ) )
        
        # walk through all the nodes to find the one with the smalles
        # Prj - Uej
        
        selected = None
        
        for ni, node in enumerate(nodes):
            
            if nodes[ni]["diff_p_e"] is not None:
                
                selected = ni
                break
                
            
        
        if selected is None:
            
            return 0
            
        
        for ni, node in enumerate(nodes):
            
            if nodes[ni]["diff_p_e"] is not None:
                
                if ( nodes[ni]["diff_p_e"] < nodes[selected]["diff_p_e"] ):
                    
                    selected = ni
                    
                
            
        
        # if all the nodes have None in diff_p_e, than
        # there was no node for which the timing as well as the energy
        # checks passed. if the previous loop resulted in finding a
        # node with an diff_p_e of None, then the task could
        # not be assigned.
        
        if nodes[selected]["diff_p_e"] is None:
            
            return 0
            
        else:
            
            pass
            # ~ print( "partition was possible" )
            
        
        
        # ~ prgs[pi]["ass_to"] = selected
        
        nodes[selected]["acc_up"] += upi;
        nodes[selected]["acc_ue"] += uei;
        
        print( "added p" + str(pi) + " to n" + str(selected) + " having up of: " + str(nodes[selected]["acc_up"]) )
        
        nodes[selected]["prgs"].append( pi )
        
    
    return 1
    

def nodes_set_e_max( nodes ):
    
    for ni, node in enumerate(nodes):
        node_arch = nodes[ni]["arch"]
        for pi, prg in enumerate(nodes[ni]["prgs"]):
            if nodes[ni]["e_max"] < prgs[pi]["arch"][node_arch]["e"]:
                nodes[ni]["e_max"] = prgs[pi]["arch"][node_arch]["e"]

def each_loop( ni, time ):
    
    # print prgs
    
    # ~ for pi in nodes[ni]["prgs"]: print( repr( prgs[pi] ) )
    
    # set_node_idle
    
    if nodes[ni]["busy_until"] != None:
        if nodes[ni]["busy_until"] < time:
            
            # ~ print( str(time) + " n" + str(ni) + ": became idle" )
            nodes[ni]["busy_until"] = None
            
            # check if the deadline of the prg has been missed
            
            pi = nodes[ni]["running"]
            time_until_d = prgs[pi]["next_d"] - time
            
            # ~ print( "time to deadline: " + str( time_until_d ) )
    
    for pi in nodes[ni]["prgs"]:
        
        # set_prgs_ready
        
        if prgs[pi]["ready"] ==  False:
            if prgs[pi]["next_d"] < time:
                
                # ~ print( str(time) + " p" + str(pi) + ": became ready" )
                prgs[pi]["ready"] = True








def get_ST( ni, time ):
    
    # ~ print( "\nrunning ST for n" + str(ni) )
    
    smallest_ST_tau = MAX
    smallest_ST_tau_new = MAX
    
    for pi, prg in enumerate(nodes[ni]["prgs"]):
        
        d = 0
        
        # ~ print( "\nin ST for p" + str(pi) )
        # ~ print( "checking clairvoyance: " + str(get_clair()) )
        
        instances = get_clair() / prgs[pi]["t"]
        
        # ~ print( "covering instances: " + str(instances) )
        # ~ print( "having a period of: " + str(prgs[pi]["t"]) )
        
        j = 0
        
        while ( j < instances ):
            
            d += prgs[pi]["t"]
            
            # ~ print( "checking instance: " + str(j) )
            # ~ print( "until it's deadline: " + str(d) )
            
            smallest_ST_tau_new = get_ST_tau( ni, pi, d, time )
            
            # ~ print( "\n=> back in ST smalles_ST_tau_new: " + str(smallest_ST_tau_new) )
            
            if ( smallest_ST_tau_new < smallest_ST_tau ):
                
                # ~ print( "new ST tau is smaller old ST tau was: " + str(smallest_ST_tau) )
                
                smallest_ST_tau = smallest_ST_tau_new
                
            
            j += 1
            
    
    # ~ print( "\nfinished checking instances of p" + str(pi) )
    
    return smallest_ST_tau
    


def get_ST_tau( ni, pi, d, time ):
    
    # ~ print( "\n# ST_tau\n" )
    
    # ~ print( "ST_tau for p" + str(pi) )
    
    ST_tau = d
    #ST_tau = time_get_cnt_until( prgs[ prg_i ].next_deadline_clk_cnt, prgs[ prg_i ].next_deadline_overflows );
    
    # ~ print(" ST_tau = T: " + str(ST_tau) )
    
    ST_tau -= get_h( ni, d, time )
    
    if ST_tau < 0:
        
        ST_tau = 0
        
    
    return ST_tau
    
def get_h( ni, d, time ):
    
    # ~ print( "\ngetting h for period: " + str(d) + "\n")
    
    executions = 0
    h = 0
    
    for pi, prg in enumerate(nodes[ni]["prgs"]):
        
        # figure out how many times the task can be executed during
        # the period defined by d.
        
        # ~ print( "looking at p" + str(pi) )
        # ~ print( "having period t of: " + str( prgs[pi]["t"] ) )
        
        if prgs[pi]["t"] <= d:
            
            # ~ print( "t_clk_cnt is smaller than d" )
            
            # the number of times the prg can be executed in the time span
            
            executions = d / prgs[pi]["t"];
            
            # yes, it is c, the worst-case execution time.
            # that is how the function is defined in the papers.
            
            h += ( executions * prgs[pi]["arch"][ nodes[ni]["arch"] ]["c"] )
            
            # ~ print( "possible executions: " + str( executions ) )
            # ~ print( "considering di: " + str( d ) )
            # ~ print( "and the prg's period: " + str( prgs[pi]["t"] ) )
            # ~ print( "h is now: " + str( h ) )
            # ~ print( "considering c of: " + str( prgs[pi]["arch"][ nodes[ni]["arch"] ]["c"] ) )
            
        # ~ else:
            
            # ~ print( "t_clk_cnt is greater than d" )
            # ~ print( "-> ignoring" )
            
        
    
    # ~ print( "\n## h - end\n" )
    
    return h



def schedule( nodes ):
    
    time = 0
    
    # ~ for ni, node in enumerate(nodes):
        # ~ print( repr( nodes[ni] ) )
        # ~ for pi in nodes[ni]["prgs"]:
            # ~ print( repr( prgs[pi] ) )
    
    
    while 1 == 1:
        
        for ni, node in enumerate(nodes):
            
            if (len(nodes[ni]["prgs"]) == 0 ):
                continue
            
            each_loop( ni, time )
            
            pi = prg_to_run( ni, time )
            
            if pi == -1:
                continue
            
            # there is a prg to run, but we do not know if we should yet
            
            # -----------------------------------------------------------------
            # 
            # ED-H rule 3
            # 
            # -----------------------------------------------------------------
            
            # idle if there are jobs, but no energy or no slack energy
            # -> empty battery
            
            if nodes[ni]["charge"] < nodes[ni]["e_max"]:
                
                # ~ print( "n" + str(ni) + " wants to run p" + str(pi) + " but there is not enough charge left" )
                # ~ print( "charge left: " + str(nodes[ni]["charge"]) + " but max is: " + str(nodes[ni]["e_max"]) )
                
                print( "c = 0: " + str(ni) )
                
                return time
                
                continue
                
            
            # slack energy
            
            se = get_SE( ni, time )
            
            # ~ print( "------------------" )
            # ~ print( "finished running SE: " + str(se) )
            
            if ( se < nodes[ni]["e_max"] ):
                
                # ~ print( "SE is empty" )
                
                print( "SE = 0: " + str(ni) )
                
                return time
                
                continue
                
            
            # -----------------------------------------------------------------
            # 
            # ED-H rule 4
            # 
            # -----------------------------------------------------------------
            
            # busy if there are jobs and battery is full or no slack time
            # -> full battery time critical
            
            # das ist alles wurscht, da wir es sowieso ausfuehren
            
            # ~ print( "==================" )
            # ~ print( "ED-H rule 4" )
            # ~ print( "" )
            # ~ print( "battery full or no slack time" )
            
            # ~ if ( nodes[ni]["charge"] >= get_charge_max() ):
                
                # ~ print( "E is full" )
                
                # ~ return prg
                
            
            # ~ st = get_ST( ni, time )
            
            # ~ if ( 0 == st ):
                
                # ~ print( "ST is 0" )
                
                # ~ return prg
                
            
            
            assign( ni, pi, time )
        
        time += 1
        
        
        
        # ~ if time == 500:
            # ~ exit()
        
        
        
    
    # ~ print( repr( nodes ) )
    

def print_combinations( combination, pre ):
    
    n0 = ""
    n1 = ""
    
    # ~ print( "------------------" )
    
    s = ""
    
    for combination_i, combination in enumerate(combinations):
        
        # ~ if combinations[combination_i]["0"] == 0:
            # ~ n0 = "e"
        # ~ else:
            # ~ n0 = "a"
        
        # ~ if combinations[combination_i]["1"] == 0:
            # ~ n1 = "e"
        # ~ else:
            # ~ n1 = "a"
        
        # ~ s += n0 + n1 + ";" + str(combinations[combination_i]["res"]) + ";"
        s += str(combinations[combination_i]["res"]) + ";"
        
    
    print( pre + ";" + s )
    

def print_minmax( minmax ):
    
    for mimx in minmax:
        
        s = str( mimx ) + ";"
        
        for comb in minmax[mimx]:
            
            s += str( minmax[mimx][comb]["min"] ) + ";" + str( minmax[mimx][comb]["max"] ) + ";"
            s += str( minmax[mimx][comb]["rmin"] ) + ";" + str( minmax[mimx][comb]["rmax"] ) + ";;"
            
        
        print( s )
        
    


pprgs = [
     { "name" : "dhrystone"    ,"e" : 26.63   ,"a" : 26.52   }
    ,{ "name" : "msort"        ,"e" : 21.45   ,"a" : 21.45   }
    ,{ "name" : "norx"         ,"e" : 57.09   ,"a" : 57.09   }
    ,{ "name" : "primes"       ,"e" : 2.69    ,"a" : 2.69    }
    ,{ "name" : "sha256"       ,"e" : 50.50   ,"a" : 50.44   }
    ,{ "name" : "square_mmult" ,"e" : 9.61    ,"a" : 7.67    }
    ,{ "name" : "blowfish"     ,"e" : 397.57  ,"a" : 397.57  }
    ,{ "name" : "aes"          ,"e" : 1651.60 ,"a" : 1651.60 }
    ,{ "name" : "grayscale"    ,"e" : 89.83   ,"a" : 25.55   }
    ,{ "name" : "qsort"        ,"e" : 26.93   ,"a" : 5.22    }
    ,{ "name" : "sharpen_mul"  ,"e" : 95.57   ,"a" : 78.07   }
]

ran = 10
per = 1

j = 0

minmax = {}

# ~ while per < 11:
    
minmax[ "6" ] = {}

minmax[ "6" ][ 0 ] = {}
minmax[ "6" ][ 1 ] = {}
minmax[ "6" ][ 2 ] = {}

minmax[ "6" ][ 0 ][ "min" ] = 1000000
minmax[ "6" ][ 0 ][ "max" ] = 0
minmax[ "6" ][ 0 ][ "rmin" ] = 1000000
minmax[ "6" ][ 0 ][ "rmax" ] = 0


minmax[ "6" ][ 1 ][ "min" ] = 1000000
minmax[ "6" ][ 1 ][ "max" ] = 0
minmax[ "6" ][ 1 ][ "rmin" ] = 1000000
minmax[ "6" ][ 1 ][ "rmax" ] = 0

minmax[ "6" ][ 2 ][ "min" ] = 1000000
minmax[ "6" ][ 2 ][ "max" ] = 0
minmax[ "6" ][ 2 ][ "rmin" ] = 1000000
minmax[ "6" ][ 2 ][ "rmax" ] = 0
    
    # ~ per += 0.25
    

# ~ print( repr(minmax) )

per = 10

while j < 1:
    
    per = 6
    
    while per < 6.25:
        
        i = 0
        
        for combination_i, combination in enumerate(combinations):
            
            combinations[combination_i]["res"] = 0
            combinations[combination_i]["rmin"] = 1000000
            combinations[combination_i]["rmax"] = 0
            
        
        while i < 1:
            
            redo = False
            
            # ~ time = 0
            
            prgs = []
            
            for pprg in pprgs:
                # ~ # prgs.append( get_pprg( pprg, 5, 15 ) )
                prgs.append( get_pprg( pprg, per, per+ran ) )
            
            
            # ~ prg_i = 0
            # ~ while prg_i < 11:
                # ~ prgs.append( get_prg( per * 10 ) )
                # ~ prg_i += 1
                
            
            for combination_i, combination in enumerate(combinations):
                
                nodes = []
                
                nodes.append( get_node( combinations[combination_i]["0"] ) )
                nodes.append( get_node( combinations[combination_i]["1"] ) )
                
                res = partition( prgs, nodes )
                
                combinations[combination_i]["res"] += res
                
                if res == 1:
                    
                    # ~ print( "combination: " + str(combinations[combination_i]["0"]) + " - " + str(combinations[combination_i]["1"]) )
                    
                    nodes_set_e_max( nodes )
                    time = schedule( nodes )
                    
                    
                    # ~ print( "time: " + str(time) )
                    # ~ print( "rmax: " + str(combinations[combination_i]["rmax"]) )
                    
                    # ~ combinations[combination_i]["total_running"] += time
                    
                    if time < combinations[combination_i]["rmin"]:
                        combinations[combination_i]["rmin"] = time
                    if time > combinations[combination_i]["rmax"]:
                        combinations[combination_i]["rmax"] = time
                    
                else:
                    
                    print( "redo" )
                    
                    redo = True
                    
                
                # ~ print( str( len(nodes[0]["prgs"] ) ) )
                
            
            if redo == False:
                i += 1
        
        
        # hier weiss ich dann wie viele erfolgreich verpackt werden konnten
        
        # ~ print( repr( combinations ) )
        # ~ exit()
        
        # ~ print_combinations( combinations, str(per).replace(".", ",") + ":" + str(per+ran).replace(".", ",") )
        
        for combination_i, combination in enumerate(combinations):
            
            if combinations[combination_i]["res"] < minmax[ str( per ) ][ combination_i ][ "min" ]:
                minmax[ str( per ) ][ combination_i ][ "min" ] = combinations[combination_i]["res"]
            elif combinations[combination_i]["res"] > minmax[ str( per ) ][ combination_i ][ "max" ]:
                minmax[ str( per ) ][ combination_i ][ "max" ] = combinations[combination_i]["res"]
            
            # ~ print( "comb: " + str(combination_i) )
            # ~ print( str(combinations[combination_i]["rmin"]) )
            # ~ print( str(minmax[ str( per ) ][ combination_i ][ "rmin" ]) )
            
            # ~ if combinations[combination_i]["rmin"] == 0:
                # ~ combinations[combination_i]["rmin"] = 1000
            
            if combinations[combination_i]["rmin"] < minmax[ str( per ) ][ combination_i ][ "rmin" ]:
                minmax[ str( per ) ][ combination_i ][ "rmin" ] = combinations[combination_i]["rmin"]
            if combinations[combination_i]["rmax"] > minmax[ str( per ) ][ combination_i ][ "rmax" ]:
                minmax[ str( per ) ][ combination_i ][ "rmax" ] = combinations[combination_i]["rmax"]
            
        
        # ~ print( repr( minmax ) )
        # ~ exit()
        
        per += 0.25
        
    
    # ~ print_minmax( minmax )
    # ~ exit()
    
    j += 1
    

print_minmax( minmax )

