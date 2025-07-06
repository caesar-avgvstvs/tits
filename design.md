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
