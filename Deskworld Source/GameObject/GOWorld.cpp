/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#include "GOWorld.h"

GOWorld::GOWorld(vector<Point> vertices) {
	gravity.SetZero();
	currentTool = circle;
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
	engine->DestroyObject(this->wObject);
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

vector<Point> GOWorld::GetVertices(){
	return vertices;
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
//		if(objects->at(i)->object.body->GetUserData() != NULL){
//			int* poly = (int*)objects->at(i)->object.body->GetUserData();
//			if(*poly != 33){
//				if(this->isInside(objects->at(i))){
//					b2Vec2 gravbod;
//					gravbod.Set(gravity.x*objects->at(i)->GetBody()->GetMass(), gravity.y*objects->at(i)->GetBody()->GetMass());
//					objects->at(i)->GetBody()->ApplyForce(gravbod, objects->at(i)->GetBody()->GetWorldCenter());
//					objects->at(i)->Update();
//				}
//			}else{
//				Point p;
//				p.x = (int)(objects->at(i)->object.shape.GetVertex(0).x*PIXELS_PER_METRE);
//				p.y = (int)(objects->at(i)->object.shape.GetVertex(0).y*PIXELS_PER_METRE);
//				if(this->isInside(p)){
//					b2Vec2 gravbod;
//					gravbod.Set(gravity.x*objects->at(i)->GetBody()->GetMass(), gravity.y*objects->at(i)->GetBody()->GetMass());
//					objects->at(i)->GetBody()->ApplyForce(gravbod, objects->at(i)->GetBody()->GetWorldCenter());
//					objects->at(i)->Update();
//				}
//			}
//		}
		if(this->isInside(objects->at(i))){
			b2Vec2 gravbod;
			gravbod.Set(gravity.x*objects->at(i)->GetBody()->GetMass(), gravity.y*objects->at(i)->GetBody()->GetMass());
			objects->at(i)->GetBody()->ApplyForce(gravbod, objects->at(i)->GetBody()->GetWorldCenter());
			objects->at(i)->Update();
		}
	}
}
