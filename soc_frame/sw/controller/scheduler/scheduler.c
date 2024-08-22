
#include "scheduler.h"

int get_prg_apply_edh_rules( int node_i )
{
	#ifdef DBG_EDH_RULES
		
		print_str( "\ngetting prg by edh rules\n" );
		
	#endif
	
	int prg_i = BE_IDLE;
	
	// -----------------------------------------------------------------
	//
	// ED-H rule 2
	//
	// -----------------------------------------------------------------
	
	// idle if there are no jobs available
	// -> nothing to do
	
	if ( TRUE == L_r_empty( node_i ) )
	{
		#ifdef DBG_EDH_RULES
			print_str( "-> L_r is empty\n" );
		#endif
		
		return BE_IDLE;
	}
	
	// -----------------------------------------------------------------
	//
	// ED-H rule 1
	//
	// -----------------------------------------------------------------
	
	// EDF is used to select the next job
	
	prg_i = get_prg_i_via_edf( node_i );
	// -----------------------------------------------------------------
	// 
	// ED-H rule 3
	// 
	// -----------------------------------------------------------------
	
	// idle if there are jobs, but no energy or no slack energy
	// -> empty battery
	
	#ifdef DBG_EDH_RULES
		
		print_str( "\n==================\n" );
		print_str( "ED-H rule 3\n" );
		
		print_str( "checking for no energy\n" );
	#endif
	
	if ( TRUE == E_is_empty( node_i ) )
	{
		#ifdef DBG_EDH_RULES
			print_str( "\n-> E is empty\n" );
		#endif
		
		return BE_IDLE;
	}
	
	#ifdef DBG_EDH_RULES
		
		print_str( "checking slack energy\n" );
	#endif
	
	unsigned int se = SE( node_i );
	
	#ifdef DBG_EDH_RULES
		
		print_str( "------------------\n" );
		print_str( "finished running SE: " ); print_dec( se );
		
	#endif
	
	if ( TRUE == is_empty( se ) )
	{
		#ifdef DBG_EDH_RULES
			print_str( "\nSE is empty\n" );
		#endif
		
		return BE_IDLE;
	}
	
	// -----------------------------------------------------------------
	// 
	// ED-H rule 4
	// 
	// -----------------------------------------------------------------
	
	// busy if there are jobs and battery is full or no slack time
	// -> full battery time critical

	#ifdef DBG_EDH_RULES
		
		print_str( "\n==================\n" );
		print_str( "ED-H rule 4\n" );
		
		print_str( "battery full or no slack time\n" );
	#endif
	
	if ( TRUE == E_is_full( node_i ) )
	{
		#ifdef DBG_EDH_RULES
			print_str( "E is full\n" );
		#endif
		
		return prg_i;
	}
	
	unsigned int st = ST( node_i );
	
	if ( 0 == st )
	{
		#ifdef DBG_EDH_RULES
			print_str( "\nST is 0\n" );
		#endif
		
		return prg_i;
	}
	
	// -----------------------------------------------------------------
	//
	// ED-H rule 5
	//
	// -----------------------------------------------------------------
	
	// asap if anything else
	
	#ifdef DBG_EDH_RULES
		print_str( "\nfound a prg to run: " );
		print_dec( prg_i );
	
	#endif
	
	return prg_i;
}



