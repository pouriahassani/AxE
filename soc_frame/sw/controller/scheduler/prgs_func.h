#ifndef PRGS_FUNC_H
#define PRGS_FUNC_H
//------------------------------------------------------------------------------
// 
// estimate execution time
// 
//------------------------------------------------------------------------------

// for every arch, every prg is executed. the selected node has to have the arch
// for which the execution time is estimated.
#include "globals.h"
#include "time_func.h"
#include "nodes_func.h"
void prgs_estimate_execution_times();
    
    
    

    

void prg_estimate_execution_time( int node_i, int prg_i );
void prgs_execution_time_debug();

// generally speaking ms are considered fixed point numbers

int prgs_get_execution_time_in_ms( int clk_cnt );

//------------------------------------------------------------------------------
// 
// prgs_set_relative_deadline
// 
//------------------------------------------------------------------------------

void prgs_set_relative_deadline();
#ifdef DBG_GET_RELATIVE_DEADLINE
    void prgs_get_relative_deadline_debug();
#endif

//------------------------------------------------------------------------------
// 
// prgs_set_period
// 
//------------------------------------------------------------------------------

void prgs_set_period();
void prgs_set_period_clk_cnt();














//------------------------------------------------------------------------------
// 
// estimate energy requirements
// 
//------------------------------------------------------------------------------

void prgs_estimate_energy_requirements();
void estimate_energy_requirement( int arch_i, int prg_i );





void prgs_set_initial_deadlines();

#ifdef REP_INITIAL_DEADLINES
    
void rep_prgs_set_initial_deadlines();
    
    
#endif

void prg_set_next_deadline( int prg_i );

















//------------------------------------------------------------------------------
// 
// prgs_check_if_finished
// 
//------------------------------------------------------------------------------



void prgs_check_if_finished();
//------------------------------------------------------------------------------
// 
// prg_set_inactive
// 
//------------------------------------------------------------------------------

// TODO - only works for 32 or less prgs. maybe not needed anymore.

void prg_set_inactive( int prg_i );
//------------------------------------------------------------------------------
// 
// prg_set_active
// 
//------------------------------------------------------------------------------

void prg_set_active( int prg_i );
//------------------------------------------------------------------------------
// 
// prg_is_running
// 
//------------------------------------------------------------------------------

int prg_is_running( int prg_i );

//------------------------------------------------------------------------------
// 
// prgs_summary
// 
//------------------------------------------------------------------------------
   
void prgs_summary();

void prgs_set_ready( int node_i );

#endif