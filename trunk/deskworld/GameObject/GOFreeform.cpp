/*
 * GOFreeform.cpp
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#include "GOFreeform.h"

GOFreeform::GOFreeform(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic, float32 thickness) {
	engine = engine->getInstance();
	this->vx = vx;
	this->vy = vy;
	this->color = color;
	this->dynamic = dynamic;

	this->thickness = thickness;
	object = engine->CreateFreeform(vx, vy, thickness, dynamic);
}

GOFreeform::~GOFreeform() {
	engine->DestroyObject(this->object);
}

void GOFreeform::Update(){
	if(dynamic){
		b2Fixture* fixList = object.body->GetFixtureList();
		b2CircleShape* shape;
		for(Uint32 i = 0 ; fixList != NULL ; i++){
			shape = (b2CircleShape*) fixList->GetShape();
			vx.at(i) = (int)((object.body->GetWorldPoint(shape->GetVertex(0)).x)*PIXELS_PER_METRE);
			vy.at(i) = (int)((object.body->GetWorldPoint(shape->GetVertex(0)).y)*PIXELS_PER_METRE);
			fixList = fixList->GetNext();
		}
	}
}


void GOFreeform::Render(){
	for(Uint32 i = 0 ; i < vx.size() ; i++){
		graphics->DrawCircle( (int)vx.at(i), (int)vy.at(i), (int)thickness, color);
	}
}
