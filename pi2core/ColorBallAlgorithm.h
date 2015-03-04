/**
* ColorBallAlgorithm.h
*
* Created by: Colten Normore
*	Created on: Feb 17th, 2015 
*
* ColorBallAlgorithm inherits from AlgorithmInterface. It encompases the logic
* needed to track a colored ball. The logic is kept in the pi2Main fucntion, and
* loops until interruption. 
*/

#ifndef COLORBALLALGORITHM_H_
#define COLORBALLALGORITHM_H_

#include "AlgorithmInterface.h"

class FrameQueue;
class CommandQueue;

class ColorBallAlgorithm : public AlgorithmInterface
{
public:
	ColorBallAlgorithm(){};
	~ColorBallAlgorithm(){};
	
	int pi2Main();
	int testMain(FrameQueue *fq, CommandQueue *cq);
};

#endif