OUTPUT_ARCH( "riscv" )
MEMORY
{
    ram (rx) : ORIGIN = 0x10000, LENGTH = 0x10000
}
SECTIONS
{
    . = 0x10000; /* Start address */
    .text : { *(.text) } > ram
    .data : { *(.data) } > ram
    /* Define other sections as needed */
}

