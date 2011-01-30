/*
 * Engine.h
 *
 *  Created on: 21/08/2010
 *      Author: Zucca
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Box2D/Box2D.h"
#include "../Common.h"

#include <vector>
#include <map>
#include "../Graphics/Sprite.h"

struct Object{
	b2Body* body;
	b2PolygonShape shape;
};

class Engine {
	map<Sint16,b2MouseJoint*>::iterator it;
	b2Vec2 gravity;
	b2World* world;
	bool doSleep;
	Engine* instance;
	Engine();
	b2TimeStep timestep;
	b2Vec2 mouseWorld;
	b2Body* groundBody;
public:
	map<Sint16,b2MouseJoint*> mouseJoint;
	virtual ~Engine();
	void Initialize();
	Engine* getInstace();
	Object CreateLine(Uint16 posX, Uint16 posY, Uint16 distance, float32 angle, bool dynamic);
	Object CreateTriangle(Uint16 posX, Uint16 posY, vector<Sint16> vx, vector<Sint16> vy, bool dynamic);
	Object CreateRectangle(Uint16 posX, Uint16 posY, Uint16 w, Uint16 h, bool dynamic);
	Object CreateCircle(Uint16 posX, Uint16 posY, float32 radius, bool dynamic);
	Object CreateFreeform(vector<Sint16> vx, vector<Sint16> vy, float32 radius, bool dynamic);
	void MouseDown(Uint16 xOrig, Uint16 yOrig, Sint16 id);
	void DestroyMouseJoint(Sint16 id);
	void DestroyObject(Object object);
	Object* EraseObject(Uint16 x, Uint16 y);
	void Update();
};

#endif /* ENGINE_H_ */
