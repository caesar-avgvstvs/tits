#include <tits.h>
#include <tits_uart.h>
#include <tits_gpio.h>


int main(void)
{
	/* TODO 
	 * System Init
	 * 	- Clock Init
	 * 	- Interrupt Ctlr Init
	 */
	titsSysInit();
	gpioInit(PORTA, PIN0, MODE_IN);
	uartInit();
}
