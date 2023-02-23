/*
 * Read button Example
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pigpio.h>

#define GPIO_BUTTON 24

int run=1;

void stop(int signum)
{
   run = 0;
}

int main()
{
   /*
    * Initialize GPIO
    *
    */
   if (gpioInitialise() < 0) return -1;
   gpioSetSignalFunc(SIGINT, stop);
   gpioSetMode(GPIO_BUTTON, PI_INPUT); // Set GPIO as input.

   int button_value=0;

   while(run)
   {
      button_value = gpioRead(GPIO_BUTTON); // Read button's logic.
      if(!button_value){
	  printf("button is pressed\n");
      }
      time_sleep(1);
   }

   /*
    * De-initialize GPIO
    *
    */
   gpioTerminate();

   return 0;
}

