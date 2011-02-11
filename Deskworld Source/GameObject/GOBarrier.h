/*
 * GOBarrier.h
 *
 *  Created on: 02/02/2011
 *      Author: Zucca
 */

#ifndef GOBARRIER_H_
#define GOBARRIER_H_

#include "GameObject.h"

class GOBarrier : public GameObject{
public:
	GOBarrier(vector<int> vx, vector<int> vy, RGBAColor color);
	virtual ~GOBarrier();
	void Update();
	void Render();
};

#endif /* GOBARRIER_H_ */
