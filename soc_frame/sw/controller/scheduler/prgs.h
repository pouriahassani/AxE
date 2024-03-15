/* This file has been automatically generated */

#define NUM_PRGS ( 1 )

void init_prgs( prg_t *prgs )
{
	prgs[0].name = "cmul";
	prgs[0].addr[ARCH_RV32I] = 0x7ffc; // index: 8191 size: 309
	prgs[0].skip_after    = 5;
	prgs[0].skip_cnt_down = 5;
	prgs[0].overflows = 0;

	prgs[1].name = "sobel";
	prgs[1].addr[ARCH_RV32IM] = 0x84f0; // index: 8508 size: 66883
	prgs[1].exec_t[ARCH_RV32IM] = 0;
	prgs[1].exec_inv[ARCH_RV32IM] = 0;
	prgs[1].exec_e[ARCH_RV32IM] = 0;
	prgs[1].skip_after    = 5;
	prgs[1].skip_cnt_down = 5;
	prgs[1].overflows = 0;

}
