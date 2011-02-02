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
	float32 Update();
	// Render the triangle.
	void Render(SDL_Surface* screen);
};

#endif /* TRIANGLE_H_ */
