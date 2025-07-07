	.section	.init,"ax",@progbits
	.global		_start
	.align		1
_start:
	j	handle_reset

	.section	.vector,"ax",@progbits
	.align		1
_vector_base:
	.option norvc
	.word _start
	.word 0
	.word NMIHandler
	.word hardFaultHandler
	.word 0
	.word ecallMModeHandler
	.word 0
	.word 0
	.word ecallUModeHandler
	.word breakPointHandler
	.word 0
	.word 0
	.word sysTickHandler
	.word 0
	.word SWHandler
	.word 0
	/* External Interrupts (Defined in the CH32V203 manual) */
 /* Not gonna handle any of the external interrupts as of now */

 .option rvc
 .section .vector_handler, "ax",@progbits
