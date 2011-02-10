/*
 * GOTriangle.h
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#ifndef GOTRIANGLE_H_
#define GOTRIANGLE_H_

#include "GameObject.h"

class GOTriangle : public GameObject{
public:
	GOTriangle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic);
	virtual ~GOTriangle();
	// Updates triangle position.
	void Update();
	// Render the triangle.
	void Render();
	float32 GetRestitution();
	float32 GetFriction();
	float32 GetDensity();
	void SetRestitution(float32 rest);
	void SetFriction(float32 fric);
	void SetDensity(float32 dens);
};

#endif /* TRIANGLE_H_ */
