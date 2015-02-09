/*
 * logic.h
 *
 *  Created on: Jul 4, 2014
 *      Author: Colten
 */

#ifndef LOGIC_H_
#define LOGIC_H_

#include "controllerInterface.h"
#include "visionInterface.h"
#include <opencv/highgui.h>
#include <opencv/cv.h>

class logic {
public:
	logic(controllerInterface *, visionInterface *);
	virtual ~logic();
	void runLogic();
    void morphologicalImgProc(cv::Mat &frame);
    std::string integerToString(int num);
    int angleToCenter(const CvPoint &v1, const CvPoint &v2);
    void doAction(int totalAngleOfFinger, int fingerSize);
    void creatHSVApp();

private:
	controllerInterface* c_module;
	visionInterface* v_module;
   
};

#endif /* LOGIC_H_ */
