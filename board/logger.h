//Sharan Arumugam and Abhijeet- Generates logging messages and Timestamps using Systick
#include "MKL25Z4.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include <stdio.h>
#include "uarts.h"
#ifdef poll
#define serialstringprint(x) Send_String_Poll(x)
#define logwrite(x) Send_String_Poll(x)
#endif
#ifdef interrupt //to use string print functions of interrupt
#define serialstringprint(x) Send_String(x)
#define logwrite(x) Send_String(x)
#endif

#ifdef ddebug //to display current function also
#define logfunction() serialstringprint("Function running is ");serialstringprint(__func__);serialstringprint("\n\r")
#define logmode() serialstringprint("Mode is Debug\n\r");
#else
#define logfunction()
#endif
//when debug messages arent required
#ifdef NORMAL
#define logmode() serialstringprint("Mode is Normal\n\r");
#endif

#ifdef TEST
#define logfunc() printf("%s ",__func__);printf("x");
#define logmode() serialstringprint("Mode is Debug\n\r");
#else
#define logfunc()
#endif
#ifdef echo
#define logapp() serialstringprint("Application running is echo\n\r")
#endif
#ifdef app
#define logapp() serialstringprint("Application running is Char count\n\r")
#endif
#ifdef echoapp
#define logapp() serialstringprint("Application running is Echo\n\r")
#endif
void Sys_Init();
void SysTick_Handler(void);
void log_time(void);
