/*
 * Read button Example
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pigpio.h>

#define GPIO_PWM 23
#define DUTY_MIN 5
#define DUTY_MAX 31

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
   gpioSetMode(GPIO_PWM, PI_OUTPUT);  // Set GPIO as output. But, no need when try to use PWM
   gpioSetPWMfrequency(GPIO_PWM, 50); // Set PWM frequency

   uint8_t duty=DUTY_MIN;
   while(run)
   {
      gpioPWM(GPIO_PWM, duty);
      duty+=1;
      if(duty>=DUTY_MAX) duty=DUTY_MIN;
      time_sleep(0.5);
   }

   /*
    * De-initialize GPIO
    *
    */
   gpioPWM(GPIO_PWM, 0);
   gpioTerminate();

   return 0;
}

