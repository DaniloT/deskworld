/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
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

void GOCircle::Update(){
	if(dynamic){
		vx.at(0) = (int)(object.body->GetPosition().x*PIXELS_PER_METRE);
		vy.at(0) = (int)(object.body->GetPosition().y*PIXELS_PER_METRE);
	}
}

void GOCircle::Render(){
	graphics->DrawCircle( (int)vx.at(0), (int)vy.at(0), (int)radius, color);
}


float32 GOCircle::GetRestitution(){
	return object.body->GetFixtureList()->GetRestitution();
}

float32 GOCircle::GetFriction(){
	return object.body->GetFixtureList()->GetFriction();
}

float32 GOCircle::GetDensity(){
	return object.body->GetFixtureList()->GetDensity();
}

void GOCircle::SetRestitution(float32 rest){
	object.body->GetFixtureList()->SetRestitution(rest);
}

void GOCircle::SetFriction(float32 fric){
	object.body->GetFixtureList()->SetFriction(fric);
}

void GOCircle::SetDensity(float32 dens){
	object.body->GetFixtureList()->SetDensity(dens);
}

