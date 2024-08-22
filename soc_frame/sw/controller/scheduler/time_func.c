
#include "time_func.h"

void time_update_global()
{
	unsigned int tmp = cnt_global.cnt;
	
	cnt_global.cnt = GET_COUNTER_GLOBAL;
	
	if ( tmp > cnt_global.cnt )
	{
		cnt_global.overflows += 1;
	}
}

void time_advance( cnt_t* cnt, unsigned int time )
{
	unsigned int cnt_tmp;
	
	cnt_tmp = (*cnt).cnt;
	
	(*cnt).cnt += time;
	
	if ( (*cnt).cnt <= cnt_tmp )
	{
		(*cnt).overflows += 1;
	}
}

int time_reached_cnt_t( cnt_t* cnt )
{
	return time_reached( (*cnt).cnt, (*cnt).overflows );
}
int time_reached( unsigned int cnt, unsigned int overflows )
{
    // if: same overflows -> check cnt
    // elif: more overflows global -> surely reached
    
    if ( cnt_global.overflows == overflows )
    {
        if ( cnt_global.cnt >= cnt )
        {
            return TRUE;
        }
    }
    else if ( cnt_global.overflows >= overflows )
    {
        return TRUE;
    }
    
    return FALSE;
}



unsigned int time_get_cnt_until( unsigned int cnt, unsigned int overflows )
{
    if ( cnt_global.overflows < overflows )
    {
        return ( (MAX-cnt_global.cnt) + cnt );
    }
    else
    {
        return ( cnt - cnt_global.cnt );
    }
}
