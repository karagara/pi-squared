/* main.cpp
 * Authors: Yan Liu, Colten Normore
 *
 * Main method for the 3pi/R.Pi vision system. Sets up the individual modules,
 * and gets things rolling
 */

#include <iostream>
#include "pi2core/pi2serialenums.h"

#include <wiringPi.h>
#include <wiringSerial.h>


int main( int argc, const char* argv[] ) {
	pi2::Serial serialTest = pi2::SETM2SPEED;
	char chartest = (char)355;
	std::cout << "chartest is " << chartest << std::endl;
	std::cout << "back to int is " << (int)chartest << std::endl;

	int fd = 0;
	int count = 0;
	unsigned int nextTime = 0;

	if ((fd = serialOpen("/dev/ttyAMA0", 9800)) < 0)
	{
		std::cout << "Unable to open serial device" << std::endl;
		return 1 ;
	}
/*	
	if (wiringPiSetup() == -1 )
	{
		std::cout << "Unable to start wiringPi" << std::endl;
	}	
	
	std::cout << "Attempting to send 'A' to the 3Pi" << std::endl;
	serialPutchar(fd, pi2::PRINT);
	serialPutchar(fd, 'A');
*/	
	return 0;
}

