#include <iostream>

#include "pi2core/ColorBallAlgorithm.h"
#include "pi2core/AlgorithmInterface.h"
#include "pi2core/TestAlg.h"

int main(){
	std::cout << "Creating Algorithm Context" << std::endl;
	AlgorithmInterface* alg = new ColorBallAlgorithm();
	
	std::cout << "Running Algorithm" << std::endl;
	return alg->pi2Main();
}
