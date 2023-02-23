/*
 * Blinking Example
 *
 * To compile with GCC
 * gcc -o blink blink-pigpio.c -lpigpio
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pigpio.h>

#define GPIO_LED 23

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

   /*
    * Blinking forever until interrupt from SIGINT
    *
    */
   while(run)
   {
      gpioWrite(GPIO_LED, 1); // Turn on LED.
      time_sleep(1);
      gpioWrite(GPIO_LED, 0); // Turn off LED.
      time_sleep(1);
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

