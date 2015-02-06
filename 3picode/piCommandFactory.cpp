#include "piCommandFactory.h"
#include "../pi2core/pi2serialenums.h"

PiCommand PiCommandFactory::createCommand(){
	char message = this.serial.getNextByte();
	PiCommand * command;
	switch(message){
	case pi2::SETM1SPEED: {
		int speed =  this.serial.getNextByte();
		OrangutanMotors::setM1Speed(speed);
		} break;
	case pi2::SETM2SPEED: {
		int speed = (int)get_next_byte();
		OrangutanMotors::setM2Speed(speed);
		} break;
	case pi2::PRINT: {
		OrangutanLCD::clear();	
		OrangutanLCD::print("the new world");
		} break; 
	default: {
        OrangutanLCD::print("invalid message");
		OrangutanLCD::clear();
		} break;
	}

	return PiCommand
}