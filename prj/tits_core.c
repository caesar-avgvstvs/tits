#include <tits_core.h>

/* Reset & Clock Control Subsystem */
#define RCC_BASE					0x40021000
#define RCC_CTLR					0x0
#define RCC_CFGR0					0x4
#define RCC_INTR					0x8

void read32(volatile u32* addr, u32 offset, u32* val)
{
	*val = *(addr + offset);
}

void write32(volatile u32* addr, u32 offset, u32 val)
{
	*(addr + offset) = val;
}

void writeAnd32(volatile u32* addr, u32 offset, u32 val)
{
	u32 prev;
	read32(addr, offset, &prev);
	write32(addr, offset, prev & val);
}

void writeOr32(volatile u32* addr, u32 offset, u32 val)
{
	u32 prev;
	read32(addr, offset, &prev);
	write32(addr, offset, prev | val);
}

status_t sysInit()
{
	/* Reset RCC_CFGR0, RCC_INTR & RCC_CTLR */
	/* Turn on HSI & Disable HSE & PLL */
	writeOr32(RCC_BASE, RCC_CTLR, 0x01);
	writeAnd32(RCC_BASE, RCC_CFGR0, 0xf8ff0000);
	writeAnd32(RCC_BASE, RCC_CTLR, 0xfef6ffff);
	writeAnd32(RCC_BASE, RCC_CTLR, 0xfffbffff);
	writeAnd32(RCC_BASE, RCC_CFGR0, 0xff80ffff);
	write32(RCC_BASE, RCC_INTR, 0x009f0000);

	/* Set system clock to the preferred configuration */
	setSysClock();
}

status_t setSysClock()
{
	
}
