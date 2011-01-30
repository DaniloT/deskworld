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
	GOCircle(vector<Sint16> vx, vector<Sint16> vy, RGBAColor color, bool dynamic);
	virtual ~GOCircle();
	// Updates the objects.
	float32 Update();
	// Render the object.
	void Render(SDL_Surface* screen);
};

#endif /* CIRCLE_H_ */
