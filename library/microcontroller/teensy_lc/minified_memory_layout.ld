/* Basic Memory Description */
MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 64K /* unser chip hat 64K speicher */
	RAM  (rwx) : ORIGIN = 0x1FFFF800, LENGTH = 8K
}

/* The original Linker script contained an entry directive.
   I don't believe it to be nessesary, as the entry point is
   an intrinsic behaviour of the chip. */
/* ENTRY(_VectorsTable) */

/* TODO rest */
SECTIONS
{
	.text : {
	      . = 0;
	      KEEP(*(.vectors))
	      *(.startup*)
	      . = 0x400;
	      KEEP(*(.flashconfig*))
	      *(.text*)
	      *(.rodata*)
	      /* I removed the next sections as I won't have a main function.
                 They all relate to standart c environments, which I don't have. */
	} > FLASH = 0xFF

        /DISCARD/ : {
	      *(.init); /* holds code which is called before main */
	      *(.preinit_array)
	      *(.init_array.*)
	      *(.init_array)
	      *(.fini);
	}

	/* I removed the next section as well, as it seems to relate to stack
	   unwinding which I don't intend to use (for now). */
	/* .ARM.exidx : { */
	/* 	   __exidx_start = .; */
	/* 	   *(.ARM.exidx* .gnu.linkonce.armexidx.*) */
	/* 	   __exidx_end = .; */
	/* } > FLASH */
	_text_end = .;

	.data : AT(_text_end) {
	      . = ALIGN(4);
	      _data_start = .;
	      *(.fastrun*)
	      *(.data*)
	      . = ALIGN(4);
	      _data_end = .;
	} > RAM

	/* This are those parts of the object files, which are not to be initialized. 
	   NOLOAD marks this section as not beeing loadable, so i.e. the programmer will
	   leave this section of memory alone. */
	.noinit (NOLOAD) : {
		*(.noinit*)
	} > RAM

	.bss (NOLOAD) : {
	     . = ALIGN(4);
	     _bss_start = .;
	     *(.bss*)
	     *(COMMON) /* Global unitialized variables */
	     . = ALIGN(4);
	     _bss_end = .;
	} > RAM

	/* This statement defines a symbol which points to the last byte in RAM.
	   It is then used as the initial stack pointer in the 0th position of the 
	   Vector Table. */
	_initial_stack = ORIGIN(RAM) + LENGTH(RAM);
}
