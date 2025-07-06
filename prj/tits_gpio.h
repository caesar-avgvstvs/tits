#ifndef _TITS_GPIO_H_
#define _TITS_GPIO_H_

typedef struct gpio_port {
	u32 base;
	volatile u32* cfglr;
	volatile u32* cfghr;
	volatile u32* indr;
	volatile u32* outdr;
	volatile u32* bshr;
	volatile u32* bshr;
	volatile u32* bcr;
	volatile u32* lckr;
} gpioPort_t;

status_t gpioInit(u8 port, u8 pin, u8 mode);
status_t gpioWriteBit(u8 port, u8 pin, u8 data);

#endif
