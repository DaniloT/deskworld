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
	map<int,b2MouseJoint*>::iterator it;
	b2Vec2 gravity;
	b2World* world;
	bool doSleep;
	Engine* instance;
	Engine();
	b2TimeStep timestep;
	b2Vec2 mouseWorld;
	b2Body* groundBody;
public:
	map<int,b2MouseJoint*> mouseJoint;
	virtual ~Engine();
	void Initialize();
	Engine* getInstance();
	Object CreateLine(int posX, int posY, int distance, float32 angle, bool dynamic);
	Object CreateTriangle(int posX, int posY, vector<int> vx, vector<int> vy, bool dynamic);
	Object CreateRectangle(int posX, int posY, int w, int h, bool dynamic);
	Object CreateCircle(int posX, int posY, float32 radius, bool dynamic);
	Object CreateFreeform(vector<int> vx, vector<int> vy, float32 radius, bool dynamic);
	void MouseDown(int xOrig, int yOrig, int id);
	void DestroyMouseJoint(int id);
	void DestroyObject(Object object);
	Object* EraseObject(int x, int y);
	void Update();
};

#endif /* ENGINE_H_ */
