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
    .global my_start

my_start:
    
    /* setup stack pointer */
    
    lui sp, %hi(STACK_POINTER)
    addi sp, sp, %lo(STACK_POINTER)
    
    call _start
    
