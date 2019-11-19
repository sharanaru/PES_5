/*
 * uarts.h
 *
 *  Created on: Nov 17, 2019
 *      Author: shara
 */

//#ifndef UARTS_H_
//#define UARTS_H_
#define begincritical() NVIC_DisableIRQ(UART0_IRQn)
#define endcritical() NVIC_EnableIRQ(UART0_IRQn)
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
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)
extern user_n k;

/*
 * @brief   Application entry point.
 */

bool UART0_Transmit_Poll() ;
bool UART0_Receive_Poll(void);
void Send_Char_Poll(char k);
void uart_init(uint8_t interrupt);
void UART0_IRQHandler(void) ;
void Send_String(char * str);
char serialreturner();
void Send_String_Poll(char *s);
char received_char();
void Send_Char(char k);
bool interrruptcheck();
void echo();
//void receivewritetobuffer();
void receivewritetobuffer(user_n *user_t, uint16_t size,uint8_t l);



//#endif /* UARTS_H_ */
