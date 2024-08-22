#ifndef TIME_FUNC_H
#define TIME_FUNC_H
#include "typedefs.h"
#include "globals.h"
void time_update_global();
void time_advance( cnt_t* cnt, unsigned int time );
int time_reached_cnt_t( cnt_t* cnt );
int time_reached( unsigned int cnt, unsigned int overflows );
unsigned int time_get_cnt_until( unsigned int cnt, unsigned int overflows );

#endif