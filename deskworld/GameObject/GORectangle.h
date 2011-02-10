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
	float32 GetRestitution();
	float32 GetFriction();
	float32 GetDensity();
	void SetRestitution(float32 rest);
	void SetFriction(float32 fric);
	void SetDensity(float32 dens);
};

#endif /* RECTANGLE_H_ */
