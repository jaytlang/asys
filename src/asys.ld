OUTPUT_ARCH( "riscv" )
ENTRY ( _start )

SECTIONS {
	. = 0x80000000;

	.text : {
		*(.text.init)
		*(.text .text.startup)
		. = ALIGN(0x1000);

		PROVIDE(startps = .);
		*(.text.ps)
		. = ALIGN(0x1000);
		PROVIDE(endps = .);

		_kernjump = .;
		*(.text.utrap)
		. = ALIGN(0x1000);
		ASSERT(. - _kernjump == 0x1000, "utrap is too thicc");
		PROVIDE(etext = .);
	}

	.rodata : {
		. = ALIGN(16);
		*(.srodata .srodata.*)
		. = ALIGN(16);
		*(.rodata .rodata.*)
	}

	.data : {
		. = ALIGN(16);
		*(.sdata .sdata.*)
		. = ALIGN(16);
		*(.data .data.*)
	}

	.bss : {
		. = ALIGN(16);
		*(.sbss .sbss.*)
		. = ALIGN(16);
		*(.bss .bss.*)
	}

	PROVIDE(ekernel = .);
}
	

