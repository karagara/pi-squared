#include "CommandQueue.h"
#include "pi2serialenums.h"

CommandQueue::CommandQueue(){
	Command c;
	c.type = "nomsg";
	c.value = 0;
	this->cq_command = c; 
}

void CommandQueue::putCommand(Command command){
	this->cq_mutex.lock();
	this->cq_command = command;
	this->cq_mutex.unlock();
}

Command CommandQueue::getCommand(){
	Command replace_c;
	replace_c.type = "nomsg";
	replace_c.value = 0;

	this->cq_mutex.lock();
	Command c = this->cq_command;
	this->cq_command = replace_c;
	this->cq_mutex.unlock();

	return c;
}
