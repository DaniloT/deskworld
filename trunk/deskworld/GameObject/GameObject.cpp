/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Introducao ao Desenvolvimento de Jogos - 01/2010
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 * Turma: A
 *
 * Descricao: Calcula e cria os objetos do jogo.
 */

#include "GameObject.h"

// Creates an object with the properties passed in the place passed.
/*
GameObject::GameObject(vector<Sint16> vx, vector<Sint16> vy, RGBAColor color, int type, bool dynamic){
	engine = engine->getInstace();
	this->vx = vx;
	this->vy = vy;
	this->color = color;
	this->dynamic = dynamic;
	this->type = type;
	Uint16 posX, posY;

	Uint16 difX, difY;
	float32 distance;

	switch(type){
	case triangle:
		//Position equals mass center for Box2d
		posX = (vx.at(0) + vx.at(1) + vx.at(2))/3;
		posY = (vy.at(0) + vy.at(1) + vx.at(2))/3;

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

		object = engine->CreateTriangle(posX, posY, vx, vy, dynamic);

		this->vx.at(0) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(0)).x)*PIXELS_PER_METRE);
		this->vy.at(0) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(0)).y)*PIXELS_PER_METRE);
		this->vx.at(1) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(1)).x)*PIXELS_PER_METRE);
		this->vy.at(1) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(1)).y)*PIXELS_PER_METRE);
		this->vx.at(2) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(2)).x)*PIXELS_PER_METRE);
		this->vy.at(2) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(2)).y)*PIXELS_PER_METRE);

		break;
	case rectangle:
		difX = abs(vx.at(0) - vx.at(1));
		difY = abs(vy.at(0) - vy.at(1));
		//Position equals mass center for Box2d
		posX = (vx.at(0) + vx.at(1))/2;
		posY = (vy.at(0) + vy.at(1))/2;
		//Creating Rectangle in the Box2D World
		object = engine->CreateRectangle(posX, posY, difX, difY, dynamic);

		//Setting the 4 rectangle vertices
		this->vx.at(0) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(0)).x)*PIXELS_PER_METRE);
		this->vy.at(0) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(0)).y)*PIXELS_PER_METRE);
		this->vx.at(1) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(1)).x)*PIXELS_PER_METRE);
		this->vy.at(1) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(1)).y)*PIXELS_PER_METRE);
		this->vx.push_back((Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(2)).x)*PIXELS_PER_METRE));
		this->vy.push_back((Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(2)).y)*PIXELS_PER_METRE));
		this->vx.push_back((Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(3)).x)*PIXELS_PER_METRE));
		this->vy.push_back((Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(3)).y)*PIXELS_PER_METRE));

		break;
	case circle:
		radius = DISTANCE((float32)vx.at(0), (float32)vy.at(0), (float32)vx.at(1), (float32)vy.at(1));
		object = engine->CreateCircle(vx.at(0),vy.at(0),radius, dynamic);
		this->vx.erase(this->vx.begin()+1);
		this->vy.erase(this->vy.begin()+1);
		break;
	case freeform:
		radius = 3;
		object = engine->CreateFreeform(vx, vy, radius, dynamic);
		break;
	}
}
*/
GameObject::~GameObject() {
	//engine->DestroyObject(this->object);
}

// Return the objects body
b2Body* GameObject::GetBody(){
	return object.body;
}

// Updates the object.
/*
float32 GameObject::Update(){
	if(dynamic){
		if(type == circle){
			vx.at(0) = (Sint16)(object.body->GetPosition().x*PIXELS_PER_METRE);
			vy.at(0) = (Sint16)(object.body->GetPosition().y*PIXELS_PER_METRE);
		}else if(type == freeform){
			b2Fixture* fixList = object.body->GetFixtureList();
			b2CircleShape* shape;
			Sint16 x = (Sint16) (object.body->GetPosition().x*PIXELS_PER_METRE);
			Sint16 y = (Sint16) (object.body->GetPosition().y*PIXELS_PER_METRE);
			for(Uint32 i = 0 ; fixList != NULL ; i++){
				shape = (b2CircleShape*) fixList->GetShape();
				vx.at(i) = (Sint16)((object.body->GetWorldPoint(shape->GetVertex(0)).x)*PIXELS_PER_METRE);
				vy.at(i) = (Sint16)((object.body->GetWorldPoint(shape->GetVertex(0)).y)*PIXELS_PER_METRE);
				fixList = fixList->GetNext();
			}
		}else{
			for(Uint32 i = 0 ; i < vx.size() ; i++){
				vx.at(i) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(i)).x)*PIXELS_PER_METRE);
				vy.at(i) = (Sint16)((object.body->GetWorldPoint(object.shape.GetVertex(i)).y)*PIXELS_PER_METRE);
			}
		}
	}
	//Return value of y axis for deleting bodys out of screen
	return object.body->GetPosition().y*PIXELS_PER_METRE;
}

// Render the object.
void GameObject::Render(SDL_Surface* screen){
	switch(type){
	case triangle:
		graphics->DrawPolygon(screen, vx, vy, 3, color);
		break;
	case rectangle:
		graphics->DrawPolygon(screen, vx, vy, 4, color);
		break;
	case circle:
		graphics->DrawCircle(screen, (Uint16)vx.at(0), (Uint16)vy.at(0), (Sint16)radius, color);
		break;
	case freeform:
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			graphics->DrawCircle(screen, (Uint16)vx.at(i), (Uint16)vy.at(i), (Sint16)radius, color);
		}
		break;
	}
}
*/
