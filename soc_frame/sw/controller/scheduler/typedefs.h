
// good info about typedefs:
// https://stackoverflow.com/a/23660072
#ifndef TYPEDEF_H
#define TYPEDEF_H
#include "NAP.h"
#include "mpsoc.h"
typedef struct {
    
    char* name;
    
    // the entry point for the prg. as the system might have nodes of
    // different architectures there needs to be an entry point for each
    // compiled version.
    
    int   addr [ NUM_ARCHS ];
    
    // like the addr, there needs to be timing estimations and so on for
    // each architecture that the system has.
    
    unsigned int   c [ NUM_ARCHS ]; // worst-case execution time
    unsigned int   d [ NUM_ARCHS ]; // relative deadline
    unsigned int   t [ NUM_ARCHS ]; // period
    unsigned int   e [ NUM_ARCHS ]; // worst-case energy consumption
    
    unsigned int   c_clk_cnt [ NUM_ARCHS ]; // c in clk cnts
    unsigned int   t_clk_cnt [ NUM_ARCHS ]; // t in clk cnts
    
    unsigned int   d_multiplyer;
    
    // after skipping a task instance at least s-1 instances must meet
    // their deadline.
    
    unsigned int   s;          // skip parameter/factor
    unsigned int   s_cnt_down; // count down to the next allowed skip
    
    // next deadline in absolute time (as clk_cnt)
    
    unsigned int   next_release_clk_cnt;
    unsigned int   next_release_overflows;
    
    unsigned int   next_deadline_clk_cnt;
    unsigned int   next_deadline_overflows;
    
    // the node the prg is assigned to. this corresponds to the index in
    // the nodes array.
    
    unsigned int   assigned_to;
    
} prg_t;

typedef struct {
    
    int id;
    int arch;
    int id_flag;
    int addr_assign;
    int cnt;
    int prg;                   // the prg that is assigned to the node
    unsigned int charge;
    int mem_address_assigned;
    unsigned int prgs_start_i; // the index in the prg array where the prgs for this node start
    
} node_t;

typedef struct {
    
    unsigned int node_mask;
    unsigned int power;
    
} arch_t;

typedef struct {
    
    unsigned int  cnt;
    unsigned char event;
    
} queue_t;

typedef struct {
    
    unsigned int cnt;
    unsigned int overflows;
    
} cnt_t;

typedef struct {
    
    cnt_t cnt;
    unsigned int interval_cnt;
    
} interval_t;

typedef struct {
    
    unsigned int e_max;
    unsigned int prgs_active;
    
} task_set_t;

typedef struct {
    
    unsigned int C;
    
} battery_t;

typedef struct {
    
    unsigned int Pr;                // worst-case charging rate
    unsigned int charge_i;          // index of the next charge
	cnt_t next_charge_cnt;
    unsigned int interval_cnt;      // number of clk cnts between charges
    unsigned int clairvoyance;      // clk cnts the system knowns into the
                                    // future. should not be number of
                                    // charges as we are using it in regards
                                    // to task deadlines.
    
} energy_harvester_t;

#endif