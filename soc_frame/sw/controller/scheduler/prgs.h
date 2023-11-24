/* This file has been automatically generated */

#define NUM_PRGS ( 3 )

void init_prgs( prg_t *prgs )
{
	prgs[0].name = "mul_500_nop_500";
	prgs[0].addr[ARCH_RV32I] = 0x7ffc; // index: 8191 size: 1348
	prgs[0].addr[ARCH_RV32IM] = 0x9530; // index: 9548 size: 1284
	prgs[0].exec_t[ARCH_RV32I] = 0;
	prgs[0].exec_t[ARCH_RV32IM] = 0;
	prgs[0].exec_inv[ARCH_RV32I] = 0;
	prgs[0].exec_inv[ARCH_RV32IM] = 0;
	prgs[0].exec_e[ARCH_RV32I] = 0;
	prgs[0].exec_e[ARCH_RV32IM] = 0;
	prgs[0].skip_after    = 5;
	prgs[0].skip_cnt_down = 5;
	prgs[0].overflows = 0;

	prgs[1].name = "mul_500_nop_501";
	prgs[1].addr[ARCH_RV32I] = 0xa964; // index: 10841 size: 1348
	prgs[1].addr[ARCH_RV32IM] = 0xbe98; // index: 12198 size: 1284
	prgs[1].exec_t[ARCH_RV32I] = 0;
	prgs[1].exec_t[ARCH_RV32IM] = 0;
	prgs[1].exec_inv[ARCH_RV32I] = 0;
	prgs[1].exec_inv[ARCH_RV32IM] = 0;
	prgs[1].exec_e[ARCH_RV32I] = 0;
	prgs[1].exec_e[ARCH_RV32IM] = 0;
	prgs[1].skip_after    = 5;
	prgs[1].skip_cnt_down = 5;
	prgs[1].overflows = 0;

	prgs[2].name = "mul_500_nop_502";
	prgs[2].addr[ARCH_RV32I] = 0xd2cc; // index: 13491 size: 1348
	prgs[2].addr[ARCH_RV32IM] = 0xe800; // index: 14848 size: 1284
	prgs[2].exec_t[ARCH_RV32I] = 0;
	prgs[2].exec_t[ARCH_RV32IM] = 0;
	prgs[2].exec_inv[ARCH_RV32I] = 0;
	prgs[2].exec_inv[ARCH_RV32IM] = 0;
	prgs[2].exec_e[ARCH_RV32I] = 0;
	prgs[2].exec_e[ARCH_RV32IM] = 0;
	prgs[2].skip_after    = 5;
	prgs[2].skip_cnt_down = 5;
	prgs[2].overflows = 0;

}
