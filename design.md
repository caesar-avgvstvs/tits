# TITS boot flow

1. startup.s sets up the interrupt vector table
2. startup.s then calls the systemInit routine setup the system clock
3. startup.s then transfers control to the C routine 'main'.
4. main then initializes the interrupt controller and the peripherals that are to be used.
5. main then starts the scheduler to run the tasks.


## CH32V203 UART Driver Notes

- 3 USART (USART1/2/3)
- 5 UART (USART4/5/6/7/8)

Configuration:
- When TE bit in USARTx_CTRL1 is set, the data in the transmission shift register will be outputtted on TX and the clock will be outputted on CK.
- Data word length is set by configuring the M bit in USARTx_CTRL1.
- No. of stop bits is configurable.

USARTx_CTRL1:
- TE
- RE
- RXNEIE
- TCIE
- TXEIE
- M
- UE
