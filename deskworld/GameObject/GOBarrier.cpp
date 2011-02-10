/*
 * GOBarrier.cpp
 *
 *  Created on: 02/02/2011
 *      Author: Zucca
 */

#include "GOBarrier.h"

GOBarrier::GOBarrier(vector<int> vx, vector<int> vy, RGBAColor color) {
	this->color = color;
	this->vx = vx;
	this->vy = vy;
	engine = engine->getInstance();

	if(vx[0] == vx[1]){
		if(vy[0] > vy[1]){
			int dify = (vy[0] - vy[1])/2;
			object = engine->CreateRectangle(vx[0], dify, 4, dify*2, false);
		}else{
			int dify = (vy[1] - vy[0])/2;
			object = engine->CreateRectangle(vx[0], dify, 4, dify*2, false);
		}
	}else{
		if(vx[0] > vx[1]){
			int difx = (vx[0] - vx[1])/2;
			object = engine->CreateRectangle(difx, vy[0], difx*2, 4, false);
		}else{
			int difx = (vx[1] - vx[0])/2;
			object = engine->CreateRectangle(difx, vy[0], difx*2, 4, false);
		}
	}


}

GOBarrier::~GOBarrier() {
	engine->DestroyObject(this->object);
}

//void GOBarrier::SetInterpoints(Point p){
//	interpoints.push_back(p);
//}
//
//bool GOBarrier::Intersects(vector<int> ivx, vector<int> ivy){
//	int factor = (int)((((ivx[1]-ivx[0])*(vy[0]-ivy[0])-(ivy[1]-ivy[0])*(vx[0]-ivx[0]))/((ivy[1]-ivy[0])*(vx[1]-vx[0])-(ivx[1]-ivx[0])*(vy[1]-vy[0])))*PIXELS_PER_METRE);
//	Point p;
//	p.x = (int)(vx[0]*PIXELS_PER_METRE)+factor*(int)((vx[1] - vx[0])*PIXELS_PER_METRE);
//	p.y = (int)(vy[0]*PIXELS_PER_METRE)+factor*(int)((vy[1] - vy[0])*PIXELS_PER_METRE);
////	if(factor){
////
////	}
//}

void GOBarrier::Update(){

}

void GOBarrier::Render(){
	graphics->DrawLine(vx[0], vy[0], vx[1], vy[1], color);
}
