/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    uart.c
 * @brief   Application entry point.
 */
#include "uarts.h"
#include "ctype.h"
uint8_t txinterrupt;

bool UART0_Transmit_Poll() {
	while(!(UART0->S1 & UART0_S1_TDRE_MASK))

		//UART0->D = data;
		return true;

	return false;
}

bool UART0_Receive_Poll(void)
{
	if(!(UART0->S1 & UART0_S1_RDRF_MASK))

		//return UART0->D;
		return true;
	else
		return false;
}
char serialreturner()
{ UART0->S1 |= UART0_S1_OR(1);
	while(UART0_Receive_Poll())
		;
	return UART0->D;


}
char stringsender(char k)
{
	//if (*k != '\0') { // Send characters up to null terminator

	return k;
	//UART0_Transmit_Poll(*str++);


}
void Send_Char_Poll(char k) {
	// enqueue string
	//	while (*str != '\0') { // Send characters up to null terminator
	//
	//		UART0_Transmit_Poll(*str++);
	while(UART0_Transmit_Poll()) //blocking here
		;

	//if((!UART0_Transmit_Poll()))
	UART0->D=stringsender(k);


}
void Send_String_Poll(char *s)
{
	while(*s !='\0')
		Send_Char_Poll(*s++);
}

void uart_init(uint8_t interrupt){

	/* Init board hardware. */

	uint16_t sbr;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK/2)/(115200 * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
			UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	if(interrupt)
	{
		// Enable interrupts. Listing 8.11 on p. 234


		NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
		NVIC_ClearPendingIRQ(UART0_IRQn);
		NVIC_EnableIRQ(UART0_IRQn);

		// Enable receive interrupts but not transmit interrupts yet
		UART0->C2 |= UART_C2_RIE(1);
	}
	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;





}
uint8_t ch; bool received;
void UART0_IRQHandler(void) {


	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
			UART_S1_FE_MASK | UART_S1_PF_MASK))
	{
		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
				UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		ch = UART0->D;



	}
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		ch = UART0->D;received=true;



	}


	if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		// can send another character

		//UART0->D = ch;
		txinterrupt=true;
		UART0->C2 &= ~UART0_C2_TIE_MASK;
	}

	// queue is empty so disable transmitter interrupt
	//UART0->C2 &= ~UART0_C2_TIE_MASK;
}

bool txinterruptcheck()
{
	UART0->C2 |= UART0_C2_TIE_MASK; //enabling tx interrupt here
	while(!txinterrupt)
		;
	//if(txinterrupt)
	//{
	txinterrupt=false;UART0->C2 &= ~UART0_C2_TIE_MASK;
	return true;
	//}
	//else
	//return false;
}
char received_char()
{

	return ch;

}
void Send_Char(char k)
{
	if(txinterruptcheck())
	{
		begincritical();
		UART0->D = k;
		endcritical();
	}

}
void receivewritetobuffer(user_n *user_t,uint16_t size,uint8_t l)
{
	if(received)
	{

		buffer_write(user_t,received_char(), size);
		received=false;


	}
}
void poll_receivewritetobuffer(user_n *user_t,uint16_t size)
{
	uint8_t writed=serialreturner();
	buffer_write(user_t, writed, size);
}
void Send_String(char *str) {
	// enqueue string
	while (*str != '\0') { // copy characters up to null terminator

		if(txinterruptcheck())
		{
			begincritical();
			UART0->D = *str;
			str++;
			endcritical();
			//UART0->C2 |= UART0_C2_TIE(1);
		}
	}
}


void echo()
{
	if(received)
	{
		Send_Char(received_char());
		received=false;
	}
}







