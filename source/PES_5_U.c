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
 * @file    PES_5_U.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include <stdbool.h>
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
//#include "buffer_functions.h"
#include "uarts.h"
#include "MKL25Z4.h"
#define serialstringprint(x) Send_String(x)
//#include "fsl_debug_console.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 *

 */
uint8_t characters[95]={0};
void character_counter(uint16_t bufferlength,user_n *user_t)//counts the characters in buffer
{	uint8_t charvalue;
for(int i=0;i<bufferlength;i++)
{

	charvalue=buffer_read(user_t);
	characters[charvalue-32]+=1;
}
}

void generate_charreport() //prints the character report by going through buffer
{
	serialstringprint("\n\r");

	for(int i=0;i<95;i++)
	{
		if(characters[i]!=0)
		{
			char test[40];
			sprintf( test,"Character %c: %d times \0",i+32,characters[i]);
			Send_String(test);characters[i]=0;

		}
	}
	serialstringprint("\n\r");
}


int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	uint16_t *buffer_t=NULL;
	//	enum Error_status result;

	user_n k = {NULL,NULL,NULL,0,0,0};
	user_n *t=&k;
	uint16_t space = 100; uint8_t l=space;
	printf("hello");
	create_buffer(buffer_t,t, &space);
	uart_init(1);
	Send_String("heya\n\r");
	Send_String("hs\n\r");



	while(1)
	{


		receivewritetobuffer(t, space,l);
		if(k.full)
		{
			//Send_String("Limit reached \n\r");


			character_counter(space,t);
			generate_charreport();
			buffer_reset(t);

		}



		//Send_String("Buffer full");
	}









	return 0 ;
}


