/*
 * GOBarrier.cpp
 *
 *  Created on: 02/02/2011
 *      Author: Zucca
 */

#include "GOBarrier.h"

GOBarrier::GOBarrier(vector<Point> vertices, RGBAColor color, bool passable) {
	bool validate = true;
	for(Uint32 i = 0 ; i < vertices.size() ; i++){
		if((vertices[i].x != 0)&&(vertices[i].x != WIDTH)){
			if((vertices[i].y != 0)||(vertices[i].y != HEIGHT)){
				validate = false; break;
			}
		}else if((vertices[i].y != 0)&&(vertices[i].y != HEIGHT)){
			if((vertices[i].x != 0)||(vertices[i].x != WIDTH)){
				validate = false; break;
			}
		}else if(((vertices[i].x != 0)&&(vertices[i].x != WIDTH))||((vertices[i].y != 0)&&(vertices[i].y != HEIGHT))){
			validate = false; break;
		}

		vx.push_back(vertices[i].x);
		vy.push_back(vertices[i].y);
	}
	this->color = color;
	if(validate){
		engine = engine->getInstance();


		if(!passable)
		object = engine->CreateBarrier(vertices);

		for (b2ContactEdge* ce = object.body->GetContactList(); ce; ce = ce->next){
		  b2Contact* c = ce->contact;
		  b2Fixture *fixA, *fixB;
		  fixA = c->GetFixtureA();
		  fixB = c->GetFixtureB();
		  if(((int)(fixA->GetUserData()) == BARRIER)&&((int)(fixB->GetUserData()) == BARRIER)){
			  b2PolygonShape* shapeA = (b2PolygonShape*)fixA->GetShape();
			  b2PolygonShape* shapeB = (b2PolygonShape*)fixB->GetShape();
			  b2Vec2 vA0 = shapeA->GetVertex(0), vA1 = shapeA->GetVertex(1);
			  b2Vec2 vB0 = shapeB->GetVertex(0), vB1 = shapeB->GetVertex(1);
			  int factor = (int)((((vB1.x-vB0.x)*(vA0.y-vB0.y)-(vB1.y-vB0.y)*(vA0.x-vB0.x))/((vB1.y-vB0.y)*(vA1.x-vA0.x)-(vB1.x-vB0.x)*(vA1.y-vA0.y)))*PIXELS_PER_METRE);
			  Point p;
			  p.x = (int)(vA0.x*PIXELS_PER_METRE)+factor*(int)((vA1.x - vA0.x)*PIXELS_PER_METRE);
			  p.y = (int)(vA0.y*PIXELS_PER_METRE)+factor*(int)((vA1.y - vA0.y)*PIXELS_PER_METRE);
			  interpoints.push_back(p);

		  }
		}
	}
}

GOBarrier::~GOBarrier() {
	engine->DestroyObject(this->object);
}

void GOBarrier::SetInterpoints(Point p){
	interpoints.push_back(p);
}

void GOBarrier::Render(){
	graphics->DrawLine(vx[0], vy[0], vx[1], vy[1], color);
}
