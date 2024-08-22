#ifndef GLOBALS_H
#define GLOBALS_H
// TODO - try to minimize as much as possible
#include "defines.h"
#include "typedefs.h"
#include "debug.h"
#include "controller.h"

#include "./../../_libs/fixed_point.h"
#include "./../../_libs/print.h"
#include "./../../_libs/util.h"
#include "NAP.h"
#include "mpsoc.h"
extern node_t nodes[ NUM_NODES ];
extern prg_t prgs[ NUM_PRGS ];
extern arch_t archs[ NUM_ARCHS ];
extern queue_t queue[ 100 ];

extern int prgs_list[ NUM_PRGS ];
extern int ready_list[ NUM_PRGS ]; // could be encoded into the prgs_list

extern task_set_t task_set;
extern battery_t battery;
extern energy_harvester_t energy_harvester;
extern cnt_t cnt_global;

extern int charges[ NUM_CHARGES ];
extern unsigned int charges_i;

extern int queue_index;

extern unsigned int cnt_prev;
extern unsigned int cnt;

extern int save_mode;

extern int nodes_busy;

extern int prgs_active;

extern int leds_status;

extern int preferred_archs[ NUM_ARCHS ];
#endif