#include <pololu/orangutan>
#include "../pi2core/pi2serialenums.h"
   
char receive_buffer[32];
char send_buffer[32];
unsigned char receive_buffer_position = 0;

void process_messages();
void increment_buffer_position();
void wait_for_sending_to_finish();
char get_next_byte();

int main()
{
    OrangutanSerial::setBaudRate(9600);
    OrangutanSerial::receiveRing(receive_buffer, sizeof(receive_buffer));
    OrangutanLEDs::green(HIGH);
    OrangutanLEDs::red(TOGGLE);
    OrangutanLCD::print("Derp");
    
    while(1)
    {
        process_messages();
    }
}


void process_messages(){
	//get one byte
	char message = get_next_byte();

	switch(message){
	case pi2::SETM1SPEED: {
		int speed = (int)get_next_byte();
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
}

char get_next_byte(){
	char byte;
	while (OrangutanSerial::getReceivedBytes() == receive_buffer_position);
	byte = receive_buffer[receive_buffer_position];
	increment_buffer_position();
	return byte;
}

void increment_buffer_position()
{
	if (receive_buffer_position == sizeof(receive_buffer)-1)
        {
            receive_buffer_position = 0;
        }
        else
        {
            receive_buffer_position++;
        }
}

void wait_for_sending_to_finish()
{
    while(!OrangutanSerial::sendBufferEmpty());
}
