/*
 * GORectangle.cpp
 *
 *  Created on: 19/01/2011
 *      Author: Zucca
 */

#include "GORectangle.h"

GORectangle::GORectangle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic) {
	int posX, posY;
	int difX, difY;

	engine = engine->getInstance();
	this->color = color;
	this->dynamic = dynamic;
	this->vx = vx;
	this->vy = vy;

	difX = abs(vx.at(0) - vx.at(1));
	difY = abs(vy.at(0) - vy.at(1));
	//Position equals mass center for Box2d
	posX = (vx.at(0) + vx.at(1))/2;
	posY = (vy.at(0) + vy.at(1))/2;
	//Creating Rectangle in the Box2D World
	object = engine->CreateRectangle(posX, posY, difX, difY, dynamic);

	//Setting the 4 rectangle vertices
	this->vx.at(0) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(0)).x)*PIXELS_PER_METRE);
	this->vy.at(0) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(0)).y)*PIXELS_PER_METRE);
	this->vx.at(1) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(1)).x)*PIXELS_PER_METRE);
	this->vy.at(1) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(1)).y)*PIXELS_PER_METRE);
	this->vx.push_back((int)((object.body->GetWorldPoint(object.shape.GetVertex(2)).x)*PIXELS_PER_METRE));
	this->vy.push_back((int)((object.body->GetWorldPoint(object.shape.GetVertex(2)).y)*PIXELS_PER_METRE));
	this->vx.push_back((int)((object.body->GetWorldPoint(object.shape.GetVertex(3)).x)*PIXELS_PER_METRE));
	this->vy.push_back((int)((object.body->GetWorldPoint(object.shape.GetVertex(3)).y)*PIXELS_PER_METRE));
}

GORectangle::~GORectangle() {
	engine->DestroyObject(this->object);
}

float32 GORectangle::Update(){
	if(dynamic){
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			vx.at(i) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(i)).x)*PIXELS_PER_METRE);
			vy.at(i) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(i)).y)*PIXELS_PER_METRE);
		}
	}
	//Return value of y axis for deleting bodys out of screen
	return object.body->GetPosition().y*PIXELS_PER_METRE;
}

void GORectangle::Render(SDL_Surface* screen){
	graphics->DrawRectangle(screen, vx, vy, color);
}
