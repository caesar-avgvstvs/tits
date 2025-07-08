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
	.section .text.vector_handler, "ax",@progbits
	.weak NMIHandler
	.weak hardFaultHandler
	.weak ecallMModeHandler
	.weak ecallUModeHandler
	.weak breakPointHandler
	.weak sysTickHandler
	.weak SWHandler

NMIHandler:
hardFaultHandler:
ecallMModeHandler:
ecallUModeHandler:
breakPointHandler:
sysTickHandler:
SWHandler:
1:
	j 1b


	.section .text.handler_reset,"ax", @progbits
	.weak handle_reset
	.align 1
handle_reset:
	.option push
	.option norelax
	la gp, __global_pointer$
	.option pop
1:
	la sp, _eusrstack
2:
	la a0, _data_lma
	la a1, _data_vma
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
