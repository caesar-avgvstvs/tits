#ifndef _TITS_CORE_H_
#define _TITS_CORE_H_

/* Register Read & Write routines */
void read32(volatile u32* addr, u32 offset, u32* val);
void write32(volatile u32* addr, u32 offset, u32 val);
void writeAnd32(volatile u32* addr, u32 offset, u32 val);
void writeOr32(volatile u32* addr, u32 offset, u32 val);

status_t sysInit();

#endif
