// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// Only save registers in IRQ wrapper that are to be saved by the caller in
// the RISC-V ABI, with the excpetion of the stack pointer. The IRQ handler
// will save the rest if necessary. I.e. skip x3, x4, x8, x9, and x18-x27.

    .section .text
    .global main

/*
reset_vec:
    j start
*/

/* Main program
 **********************************/

main:
    /* zero-initialize all registers */

    addi x1, zero, 0
    
    /*
    addi x2, zero, 0
    addi x3, zero, 0
    addi x4, zero, 0
    */
    
    addi x5, zero, 0
    addi x6, zero, 0
    addi x7, zero, 0
    addi x8, zero, 0
    addi x9, zero, 0
    addi x10, zero, 0
    addi x11, zero, 0
    addi x12, zero, 0
    addi x13, zero, 0
    addi x14, zero, 0
    addi x15, zero, 0
    addi x16, zero, 0
    addi x17, zero, 0
    addi x18, zero, 0
    addi x19, zero, 0
    addi x20, zero, 0
    addi x21, zero, 0
    addi x22, zero, 0
    addi x23, zero, 0
    addi x24, zero, 0
    addi x25, zero, 0
    addi x26, zero, 0
    addi x27, zero, 0
    addi x28, zero, 0
    addi x29, zero, 0
    addi x30, zero, 0
    addi x31, zero, 0
    
    /* setup stack pointer */
    /*
    lui sp, %hi(STACK_POINTER)
    addi sp, sp, %lo(STACK_POINTER)
    */
    
    call my_main
    
    /* trap */
    /* ebreak */
    
    /* signal fin */
    
    /*
    Once the program is finished it signals its completion that is picked up
    by the axi_detector.
    After that it theoretically enteres an endelss loop, but practically the
    CPU should be turned off before the instruction can be read.
    */
    
    lui     a5,0x1000
    addi    a5,a5,-4 # fffffc <__global_pointer$+0xffdf84>
    lui     a4,0x1000
    addi    a4,a4,-4 # fffffc <__global_pointer$+0xffdf84>
    sw      a4,0(a5)

loop:
    j loop
