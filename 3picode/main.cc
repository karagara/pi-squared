#include <pololu/orangutan.h> 
#include "../pi2core/pi2serialenums.h"
   
char receive_buffer[32];
char send_buffer[32];
 
void wait_for_sending_to_finish();
void process_received_byte(char byte);
void check_for_new_bytes_received();
 
int main()
{
    serial_set_baud_rate(9600);
    serial_receive_ring(receive_buffer, sizeof(receive_buffer));

    lcd_init_printf(); 
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
		set_m1_speed(speed);
		} break;
	case pi2::SETM2SPEED: {
		int speed = (int)get_next_byte();
		set_m2_speed(speed);
		} break;
	case pi2::PRINT: {
		printf("the new world");
		} break; 
	default: {
                printf("invalid message");
		} break;
	}
}

char get_next_byte(){
	char byte;
	while (serial_get_recieved_bytes() == recieve_buffer_position);
	byte = receive_buffer[receive_buffer_position];
	increment_buffer_position();
	return byte;
}

int increment_buffer_position()
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
    while(!serial_send_buffer_empty());
}