int L_r_empty( int node_i )
{
	#ifdef DBG_EDH_L_R
		
		print_str( "\ncheck L_r empty for n" ); print_dec( node_i );
	#endif
	
	int i;
	int prg_i = 0;
	
	unsigned int end = ( LAST_NODE(node_i) ) ? NUM_PRGS : nodes[ node_i+1 ].prgs_start_i;
	
	#ifdef DBG_EDH_L_R
		print_str( "\nrange: " );
		print_dec( nodes[ node_i ].prgs_start_i ); print_str( " - " ); print_dec( end ); 
	#endif
	
	// iterating all the prgs assigned to the node
	// -----------------------------------------------------------------
	
	for ( i = nodes[ node_i ].prgs_start_i; i < end; i++ )
	{
		if ( ready_list[ i ] == 1 )
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

int get_prg_i_via_edf( int node_i )
{
	#ifdef DBG_EDH_EDF
		print_str( "\nget p via edf for n" ); print_dec( node_i );
	#endif
	
	int i;
	int prg_i = 0;
	int prg_i_earliest_deadline = 0;
	
	unsigned int earliest_deadline = MAX;
	unsigned int earliest_deadline_new = MAX;
	
	unsigned int end = ( LAST_NODE(node_i) ) ? NUM_PRGS : nodes[ node_i+1 ].prgs_start_i;
	
	#ifdef DBG_EDH_EDF
		print_str( "\nrange: " );
		print_dec( nodes[ node_i ].prgs_start_i ); print_str( " - " ); print_dec( end );
	#endif
	
	// iterating all the prgs assigned to the node
	// -----------------------------------------------------------------
	
	for ( i = nodes[ node_i ].prgs_start_i; i < end; i++ )
	{
		prg_i = prgs_list[ i ];
		
		if ( ready_list[ i ] == 1 )
		{
			earliest_deadline_new = time_get_cnt_until( prgs[ prg_i ].next_deadline_clk_cnt, prgs[ prg_i ].next_deadline_overflows );
			
			#ifdef DBG_EDH_EDF
				print_str("\np");print_dec(prg_i);print_str(" d: ");print_dec(earliest_deadline_new);
			#endif
			
			if ( earliest_deadline_new < earliest_deadline )
			{
				earliest_deadline = earliest_deadline_new;
				prg_i_earliest_deadline = prg_i;
			}
		}
	}
	
	#ifdef DBG_EDH_EDF
		print_str("\nearliest deadline has p");print_dec(prg_i_earliest_deadline);
	#endif
	
	return prg_i_earliest_deadline;
}








unsigned int E( int node_i ) // OK
{
	return nodes[node_i].charge;
}

// 3)

int E_is_empty( int node_i ) // OK
{
	#ifdef DBG_EDH_E
		print_str("\nchecking E empty for n");print_dec(node_i);
		print_str("\nE: ");print_dec( E(node_i) );
	#endif
	
	if ( E(node_i) < task_set.e_max )
	{
		return TRUE;
	}
	
	return FALSE;
}



int is_empty( unsigned int whatever )
{
	if ( whatever < task_set.e_max )
	{
		return TRUE;
	}
	
	return FALSE;
}

// 4)

int E_is_full( int node_i ) // OK
{
	// C <= E(t) < C + e_max
	
	if ( E(node_i) == battery.C )
	{
		return TRUE;
	}
	return FALSE;
}

// 3)

// this is only done for one CPU / node. as the tasks cannot be moved
// after they have been assigned to a node, we only have to look at the
// task assigned to the node.

// NOTE for hetero:
// if we change the system to a hetero one, we don't have to check for
// any arch stuff here. the prgs have been assigned to a big, small, or
// whatever node and so we only have to check one again.

// find the min of all SE_tau

// SE	 -> one node, every task deadline
// SE_tau -> one node, specific task deadline

unsigned int SE( int node_i )
{
	#ifdef DBG_SE
		
		print_str( "\nSE for n" ); print_dec( node_i ); 
	#endif
	
	unsigned int smallest_SE_tau = MAX;
	unsigned int smallest_SE_tau_new = MAX;
	
	int i;
	int j;
	int prg_i = 0;
	
	unsigned int d = 0;
	
	// determine interval where assigned prgs are located
	// -----------------------------------------------------------------
	
	// we find the prgs assigned to the node like this:
	
	// start: nodes[ j ].prgs_start_i
	// end:   nodes[ j+1 ].prgs_start_i, or the end of the array if we
	//		are working with the last node.
	
	unsigned int end = ( LAST_NODE(node_i) ) ? NUM_PRGS : nodes[ node_i+1 ].prgs_start_i;
	
	// we iterate over all the programs that are assigned to the node.
	
	#ifdef DBG_SE
		print_str( "\nrange: " );
		print_dec( nodes[ node_i ].prgs_start_i ); print_str( " - " ); print_dec( end );
	#endif
	
	// iterating all the prgs assigned to the node
	// -----------------------------------------------------------------
	
	for ( i = nodes[ node_i ].prgs_start_i; i < end; i++ )
	{
		prg_i = prgs_list[ i ];
		d = 0;
		
		// iterating over all instances of a prg that fit into the time
		// until the clairvoyance ends.
		
		#ifdef DBG_SE
			NL;
			print_str( "\nin SE for p" ); print_dec( prg_i ); 
			print_str( "\nchecking clairvoyance: " ); print_dec( energy_harvester.clairvoyance ); 
		#endif
		
		unsigned int instances = energy_harvester.clairvoyance / prgs[ prg_i ].t_clk_cnt[ 0 ];
		
		#ifdef DBG_SE
			print_str( "\ncovering instances: " ); print_dec( instances ); 
			print_str( "\nhaving a period of: " ); print_dec( prgs[ prg_i ].t_clk_cnt[ 0 ] );
		#endif
		
		for ( j = 0; j < instances; j++ )
		{
			d += prgs[ prg_i ].t_clk_cnt[ 0 ];
			
			#ifdef DBG_SE
				print_str( "\nchecking instance: " ); print_dec( j ); 
				print_str( "\nuntil it's deadline: " ); print_dec( d );
			#endif
			
			smallest_SE_tau_new = SE_tau( node_i, prgs_list[ i ], d );
			
			#ifdef DBG_SE
				
				print_str( "\n=> back in SE\n" );
				print_str( "\nsmalles_SE_tau_new: " ); print_dec( smallest_SE_tau_new );
			#endif
			
			if ( smallest_SE_tau_new < smallest_SE_tau )
			{
				#ifdef DBG_SE
					print_str( "\nnew SE tau is smaller" ); 
					print_str( "\nold SE tau was: " ); print_dec( smallest_SE_tau );
				#endif
				
				smallest_SE_tau = smallest_SE_tau_new;
			}
		}
		
		#ifdef DBG_SE
			
			print_str( "\nfinished checking instances of p" ); print_dec( prg_i ); 
		#endif
		
	}
	
	return smallest_SE_tau;
}

unsigned int ST( int node_i )
{
	#ifdef DBG_ST
		
		print_str( "\nrunning ST for n" ); print_dec( node_i );
	#endif
	
	unsigned int smallest_ST_tau = MAX;
	unsigned int smallest_ST_tau_new = MAX;
	
	int i;
	int j;
	int prg_i = 0;
	
	unsigned int d = 0;

	// determine interval where assigned prgs are located
	// -----------------------------------------------------------------
	
	// we find the prgs assigned to the node like this:
	
	// start: nodes[ j ].prgs_start_i
	// end:   nodes[ j+1 ].prgs_start_i, or the end of the array if we
	//		are working with the last node.
	
	unsigned int end = ( LAST_NODE(node_i) ) ? NUM_PRGS : nodes[ node_i+1 ].prgs_start_i;
	
	// iterating all the prgs assigned to the node
	// -----------------------------------------------------------------
	
	#ifdef DBG_ST
		print_str( "\nrange: " );
		print_dec( nodes[ node_i ].prgs_start_i ); print_str( " - " ); print_dec( end );
	#endif
	
	for ( i = nodes[ node_i ].prgs_start_i; i < end; i++ )
	{
		prg_i = prgs_list[ i ];
		d = 0;

		#ifdef DBG_ST
			
			print_str( "\nin ST for p" ); print_dec( prg_i ); 
			print_str( "\nchecking clairvoyance: " ); print_dec( energy_harvester.clairvoyance ); 
		#endif

		unsigned int instances = energy_harvester.clairvoyance / prgs[ prg_i ].t_clk_cnt[ 0 ];

		#ifdef DBG_ST
			print_str( "\ncovering instances: " ); print_dec( instances ); 
			print_str( "\nhaving a period of: " ); print_dec( prgs[ prg_i ].t_clk_cnt[ 0 ] );
		#endif

		for ( j = 0; j < instances; j++ )
		{
			d += prgs[ prg_i ].t_clk_cnt[ 0 ];
			
			#ifdef DBG_ST
				print_str( "\nchecking instance: " ); print_dec( j ); 
				print_str( "\nuntil it's deadline: " ); print_dec( d );
			#endif
			
			smallest_ST_tau_new = ST_tau( node_i, prgs_list[ i ], d );
			
			#ifdef DBG_ST
				
				print_str( "\n=> back in ST\n" );
				print_str( "\nsmalles_ST_tau_new: " ); print_dec( smallest_ST_tau_new );
			#endif
			
			if ( smallest_ST_tau_new < smallest_ST_tau )
			{
				#ifdef DBG_ST
					print_str( "\nnew ST tau is smaller" ); 
					print_str( "\nold ST tau was: " ); print_dec( smallest_ST_tau ); 
				#endif
				
				smallest_ST_tau = smallest_ST_tau_new;
			}
		}

		#ifdef DBG_ST
			
			print_str( "\nfinished checking instances of p" ); print_dec( prg_i );
		#endif
		
	}
	
	return smallest_ST_tau;
}

// SE_taui( t ) = E(t) + Es( t, di ) - g( t, di )

// slack energy of tau_i at time t.
// wir betrachten hier also einen task. in diesem fall haben wir eine
// bestimmte deadline von dem task. das muss jedoch nicht nur fuer die
// naechste deadline ausgefuehrt werden, sondern fuer alle in der
// zukunft bzw. fuer alle deadlines die in der clairvoyance liegen.
// also sowas wie di * n | 0 < n && di * n <= clairvoyance.

// SE_tau is used to get the energy that will be available at a time di.
// these times will always correspond to task deadlines.

unsigned int SE_tau( int node_i, int prg_i, unsigned int d )
{
	#ifdef DBG_SE_TAU
		
		print_str("\n# SE_tau\n");
		
		
		print_str( "SE_tau for p" ); print_dec( prg_i );
	#endif
	
	unsigned int SE_tau;
	unsigned int temp;
	
	SE_tau = E( node_i );
	
	#ifdef DBG_SE_TAU
		print_str("\nSE_tau = E: ");print_dec(SE_tau);
	#endif
	
	temp = SE_tau;
	//~ SE_tau += Es( prgs[ prg_i ].t_clk_cnt[0] );
	SE_tau += Es( d );
	
	if ( SE_tau < temp ) // overflow
	{
		#ifdef DBG_SE_TAU
			print_str( "\nSE_tau got overflow\n" );
		#endif

		SE_tau = MAX;
	}
	
	#ifdef DBG_SE_TAU
		print_str("\nSE_tau += Es: ");print_dec(SE_tau);
	#endif
	
	temp = SE_tau;
	SE_tau -= g( node_i, prg_i, d );
	
	if ( SE_tau > temp ) // underflow
	{
		#ifdef DBG_SE_TAU
			print_str( "\nSE_tau got underflow\n" );
		#endif

		SE_tau = 0;
	}
	
	#ifdef DBG_SE_TAU
		print_str("\nSE_tau -= g: ");print_dec(SE_tau);
	#endif
	
	return SE_tau;
}

// ST_taui( t ) = di - t - h( t, di )
// ST_taui( t ) = time_to_deadline - time_busy

// di: deadline
// t: current time
// h(): time unavailable

unsigned int ST_tau( int node_i, int prg_i, unsigned int d )
{
	#ifdef DBG_ST_TAU
		
		print_str("\n# ST_tau\n");
		
		
		print_str( "\nST_tau for p" ); print_dec( prg_i ); 
	#endif
	
	unsigned int ST_tau;
	unsigned int temp;
	
	ST_tau = d;
	//ST_tau = time_get_cnt_until( prgs[ prg_i ].next_deadline_clk_cnt, prgs[ prg_i ].next_deadline_overflows );
	
	#ifdef DBG_ST_TAU
		print_str("\nST_tau = T: ");print_dec(ST_tau);
	#endif

	temp = ST_tau;
	ST_tau -= h( node_i, d );
	
	if ( ST_tau > temp ) // underflow
	{
		#ifdef DBG_ST_TAU
			print_str( "\nST_tau got underflow\n" );
		#endif
		
		ST_tau = 0;
	}
	
	return ST_tau;
}

// the charges that are going to occure are not dependent on the node!

// Es is not dependent on the clk cnt. we know the number of clk cnts
// needed to reach the deadline and the number of charges in that
// period. charges are not applied each clk cycles, so getting the
// number of charges that are applied over a clk cnt overflow is not
// that hard.

unsigned int Es( unsigned int di ) // OK
{
	#ifdef DBG_ES
		
		print_str("\n## ES\n");
		
	#endif
	
	// we know the index of the last charge. this can be considered the
	// charge of the current time t.
	// as we know the number of clk cycles needed between each charge
	// we can use the deadline d to calculate how many charges are going
	// to be done until the deadline. then we can add all those charges
	// and get the charges until the deadline.
	
	unsigned int Es = 0;
	
	// number of charges = deadline / interval
	
	unsigned int num_of_charges = di / energy_harvester.interval_cnt;
	
	#ifdef DBG_ES
		print_str("num_of_charges: ");print_dec(num_of_charges);NL;
		print_str("based on di: ");print_dec(di);NL;
		print_str("and interval: ");print_dec(energy_harvester.interval_cnt);NL;
	#endif
	
	// iterate over the charges done before the deadline.
	// the index of the next charge is energy_harvester.charge_i.
	
	unsigned int i;
	
	for ( i = 0; i < num_of_charges; i++ )
	{
		Es += charges[ energy_harvester.charge_i+i ];
		//~ Es += 100000;
	}
	
	#ifdef DBG_ES
		print_str("ES: ");print_dec(Es);NL;
		NL;
		print_str("## ES - end\n");
		NL;
	#endif
	
	return Es;
}

// with g we look at all the tasks that have their release time as well
// as their deadline within t (the current time) and d.
// t <= r_k, d_k <= d
// as the deadline is the same as the period, the release time is
// is right after the deadline.

// d is the relative deadline of the task for which g is determined.

unsigned int g( int node_i, int prg_i_tau, unsigned int d )
{
	#ifdef DBG_G
		NL;
		print_str("## g\n");
		NL;
	#endif
	
	//~ unsigned int d = prgs[ prg_i_tau ].t_clk_cnt[0];
	
	#ifdef DBG_G
		print_str( "getting g for deadline: " ); print_dec( d ); NL;
	#endif
	
	int i;
	int prg_i = 0;
	unsigned int executions = 0;
	unsigned int g = 0;
	
	unsigned int end = ( LAST_NODE(node_i) ) ? NUM_PRGS : nodes[ node_i+1 ].prgs_start_i;
	
	#ifdef DBG_G
		print_str( "range: " );
		print_dec( nodes[ node_i ].prgs_start_i ); print_str( " - " ); print_dec( end ); NL;
	#endif
	
	// iterating all the prgs assigned to the node
	// -----------------------------------------------------------------
	
	for ( i = nodes[ node_i ].prgs_start_i; i < end; i++ )
	{
		prg_i = prgs_list[ i ];
		
		// figure out how many times the task can be executed during
		// the period defined by d.
		
		#ifdef DBG_G
			print_str( "looking at p" ); print_dec( prg_i ); NL;
			print_str( "having period t of: " ); print_dec( prgs[ prg_i ].t_clk_cnt[ 0 ] ); NL;
		#endif
		
		// any prg with a period that is larger than the peropd of the
		// prg to be run can be ignored.
		
		// .t_clk_cnt is the period
		
		if ( prgs[ prg_i ].t_clk_cnt[ 0 ] <= d )
		{
			executions = d / prgs[ prg_i ].t_clk_cnt[ 0 ];
			
			g += ( executions * prgs[ prg_i ].e[ nodes[node_i].arch ] );
			
			#ifdef DBG_G
				print_str( "possible executions: " ); print_dec( executions ); NL;
				print_str( "considering di: " ); print_dec( d ); NL;
				print_str( "and the prg's period: "); print_dec( prgs[ prg_i ].t_clk_cnt[ 0 ] ); NL;
				print_str( "g is now: " ); print_dec( g ); NL;
				print_str( "considering e of: " ); print_dec( prgs[ prg_i ].e[ nodes[node_i].arch ] ); NL;
			#endif
		}
		else
		{
			#ifdef DBG_G
				print_str( "t_clk_cnt is greater than d\n" );
				print_str( "-> ignoring\n" );
			#endif
		}
	}
	
	#ifdef DBG_G
		NL;
		print_str("## g - end\n");
		NL;
	#endif
	
	return g;
}

unsigned int h( int node_i, unsigned int d )
{
	#ifdef DBG_H
		print_str( "getting h for period: " ); print_dec( d ); NL;
	#endif
	
	int i;
	int prg_i = 0;
	unsigned int executions = 0;
	unsigned int h = 0;
	
	unsigned int end = ( LAST_NODE(node_i) ) ? NUM_PRGS : nodes[ node_i+1 ].prgs_start_i;
	
	#ifdef DBG_H
		print_str( "range: " ); NL;
		print_dec( nodes[ node_i ].prgs_start_i ); print_str( " - " ); print_dec( end ); NL;
	#endif
	
	// iterating all the prgs assigned to the node
	// -----------------------------------------------------------------
	
	for ( i = nodes[ node_i ].prgs_start_i; i < end; i++ )
	{
		prg_i = prgs_list[ i ];
		
		// figure out how many times the task can be executed during
		// the period defined by d.
		
		#ifdef DBG_H
			print_str( "looking at p" ); print_dec( prg_i ); NL;
			print_str( "having period t of: " ); print_dec( prgs[ prg_i ].t_clk_cnt[ 0 ] ); NL;
			// print_str("prg_i in h function is: ");print_dec(prg_i);NL;
		#endif
					// while(1){
						print_str("prg_i: ");print_dec(prg_i);NL;
						print_str("prgs[ prg_i ].t_clk_cnt[0]: ");print_dec(prgs[ prg_i ].t_clk_cnt[0]);NL;
						// print_str("prg_i in h function is: ");print_dec(prgs[ prg_i ].t_clk_cnt[0]);NL;

					// }
		if ( prgs[ prg_i ].t_clk_cnt[0] <= d )
		{

			#ifdef DBG_H
				print_str( "t_clk_cnt is smaller than d" ); NL;
			#endif
			
			// the number of times the prg can be executed in the time span
			executions = d / prgs[ prg_i ].t_clk_cnt[ 0 ];
			// yes, it is c, the worst-case execution time.
			// that is how the function is defined in the papers.
			h += ( executions * prgs[ prg_i ].c[ nodes[node_i].arch ] );
			
			#ifdef DBG_H
				print_str( "possible executions: " ); print_dec( executions ); NL;
				print_str( "considering di: " ); print_dec( d ); NL;
				print_str( "and the prg's period: "); print_dec( prgs[ prg_i ].t_clk_cnt[ 0 ] ); NL;
				print_str( "h is now: " ); print_dec( h ); NL;
				print_str( "considering c of: " ); print_dec( prgs[ prg_i ].c[ nodes[node_i].arch ] ); NL;
			#endif
		}
		else
		{
			#ifdef DBG_H
				print_str( "t_clk_cnt is greater than d\n" );
				print_str( "-> ignoring\n" );
			#endif
		}
	}
	
	#ifdef DBG_H
		NL;
		print_str("## h - end\n");
		NL;
	#endif
	
	return h;
}
