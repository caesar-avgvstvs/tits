#include <tits_gpio.h>

#define NUM_GPIO_PORTS					1
#define write32(addr, dat)			*(addr) = (dat)

gpioPort_t gpioPorts[NUM_GPIO_PORTS] = {
	/* PORT A */
	{
		.base = 0x40010800
	}
};

status_t gpioInit(u8 port, u8 pin, u8 mode)
{
	if (port >= NUM_GPIO_PORT) {
		return ERROR;
	}
	gpioPort_t *port = &gpioPorts[port];
	/* Write to CFGLR */
	write32(port->cfglr, );
}

status_t gpioWriteBit(u8 port, u8 pin, u8 data);

