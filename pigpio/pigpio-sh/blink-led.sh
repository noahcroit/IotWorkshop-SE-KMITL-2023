#!/bin/sh

# Setup GPIO for LED as OUTPUT pin
export ledpin=23
pigs modes $ledpin w

# Blinking LED
export period=0.5
export numseq=4
for i in `seq $numseq`
do
	echo "turn on LED @ GPIO pin $ledpin"
	pigs write $ledpin 1
	sleep $period
	echo "turn off LED @ GPIO pin $ledpin"
	pigs write $ledpin 0
	sleep $period
done





