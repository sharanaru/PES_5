# 
# Project 5 PES - Readme

Team Members: 
Sharan Arumugam
Abhijeet Srivastava

# Execution Instructions
+ Using custom build configuration this time, to compile for different modes. As always ,please run clean before building a new configuration. 
+ 3 Configurations : Debug, Normal, Test
+ Polling or interrupt is chosen by defining macros before building
+ Application choice ( Echo or Char Count) is also chosen by defining macros before building application
**+ COMPILER COMMANDS**
+ *For building Debug config :* 
arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -Dddebug -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/t1.d" -MT"source/t1.o" -MT"source/t1.d" -o "source/t1.o" "../source/t1.c"
+ *For building Normal config :* 
arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DNORMAL -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/t1.d" -MT"source/t1.o" -MT"source/t1.d" -o "source/t1.o" "../source/t1.c"
+ *For building TEST config :* 
arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DTEST -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/t1.d" -MT"source/t1.o" -MT"source/t1.d" -o "source/t1.o" "../source/t1.c"



# Files in Repo
+ MCU XPRESSO Project Directory
     + Board Folder: Contains regular board files plus
	    + uarts.h/.c: These contain the UART drivers for both polling and interrupt driven
		+ led_board.h/.c These contain the LED functions
	    + buffer_functions.h/.c Contains the buffer control functions
	    + System .h/.c, Testsuite.h/.c, uCUnit-v1.0 These are the files needed for running                  the unit tests  
     + Source Folder - Contains main routine - PES_5_U.c
	
     + Default folders with no change -CMSIS,startup,drivers,utilities
     + Debug - Contains .o files after compilation and also contains .axf binary and .exe files
+ Readme 
+ FMEA analysis
+ UART capture


## Issues faced

+ Uart Initialization had to be derived from code example supplied in class. 
+ While polling , Rx Buffer tended to get full quickly and had to reset the overflow flog each time.
+ Tried to get realloc working but ran into issues when trying to track the values in the reallocated buffer. 
+ Correct value for calibrating Systick timer was difficult and leads to loss in accuracy , either due to multiple interrupts firing at same time (Priority to UART interrupt > Systick priority) or a mistake in calibration value.  
## References
+ Slack channel for clearing up questions on function definitions
+ [https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/Serial-Demo/src](https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/Serial-Demo/src)
+ https://www.nxp.com/docs/en/reference-manual/KL25P80M48SF0RM.pdf


```
