/*
 * GORectangle.h
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#ifndef GORECTANGLE_H_
#define GORECTANGLE_H_

#include "GameObject.h"

class GORectangle : public GameObject{
public:
	GORectangle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic);
	virtual ~GORectangle();
	// Updates the objects.
	void Update();
	// Render the object.
	void Render();
};

#endif /* RECTANGLE_H_ */
