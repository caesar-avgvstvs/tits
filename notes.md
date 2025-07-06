# System Reset
Either the SYSRESET bit in the Interrupt configuration register (PFIC_CFGR) should be set to 1, or the SYSRESET bit in the PFIC_SCTLR register should be set to 1.


# Memory Map

- Flash: 0x0 - 0x2000 0000
    - 0x0 - 0x0800 0000: Aliased to flash or system memory depending on the BOOT pins configuration
    - 0x0800 0000 - undefined: Code Flash (configurable, 224KB max; only 64KB can be accessed with zero wait states)
    - 0x1fff 8000 - 0x1fff f000: System Flash (28KB)
    - Vendor Bytes
    - Option Bytes

- SRAM: 0x2000 0000 - 0x2001 0000 (64KB)

- Peripherals
    - TIM1
    - GPIO
    - SPI
    - USART1

- Core Private Peripherals



# Clock

## Clock Options

* HSI: 8MHz RC oscillator. Startup time is very short but the clock frequency accuracy is very poor. If the HSE crystal oscillator fails, the HSI is used as a backup clock source.
* HSE: An external 3 to 25MHz. More accurate.

## Choosing the System Clock

* The PLL clock will be the clock output, with the HSE as its source.

* **Configuration of the Internal PLL Clock**:
    - 3 clock sources and multiplication factors can be selected by configuring the RCC_CFGR0 & the EXTEND_CTR. These must be configured before the PLL is enabled.
    - The PLL can be enabled by setting PLLON bit in RCC_CTLR. The PLLRDY bit indicated whether the PLL clock is stable. The clock is not released until the PLLRDY bit is set to 1 by the hw.
    - If the PLLRDYIE bit is set in RCC_INTR, a corresponding interrupt is generated.

* **System Clock**: System clock source can be set by configuring the SW[1:0] bits in RCC_CFGR0.
    - Set the HPRE[3:0], PPRE1[2:0], PPRE2[2:0] bits in RCC_CFGR0 to configure the clocks for the HB, PB1 & PB2 buses respectively.
    - Different peripheral modules can be reset by bits in the RCC_AHBRSTR, RCC_APB1PRSTR, RCC_APB2PRSTR registers to restore them to the initial state.
    - By setting bits in the RCC_AHBPCENR, RCC_APB1PCENR and RCC_APB2PCENR registers, the communication clock interface of different peripheral modules can be enabled or disabled. To use a peripheral, firstly enable the corresponding clock bit to access its registers.


UART Driver Pseudocode: Interrupt-driven, no-polling
Only USART4 is going to be used, that too, as UART.
Reset all the registers to their reset values.

1. Set USARTx_BRR
2. Set USARTx_CTLR1
    * [13] UE = 0 to disable USART
    * [12] M = 0 (Word length = 8 bits)
    * [10] PCE = 1 (Parity Control Enable)
    * [9] PS (Even or Odd parity. #FIXME)
    * [6] TCIE = 1 (Transmission Complete Interrupt Enable)
    * [5] RXNEIE = 1 (Receive Buffer Non-Empty Interrupt Enable)
    * [3] TE (Transmitter Enable)
    * [2] RE (Receiver Enable)
3. Set USARTx_CTLR2
    * [13:12]  STOP = 00 (1 stop bit)
    * [11] CLKEN = 0 (Clock disable)
    * [3:0] ADD (#FIXME)
4. Set USARTx_CTLR3
    * [7] DMAT (DMA Transmission Enable) (#FIXME)
    * [6] DMAR (DMA Reception Enable) (#FIXME)
5. USARTx_DATAR
    * [8:0] = DR (Data Register)
