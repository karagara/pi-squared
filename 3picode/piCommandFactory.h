#ifndef PICOMMANDFACTORY_H_
#define PICOMMANDFACTORY_H_

class PiCommand;
class SerialManager;

class PiCommandFactory {
public:
	//Constructors
	PiCommandFactory(SerialManager sManager) : serial(sManager) { };
	~PiCommandFactory();

	PiCommand createCommand();
private:
	SerialManager serial;
};

#endif /* PICOMMANDFACTORY_H_ */