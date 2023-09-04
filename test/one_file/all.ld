SECTIONS {
    . = 0x80280000;

    .data : {
        *(.data*)
    }

    .rodata : {
        *(.rodata*)
    }

    .text : {
        *(.text*)
    }

    .bss : {
        *(.bss*)
    }

    end = .;
}
