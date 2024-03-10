void init_prgs( prg_t *prgs )
{

prgs[0].name = "mul_loop_0000000F\n";
prgs[0].addr[ARCH_RV32I] = 0x3ffc; // index: 4095 size: 1298
prgs[0].addr[ARCH_RV32IM] = 0x5464; // index: 5401 size: 1234
prgs[0].exec_interval = 0;
prgs[0].exec_again_at = 0;
prgs[0].skip_after    = 5;
prgs[0].skip_cnt_down = 5;

prgs[1].name = "mul_loop_0000004F\n";
prgs[1].addr[ARCH_RV32I] = 0x67cc; // index: 6643 size: 1298
prgs[1].addr[ARCH_RV32IM] = 0x7c34; // index: 7949 size: 1234
prgs[1].exec_interval = 0;
prgs[1].exec_again_at = 0;
prgs[1].skip_after    = 5;
prgs[1].skip_cnt_down = 5;

prgs[2].name = "mul_loop_000000AF\n";
prgs[2].addr[ARCH_RV32I] = 0x8f9c; // index: 9191 size: 1298
prgs[2].addr[ARCH_RV32IM] = 0xa404; // index: 10497 size: 1234
prgs[2].exec_interval = 0;
prgs[2].exec_again_at = 0;
prgs[2].skip_after    = 5;
prgs[2].skip_cnt_down = 5;

prgs[3].name = "mul_loop_000000FF\n";
prgs[3].addr[ARCH_RV32I] = 0xb76c; // index: 11739 size: 1298
prgs[3].addr[ARCH_RV32IM] = 0xcbd4; // index: 13045 size: 1234
prgs[3].exec_interval = 0;
prgs[3].exec_again_at = 0;
prgs[3].skip_after    = 5;
prgs[3].skip_cnt_down = 5;

prgs[4].name = "mul_loop_000004FF\n";
prgs[4].addr[ARCH_RV32I] = 0xdf3c; // index: 14287 size: 1298
prgs[4].addr[ARCH_RV32IM] = 0xf3a4; // index: 15593 size: 1234
prgs[4].exec_interval = 0;
prgs[4].exec_again_at = 0;
prgs[4].skip_after    = 5;
prgs[4].skip_cnt_down = 5;

prgs[5].name = "mul_loop_00000AFF\n";
prgs[5].addr[ARCH_RV32I] = 0x1070c; // index: 16835 size: 1298
prgs[5].addr[ARCH_RV32IM] = 0x11b74; // index: 18141 size: 1234
prgs[5].exec_interval = 0;
prgs[5].exec_again_at = 0;
prgs[5].skip_after    = 5;
prgs[5].skip_cnt_down = 5;

prgs[6].name = "mul_loop_00000FFF\n";
prgs[6].addr[ARCH_RV32I] = 0x12edc; // index: 19383 size: 1298
prgs[6].addr[ARCH_RV32IM] = 0x14344; // index: 20689 size: 1234
prgs[6].exec_interval = 0;
prgs[6].exec_again_at = 0;
prgs[6].skip_after    = 5;
prgs[6].skip_cnt_down = 5;
}
