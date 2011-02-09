/*
 * GOCircle.h
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#ifndef GOCIRCLE_H_
#define GOCIRCLE_H_

#include "GameObject.h"

class GOCircle : public GameObject{
	float32 radius;
public:
	GOCircle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic);
	virtual ~GOCircle();
	// Updates the objects.
	void Update();
	// Render the object.
	void Render();
};

#endif /* CIRCLE_H_ */
