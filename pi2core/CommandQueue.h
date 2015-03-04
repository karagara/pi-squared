#ifndef COMMANDQUEUE_H_
#define COMMANDQUEUE_H_ 

#include <mutex>

struct Command
{
	std::string type;
	int value;
};

class CommandQueue
{
public:
	CommandQueue();
	~CommandQueue(){};

	Command getCommand();
	void putCommand(Command command);
	
private:
	Command cq_command;
	std::mutex cq_mutex;
};
#endif