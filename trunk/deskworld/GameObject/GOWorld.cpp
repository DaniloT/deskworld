/*
 * GOWorld.cpp
 *
 *  Created on: 02/02/2011
 *      Author: Zucca
 */

#include "GOWorld.h"

GOWorld::GOWorld(vector<Point> vertices) {
	gravity.SetZero();
	currentTool = rectangle;
	toolColor.r = 15;
	toolColor.g = 15;
	toolColor.b = 15;
	toolColor.a = 245;
	this->vertices = vertices;
	engine = engine->getInstance();
	wObject = engine->CreateWorld(vertices);
	fix = wObject.body->GetFixtureList();
	dynamic = true;
}

GOWorld::~GOWorld() {
	// TODO Auto-generated destructor stub
}

bool GOWorld::isInside(GameObject* object){
	return(fix->TestPoint(object->GetBody()->GetPosition()));
}

bool GOWorld::isInside(Point p){
	b2Vec2 vec;
	vec.x = CONVERT(p.x);
	vec.y = CONVERT(p.y);
	return (fix->TestPoint(vec));
}

uint8 GOWorld::GetCurrentTool(){
	return currentTool;
}

RGBAColor GOWorld::GetWorldColor(){
	return toolColor;
}

bool GOWorld::GetDynamic(){
	return dynamic;
}

void GOWorld::SetCurrentTool(uint8 tool){
	this->currentTool = tool;
}

void GOWorld::SetWorldColor(RGBAColor color){
	this->toolColor = color;
}

void GOWorld::SetDynamic(bool d){
	this->dynamic = d;
}

void GOWorld::SetObjects(vector<GameObject*>* objects){
	this->objects = objects;
}

void GOWorld::SetGravity(b2Vec2 gravity){
	this->gravity = gravity;
}

void GOWorld::Update(){
	//Objects update
	for(Uint32 i = 0; i < objects->size() ; i++){
		if(this->isInside(objects->at(i))){
			b2Vec2 gravbod;
			gravbod.Set(gravity.x*objects->at(i)->GetBody()->GetMass(), gravity.y*objects->at(i)->GetBody()->GetMass());
			objects->at(i)->GetBody()->ApplyForce(gravbod, objects->at(i)->GetBody()->GetWorldCenter());
			objects->at(i)->Update();
		}
	}
}
