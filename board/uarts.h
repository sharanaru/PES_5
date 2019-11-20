/*
 * uarts.h - For both interrupt and polling driven UART
 *
 *  Created on: Nov 17, 2019
 *      Author: Sharan
 */

//#ifndef UARTS_H_
//#define UARTS_H_
#define begincritical() NVIC_DisableIRQ(UART0_IRQn) //macro to define beginning of critical section
#define endcritical() NVIC_EnableIRQ(UART0_IRQn) //macro to define end of critical section
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "buffer_functions.h"
#include "led_board.h"
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)
//Resource for initialising uart -https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/src/UART.c
//extern user_n k;
//extern enum Error_status result;
/*
 * @brief   Application entry point.
 */

bool UART0_Transmit_Poll() ; //checking if transmission can occur
bool UART0_Receive_Poll(void); //checking if anything to be received
void Send_Char_Poll(char k); // sends single char value using polling driver
void uart_init(uint8_t interrupt); //iniitlaises uart functions
void UART0_IRQHandler(void) ;//uart irq handler
void Send_String(char * str);//sends string using uart interrupt
char serialreturner(); //returns received char through uart polling
void Send_String_Poll(char *s);//prints string using uart polling driver
char received_char();//returns recived character in uart interrupt
void Send_Char(char k);//sends a char to terminal using interrupt
bool txinterrruptcheck();//checks if tx interrupt has occured
void poll_receivewritetobuffer(user_n *user_t,uint16_t size);//writes to created circular buffer using received value- UART poll
void echo();
void receivewritetobuffer(user_n *user_t, uint16_t size,uint8_t l);//writes to buffer with received value -UARTinterrupt



//#endif /* UARTS_H_ */
