/* This file has been automatically generated */

#include "globals.h"

#include "Node_arch_prgs.h"

void init_prgs( prg_t *prgs )
{
	prgs[0].name = "susan";
	prgs[0].addr[ARCH_RV32IM] = 0x100000; // index: 262144 size: 18752
	prgs[0].c[ARCH_RV32IM] = 0;
	prgs[0].d[ARCH_RV32IM] = 0;
	prgs[0].t[ARCH_RV32IM] = 0;
	prgs[0].e[ARCH_RV32IM] = 0;
	prgs[0].c_clk_cnt[ARCH_RV32IM] = 0;
	prgs[0].t_clk_cnt[ARCH_RV32IM] = 0;
	prgs[0].d_multiplyer = 0b0000001101001001;
	prgs[0].s          = 5;
	prgs[0].s_cnt_down = 5;
	prgs[0].assigned_to = 0;
	prgs[0].next_release_clk_cnt = 0;
	prgs[0].next_release_overflows = 0;
	prgs[0].next_deadline_clk_cnt = 0;
	prgs[0].next_deadline_overflows = 0;

}
