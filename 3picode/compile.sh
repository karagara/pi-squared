#!/bin/bash

avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os   -c -o M1Speed.o M1Speed.cpp
avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os   -c -o M2Speed.o M2Speed.cpp
avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os   -c -o Print.o Print.cpp
avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os   -c -o PiCommand.o PiCommand.cpp
avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os   -c -o PiCommandFactory.o PiCommandFactory.cpp
avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os   -c -o SerialManager.o SerialManager.cpp
avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os   -c -o main.o main.cpp
avr-g++ -g -Wall -mcall-prologues -mmcu=atmega328p  -Os main.o SerialManager.o PiCommandFactory.o M1Speed.o M2Speed.o Print.o -Wl,-gc-sections -lpololu_atmega328p -Wl,-relax -o main.obj
avr-objcopy -R .eeprom -O ihex main.obj main.hex
rm main.obj

echo "Done!"
