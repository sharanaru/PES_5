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
#define poll
#define app
#include <stdbool.h>
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "led_board.h"
//#include "buffer_functions.h"
#include "uarts.h"
#include "MKL25Z4.h"
#ifdef TEST
#include "Testsuite.h"
#include "uCUnit-v1.0.h"
#include "System.h"
#endif
#ifdef interrupt
#define serialstringprint(x) Send_String(x)
#define uartinit() uart_init(1)
#endif
#ifdef poll
#define serialstringprint(x) Send_String_Poll(x)
#define Send_String(x) Send_String_Poll(x)
#define uartinit() uart_init(0)
#endif
#include "logger.h"
//enum Error_status result;
//#include "fsl_debug_console.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 *

 */
uint8_t characters[95]={0};
void character_counter(uint16_t bufferlength,user_n *user_t)//counts the characters in buffer
{	logfunction();
	uint8_t charvalue;
for(int i=0;i<bufferlength;i++)
{

	charvalue=buffer_read(user_t);
	characters[charvalue-32]+=1;
}
}

void generate_charreport() //prints the character report by going through buffer
{	logfunction();
	serialstringprint("\n\r");

	for(int i=0;i<95;i++)
	{
		if(characters[i]!=0)
		{
			char test[40];
			sprintf( test," %c - %d;\0",i+32,characters[i]);
			Send_String(test);
			characters[i]=0;

		}
	}
	log_time();
	serialstringprint("\n\r");
}


int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	LED_Initialise();

	uint16_t *buffer_t=NULL;
	//	enum Error_status result;

	user_n k = {NULL,NULL,NULL,0,0,0};
	user_n *t=&k;
	uint16_t space = 100; uint8_t l=space;
	//printf("hello");
	create_buffer(buffer_t,t, &space);
	Sys_Init();
	uartinit();
	LED_PROCESS();
logmode();
logapp();
#ifdef TEST

		user_n testinginstance = {NULL,NULL,NULL,0,0,0};
			user_n *testptr=&testinginstance;
			uint16_t testsize=3;
			enum Error_status testresult;
			UCUNIT_Init();
			UCUNIT_TestcaseBegin("Project 5 testing begins");
			testresult=create_buffer(buffer_t,testptr, &testsize);
			UCUNIT_CheckIsEqual(SUCCESS,testresult);//checks if buffer creation was successfull;
			buffer_write(testptr, 5, testsize);
			int f=buffer_read(testptr);
			UCUNIT_CheckIsEqual(5,f);//check if reading correctly
			buffer_write(testptr,5,testsize);
			buffer_write(testptr,6,testsize);
			buffer_write(testptr,7,testsize);
			if(testinginstance.full)
				UCUNIT_WriteString("Buffer full");
			int kt=buffer_read(testptr);
			buffer_read(testptr);
			buffer_read(testptr);
			UCUNIT_CheckIsEqual(kt,buffer_read(testptr));//check if read after end of buffer is same as first value in buffer
			buffer_write(testptr,6,testsize);
			UCUNIT_CheckIsEqual(SUCCESS,testresult);//check if it can overlap and write
			buffer_write(testptr,5,testsize);
			buffer_write(testptr,6,testsize);
			buffer_write(testptr,7,testsize);//buffer limit reached
			buffer_write(testptr,8,testsize);
			UCUNIT_CheckIsEqual(8,buffer_read(testptr));//buffer has failed
			buffer_reset(testptr);
			UCUNIT_Check(buffer_read(testptr)==FAILURE,"Buffer is empty so fail","Args is buffer pointer");
			buffer_destroy(testptr);
			UCUNIT_CheckIsNull(testptr->buffer);//if buffer is destroyed
#endif


	while(1)
	{
LED_PROCESS();
#ifdef interrupt
#ifdef app
		receivewritetobuffer(t, space,l);
		if(k.full)
		{
			//Send_String("Limit reached \n\r");

			LED_FAIL();delay();LED_PASS();
			character_counter(space,t);
			generate_charreport();
			buffer_reset(t);

		}



		//Send_String("Buffer full");
#endif
#ifdef echoapp
		echo();
#endif
#endif
#ifdef poll
#ifdef app
		poll_receivewritetobuffer(t,space);
		if(k.full)
		{
			//Send_String("Limit reached \n\r");

			LED_FAIL();delay();LED_PASS();
			character_counter(space,t);
			generate_charreport();
			buffer_reset(t);

		}
#endif
#ifdef echoapp

		Send_Char_Poll(serialreturner());

#endif
#endif

	}







	return 0 ;
}


