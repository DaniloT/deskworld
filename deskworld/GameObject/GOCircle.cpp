/*
 * GOCircle.cpp
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#include "GOCircle.h"

GOCircle::GOCircle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic) {
	engine = engine->getInstance();
	this->vx = vx;
	this->vy = vy;
	this->color = color;
	this->dynamic = dynamic;

	radius = DISTANCE((float32)vx.at(0), (float32)vy.at(0), (float32)vx.at(1), (float32)vy.at(1));
	object = engine->CreateCircle(vx.at(0),vy.at(0),radius, dynamic);
	this->vx.erase(this->vx.begin()+1);
	this->vy.erase(this->vy.begin()+1);
}

GOCircle::~GOCircle() {
	engine->DestroyObject(this->object);
}

float32 GOCircle::Update(){
	if(dynamic){
		vx.at(0) = (int)(object.body->GetPosition().x*PIXELS_PER_METRE);
		vy.at(0) = (int)(object.body->GetPosition().y*PIXELS_PER_METRE);
	}
	//Return value of y axis for deleting bodys out of screen
	return object.body->GetPosition().y*PIXELS_PER_METRE;
}

void GOCircle::Render(){
	graphics->DrawCircle( (int)vx.at(0), (int)vy.at(0), (int)radius, color);
}
