/*
 * GOTriangle.cpp
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#include "GOTriangle.h"

GOTriangle::GOTriangle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic) {
	int posX, posY;
	float32 distance;

	engine = engine->getInstance();
	this->color = color;
	this->dynamic = dynamic;
	this->vx = vx;
	this->vy = vy;

	//Bug control for tiny elements
	distance = DISTANCE(vx.at(0), vy.at(0), vx.at(1), vy.at(1));
	if(distance < 2.0f){
		vx.at(1) ++;
		vy.at(1) ++;
		vx.at(2) --;
		vy.at(2) ++;
	}
	//Bug control for tiny elements
	distance = DISTANCE(vx.at(1), vy.at(1), vx.at(2), vy.at(2));
	if(distance < 2.0f){
		vx.at(1) += 2;
		vy.at(2) -= 2;
	}

	//Position equals mass center for Box2d
	posX = (vx.at(0) + vx.at(1) + vx.at(2))/3;
	posY = (vy.at(0) + vy.at(1) + vx.at(2))/3;

	object = engine->CreateTriangle(posX, posY, vx, vy, dynamic);

	//Getting positions for the triangle in the world
	this->vx.at(0) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(0)).x)*PIXELS_PER_METRE);
	this->vy.at(0) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(0)).y)*PIXELS_PER_METRE);
	this->vx.at(1) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(1)).x)*PIXELS_PER_METRE);
	this->vy.at(1) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(1)).y)*PIXELS_PER_METRE);
	this->vx.at(2) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(2)).x)*PIXELS_PER_METRE);
	this->vy.at(2) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(2)).y)*PIXELS_PER_METRE);
}

GOTriangle::~GOTriangle() {
	engine->DestroyObject(this->object);
}

void GOTriangle::Update(){
	if(dynamic){
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			vx.at(i) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(i)).x)*PIXELS_PER_METRE);
			vy.at(i) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(i)).y)*PIXELS_PER_METRE);
		}
	}
}

void GOTriangle::Render(){
	graphics->DrawPolygon( vx, vy, 3, color);
}
