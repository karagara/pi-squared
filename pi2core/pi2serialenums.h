/****************************
* pi2serialenums.cpp
* File containing common enums for the 3pi and RPi
* 
****************************/

namespace pi2 {
	enum Serial {
		SETM1SPEED = 0,
		SETM2SPEED = 1,
		PRINT = 2
	};
    
    enum Type{
        FORWARD = 'f',
        BACK = 'b',
        LEFT = 'l',
        RIGHT = 'r',
        STOP = 's',
        NOCOMMAND = 'n',
        CONNDONE = 'c'
    };
}
