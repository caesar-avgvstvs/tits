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
 /* Setup the source and destination addresses of the binary */
	la a0, _data_lma
	la a1, _data_vma
	la a2, _edata
	bgeu a1, a2, 2f
 /* Copy the binary from src to dst 4bytes a time */
1:
	lw t0, (a0)
 sw t0, (a1)
 addi a0, a0, 4
 addi a1, a1, 4
 bltu a1, a2, 1b

2:
 /* Clear the BSS section after loading the binary */
 la a0, _sbss
 la a1, _ebss
 bgeu a0, a1, 2f

1:
 sw zero, (a0)
 addi a0, a0, 4
 bltu a0, a1, 1b


2:

/* Configure instruction pipelining & prediction */
 li t0, 0x1f
 csrw, 0xbc0, t0

/* Enable Interrupt nesting and hardware stack */
 li t0, 0x3
 csrw 0x804, t0

/* Enable global interrupts and configure privileged mode */
 li t0, 0x88
 csrw mstatus, t0

/* Configure the interrupt vector table recognition mode & entry address mode */
 li t0, _vector_base
 ori t0, t0, 3
 csrw mtvec, t0

/* Jump to the kernel's systemInit() routine */
 jal titsSysInit

/* Jump to the kernel */
 la t0, main
 csrw mepc, t0
 mret
