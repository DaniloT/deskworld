/*
 * GOPolygon.h
 *
 *  Created on: 05/02/2011
 *      Author: Zucca
 */

#ifndef GOPOLYGON_H_
#define GOPOLYGON_H_

#include "GameObject.h"

class GOPolygon : public GameObject{
	bool convex;
public:
	GOPolygon(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic);
	GOPolygon();
	virtual ~GOPolygon();
	void set(GOPolygon p);
	// Updates the objects.
	void Update();
	// Render the object.
	void Render();
	bool isConvex();
};

#endif /* POLYGON_H_ */

