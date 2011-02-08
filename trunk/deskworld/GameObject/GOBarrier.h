/*
 * GOBarrier.h
 *
 *  Created on: 02/02/2011
 *      Author: Zucca
 */

#ifndef GOBARRIER_H_
#define GOBARRIER_H_

#include "../Common.h"
#include "GameObject.h"

class GOBarrier : GameObject{
	vector<Point> interpoints;
	vector<Point> vertices;
public:
	GOBarrier(vector<Point> vertices);
	virtual ~GOBarrier();
	void SetInterpoints(Point p);
};

#endif /* GOBARRIER_H_ */
