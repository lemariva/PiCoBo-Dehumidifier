/*
 * uart.c
 *
 *  Created on: 03.05.2014
 *      Author: riva
 */

#include "uart.h"

/**
 * Callback handler for receive
 */
void (*uart_rx_isr_ptr)(unsigned char c);

void uart_init(void)
{
	uart_set_rx_isr_ptr(0L);

	#if defined(UART_DRIVER_USCI_A)
		P1SEL  = BIT1 + BIT2;					  //=>RXD + TXD;
		P1SEL2 = BIT1 + BIT2;					  //=>RXD + TXD;
		UCA0CTL1 |= UCSSEL_2;                     // SMCLK = 16MHz/2
		UCA0BR0 = 65;                             // 16MHz 9600		(UCA0BR1*256) + UCA0BR0 = SMCLK / Baudios
		UCA0BR1 = 3;                              // 16MHz 9600

		UCA0MCTL = UCBRS0;                        // Modulation UCARSx = 1
		UCA0CTL1 &= ~UCSWRST;                     // Initialize USCI state machine
		IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
	#endif
}

void uart_set_rx_isr_ptr(void (*isr_ptr)(unsigned char c))
{
	uart_rx_isr_ptr = isr_ptr;
}

unsigned char uart_getc()
{
    //while (!(IFG2 & UCA0RXIFG));                // USCI_A0 RX buffer ready?
	return UCA0RXBUF;
}


void uart_putc(unsigned char c)
{
	while (!(IFG2&UCA0TXIFG));              // USCI_A0 TX buffer ready?
  	UCA0TXBUF = c;                    		// TX
}


void uart_puts(const char *str)
{
     while(*str) uart_putc(*str++);
}

#pragma vector=USCIAB0TX_VECTOR				//UART TX USCI Interrupt
	__interrupt void USCI0TX_ISR(void)
	{
		UCA0TXBUF = tx_char;				//Copy char to the TX Buffer
		tx_flag = 0;						//ACK the tx_flag
		IE2 &= ~UCA0TXIE; 					//Turn off the interrupt to save CPU
	}
