
#!/bin/sh

# Setup GPIO as PWM OUTPUT
export pwm_pin=23
pigs modes $pwm_pin w
pigs pfs $pwm_pin 1000 # Set 1000Hz PWM.

# Generate with desired duty-cycle
# Resolution is 8-bit (0-255)
pigs pwm $pwm_pin 64 # 25% duty-cycle





