/*
 * GOCircle.cpp
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#include "GOCircle.h"

GOCircle::GOCircle(vector<Sint16> vx, vector<Sint16> vy, RGBAColor color, bool dynamic) {
	engine = engine->getInstace();
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
		vx.at(0) = (Sint16)(object.body->GetPosition().x*PIXELS_PER_METRE);
		vy.at(0) = (Sint16)(object.body->GetPosition().y*PIXELS_PER_METRE);
	}
	//Return value of y axis for deleting bodys out of screen
	return object.body->GetPosition().y*PIXELS_PER_METRE;
}

void GOCircle::Render(SDL_Surface* screen){
	graphics->DrawCircle(screen, (Uint16)vx.at(0), (Uint16)vy.at(0), (Sint16)radius, color);
}
