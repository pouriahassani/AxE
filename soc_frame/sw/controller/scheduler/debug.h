
// the defines in this file can be used to enable debug output.
// TODO - this should be moved to the python build system.

// show the negative slack with which a prg is executed again. so how late it is

//~ #define DBG_EXEC_AGAIN_NEG_SLACK

// show the calculations used to determine the next execution with an overflow.
// the result of the intermediate calculations is not used and the actual
// calculation is done without them

//~ #define DBG_EXEC_AGAIN_OVERFLOW_CALC

// check the steps that are taken to decide if a node has finished the execution
// of a prg. this output is also relevant to find out which prgs finished.






//~ #define DBG_NODES_BUSY

//~ #define DBG_NODES_FINISHED

// check the steps taken to find out which prgs are still active.

//~ #define DBG_PRGS_ACTIVE_STEPS

// see which prgs are still set to active.

//~ #define DBG_PRGS_ACTIVE


/// debugging

// charging

//~ #define DBG_CHARGING
//~ #define DBG_DISCHARGING


#define DBG_GET_NODE

// estimations/analysis

#define DBG_ESTIMATE_EXECUTION_TIME
#define DBG_GET_RELATIVE_DEADLINE
//~ #define DBG_PRGS_SUMMERY

// partition

#define DBG_PARTITION_EH_RA
#define DBG_PRGS_LIST_CREATION

// prg func

#define DBG_SET_NEXT_DEADLINE
#define DBG_SET_READY

//~ #define DBG_EVENT_QUEUE

// schedule

#define DBG_SCHEDULER

#define DBG_EDH_RULES
//#define DBG_EDH_L_R
//#define DBG_EDH_EDF
//#define DBG_EDH_E
//#define DBG_SE
//#define DBG_SE_TAU
//#define DBG_ES
//#define DBG_G
#define DBG_ST
#define DBG_ST_TAU
#define DBG_H

// math

#define DBG_MATH_CLAMP

/// report

// for printing things like summaries

#define REP_CHARGING
#define REP_DISCHARGING

#define REP_PRGS_SUMMERY

#define REP_PARTITION_EH_RA
#define REP_PRGS_LIST

#define REP_INITIAL_DEADLINES
