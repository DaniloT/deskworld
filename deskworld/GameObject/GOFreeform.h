/*
 * GOFreeform.h
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#ifndef GOFREEFORM_H_
#define GOFREEFORM_H_

#include "GameObject.h"

class GOFreeform : public GameObject{
	float32 thickness;
public:
	GOFreeform(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic, float32 thickness);
	virtual ~GOFreeform();
	// Updates the objects.
	void Update();
	// Render the object.
	void Render();
};

#endif /* FREEFORM_H_ */
