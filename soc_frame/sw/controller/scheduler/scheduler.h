#ifndef SHCEDULER_H
#define SHCEDULER_H
#include "globals.h"
#include "nodes_func.h"
#define BE_IDLE ( -1 )
int get_prg_apply_edh_rules( int );
int L_r_empty( int );
int get_prg_i_via_edf( int );

unsigned int E( int );
int E_is_empty( int );
int is_empty( unsigned int );
int E_is_full( int );

unsigned int SE( int );
unsigned int ST( int );

unsigned int SE_tau( int, int, unsigned int );
unsigned int ST_tau( int, int, unsigned int );

unsigned int Es( unsigned int );

unsigned int g( int, int, unsigned int );
unsigned int h( int, unsigned int );

#endif