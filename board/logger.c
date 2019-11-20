#include "logger.h"
volatile uint64_t milli = 0;
volatile uint32_t seconds = 0;
volatile uint8_t printseconds=0;
uint32_t minutes = 0;
uint32_t hours = 0;
uint8_t ms = 0;



void Sys_Init()
{
	//SysTick_Config(48000000UL/160000);
	SysTick->LOAD =(48000000L/(58*2));

	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{

	milli++; ms++;


	if(0 == milli%10)//4800//1000
	{
		seconds++;printseconds++;
	}
	if(ms>9)
			ms=0;

	if(printseconds>59)
			printseconds=0;
	//DisableIRQ(SysTick_IRQn);
}

void log_time(void)
{

	minutes =seconds/60;
	hours = minutes/60;


	// USE YOUR UART FUNCTION FOR PRINTING
	//  ("\n\r%d : %d: %d: %d",hours,minutes,seconds,ms);




	// USE YOUR UART FUNCTION FOR PRINTING
	char test[60];

	sprintf(test,"\n\r%d : %d: %d.%d\0",hours,minutes,printseconds,ms);
	Send_String_Poll(test);

}
