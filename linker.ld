/* Link.ld -- Linker script for the kernel - ensure everything goes in the */
/*            Correct place.  */
/*            Original file taken from Bran's Kernel Development */
/*            tutorials: http://www.osdever.net/bkerndev/index.php. */

ENTRY(start)
SECTIONS
{
    . = 0x00100000;
    .text :
    {
        *(.text)
        . = ALIGN(4096);
    }

    .data :
    {
        *(.data)
        . = ALIGN(4096);
        *(.rodata*)
        . = ALIGN(4096);
    }

    .bss :
    {
        *(COMMON)
        *(.bss)
        . = ALIGN(4096);
    }

    end = .; _end = .; __end = .;
}
