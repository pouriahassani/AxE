/* This file has been automatically generated */

#define NUM_PRGS ( 2 )

void init_prgs( prg_t *prgs )
{
	prgs[0].name = "msort";
	prgs[0].addr[ARCH_RV32IM] = 0x1fff0; // index: 32764 size: 2338
	prgs[0].exec_t[ARCH_RV32IM] = 0;
	prgs[0].exec_inv[ARCH_RV32IM] = 0;
	prgs[0].exec_e[ARCH_RV32IM] = 0;
	prgs[0].skip_after    = 5;
	prgs[0].skip_cnt_down = 5;
	prgs[0].overflows = 0;

	prgs[1].name = "qsort";
	prgs[1].addr[ARCH_RV32IM] = 0x24608; // index: 37250 size: 2668
	prgs[1].exec_t[ARCH_RV32IM] = 0;
	prgs[1].exec_inv[ARCH_RV32IM] = 0;
	prgs[1].exec_e[ARCH_RV32IM] = 0;
	prgs[1].skip_after    = 5;
	prgs[1].skip_cnt_down = 5;
	prgs[1].overflows = 0;

}
