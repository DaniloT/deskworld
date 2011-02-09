/*
 * GOWorld.h
 *
 *  Created on: 02/02/2011
 *      Author: Zucca
 */

#ifndef GOWORLD_H_
#define GOWORLD_H_

#include "../Common.h"
#include "GameObject.h"
#include "../Engine/Engine.h"

class GOWorld{
	//World Object
	Object wObject;
	//Vertices delimiting world area
	vector<Point> vertices;
	//Gravity of the world
	b2Vec2 gravity;
	//Current tool of this world
	uint8 currentTool;
	//Dynamic objetcs tool
	bool dynamic;
	//Tool color of this world
	RGBAColor toolColor;
	//Array of objects in this world
	vector<GameObject*>* objects;
	//Fixture of world for collision detection
	b2Fixture* fix;
	//Engine Instance
	Engine* engine;
public:
	//Create world with zero gravity, rectangle tool, black tool color by default
	GOWorld(vector<Point> vertices);
	virtual ~GOWorld();
	bool isInside(GameObject* object);
	bool isInside(Point p);
	Object CreateObject(GameObject* object);
	uint8 GetCurrentTool();
	RGBAColor GetWorldColor();
	bool GetDynamic();
	void SetCurrentTool(uint8 tool);
	void SetWorldColor(RGBAColor color);
	void SetDynamic(bool d);
	void SetObjects(vector<GameObject*>* objects);
	void SetGravity(b2Vec2 gravity);
	void Update();
	void Resize(vector<Point> vertices);
};

#endif /* GOWORLD_H_ */
