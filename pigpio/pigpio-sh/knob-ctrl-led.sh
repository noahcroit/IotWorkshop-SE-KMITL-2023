#!/bin/sh

# Setup GPIO for LED as OUTPUT pin
#                Knob as INPUT pin
export ledpin=23
export knobpin=24
pigs modes $ledpin w
pigs modes $knobpin r

# Blinking LED
export scanperiod=0.2
export numseq=4
while [ 1 ]
do
	if [ $(pigs read $knobpin) -eq 1 ]
	then
		echo "turn on LED @ GPIO pin $ledpin"
		pigs write $ledpin 1
	else
		pigs write $ledpin 0
	fi
	sleep $scanperiod
done





