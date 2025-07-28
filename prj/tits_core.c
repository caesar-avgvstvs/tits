#include <tits_core.h>

/* Reset & Clock Control Subsystem */
#define RCC_BASE					0x40021000
#define RCC_CTLR					0x0
#define RCC_CFGR0					0x4
#define RCC_INTR					0x8


/* RCC_CTLR bitfields */
#define RCC_HSERDY   0x00020000


/* RCC Definitions */
#define HSE_STARTUP_TIMEOUT   0x00001000
#define RCC_PLLSRC            0x00010000
#define RCC_PLLXTPRE          0x00020000
#define RCC_PLLMULL           0x003c0000
#define RCC_PLLSRC_HSE        0x00010000
#define RCC_PLLXTPRE_HSE      0x00000000
#define RCC_PLLMULL18         0x003c0000
#define RCC_PLLON             0x01000000
#define RCC_PLLRDY            0x02000000
#define RCC_SW                0x01000000
#define RCC_SW_PLL            0x00000002
#define RCC_SWS               0x0000000c



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
    /* Only supports 144MHz mode for now */
    volatile u32 startup_counter = 0;
    volatile u32 hse_status = 0;
    volatile u32 pll_status = 0;
    do {
        read32(RCC_BASE, RCC_CTLR, &hse_status);
        hse_status &= RCC_HSERDY;
        startup_counter++;
    } while ((hse_status == 0) && (startup_counter != HSE_STARTUP_TIMEOUT));
    read32(RCC_BASE, RCC_CTLR, &hse_status);
    if (hse_status & RCC_HSERDY) {
        writeAnd32(RCC_BASE, RCC_CFGR0, 
                ~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
        writeOr32(RCC_BASE, RCC_CFGR0, 
                RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL18);
        /* Turn on PLL */
        writeOr32(RCC_BASE, RCC_CTLR, RCC_PLLON);
        /* Wait till PLL is ready */
        do {
            read32(RCC_BASE, RCC_CTLR, &pll_status);
        } while ((pll_status & RCC_PLLRDY) != 0);

        /* Select PLL as System Clock source */
        writeAnd32(RCC_BASE, RCC_CFGR0, ~RCC_SW);
        writeOr32(RCC_BASE, RCC_CFGR0, RCC_SW_PLL);
        /* Wait till PLL is used as System Clock source */
        do {
            read32(RCC_BASE, RCC_CFGR0, &sws_status);
        } while ((sws_status & RCC_SWS) != 0x08);
    } else {
    /* TODO Handle case: HSE Doest startup */
    }
}
