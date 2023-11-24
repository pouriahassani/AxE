
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




// charging

//~ #define DBG_CHARGING
//~ #define DBG_DISCHARGING


//~ #define DBG_GET_NODE
//~ #define DBG_ESTIMATE_EXECUTION_TIME


//~ #define DBG_EVENT_QUEUE

/// report


#define REP_CHARGING
#define REP_DISCHARGING
