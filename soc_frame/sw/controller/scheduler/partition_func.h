#ifndef PARTITION_FUNC_H
#define PARTITION_FUNC_H
//----------------------------------------------------------------------
// 
// partition_eh_ra
// 
//----------------------------------------------------------------------

// returns -1 if partition is not successful
#include "globals.h"
#include "nodes_func.h"
int partition_eh_ra();
// report partition
//----------------------------------------------------------------------

#ifdef REP_PARTITION_EH_RA
    
    void rep_partition();
#endif

//----------------------------------------------------------------------
// 
// create task array
// 
//----------------------------------------------------------------------

void create_task_array();
// report prgs list
//----------------------------------------------------------------------

#ifdef REP_PRGS_LIST
    
    void rep_prgs_list();
    
#endif
#endif