#ifndef _TITS_UART_H_
#define _TITS_UART_H_

#define UART0			0
#define UART0_ADDR		0x40005000

/* Registers */
#define UART_CTRL1		0x0c
#define UART_CTRL2		0x10
#define UART_DATA		0x10
#define UART_STAT		0x0


/* UART Control Registers Offsets */
#define UART_CTRL1_TE
#define UART_CTRL1_RE
#define UART_CTRL1_PS
#define UART_CTRL1_PCE
#define UART_CTRL1_M
#define UART_CTRL1_UE

#define UART_CTRL2_STOP
#define UART_CTRL2_CLKEN
 
/* Status Register Offset */
#define UART_STAT_NE
#define UART_STAT_ORE
#define UART_STAT_IDLE
#define UART_STAT_RXNE
#define UART_STAT_TC
#define UART_STAT_TXE

typedef struct {
	
} uartCfg_t;

void uartInit();

#endif
