
/*
 * Workshop 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pigpio.h>

#define GPIO_LED 23
#define GPIO_X_AXIS 24
#define GPIO_Y_AXIS 25

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
   gpioSetMode(GPIO_LED, PI_OUTPUT); // Set GPIO as output.
   gpioSetMode(GPIO_X_AXIS, PI_INPUT); // Set GPIO as input.
   gpioSetMode(GPIO_Y_AXIS, PI_INPUT); // Set GPIO as input.

   while(run)
   {  
      // X-axis
      if(!gpioRead(GPIO_X_AXIS)){
          gpioWrite(GPIO_LED, 1); // Turn on LED.
          time_sleep(1);
          gpioWrite(GPIO_LED, 0); // Turn off LED.
          time_sleep(1);
      }
      
      // Y-axis
      if(!gpioRead(GPIO_Y_AXIS)){
          gpioWrite(GPIO_LED, 1); // Turn on LED.
          time_sleep(0.2);
          gpioWrite(GPIO_LED, 0); // Turn off LED.
          time_sleep(0.2);
      }
   }

   /*
    * De-initialize
    * turn off LED before exit
    *
    */
   gpioWrite(GPIO_LED, 0); // Turn off LED.
   gpioTerminate();

   return 0;
}

