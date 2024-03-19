/* This file has been automatically generated */

#define NUM_PRGS ( 1 )

void init_prgs( prg_t *prgs )
{
	prgs[0].name = "fpmul";
	prgs[0].addr[ARCH_RV32IM] = 0x1fff0; // index: 32764 size: 4040
	prgs[0].exec_t[ARCH_RV32IM] = 0;
	prgs[0].exec_inv[ARCH_RV32IM] = 0;
	prgs[0].exec_e[ARCH_RV32IM] = 0;
	prgs[0].skip_after    = 5;
	prgs[0].skip_cnt_down = 5;
	prgs[0].overflows = 0;

}
