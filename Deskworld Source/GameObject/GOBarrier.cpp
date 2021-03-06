/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#include "GOBarrier.h"

GOBarrier::GOBarrier(vector<int> vx, vector<int> vy, RGBAColor color) {
	this->color = color;
	this->vx = vx;
	this->vy = vy;
	engine = engine->getInstance();

	if(vx[0] == vx[1]){
		int dify = abs(vy[0] - vy[1]);
		int posX = (vx[0] + vx[1])/2;
		int posY = (vy[0] + vy[1])/2;
		object = engine->CreateRectangle(posX, posY, 4, dify, false);
	}else{
		int difx = abs(vx[0] - vx[1]);
		int posX = (vx[0] + vx[1])/2;
		int posY = (vy[0] + vy[1])/2;
		object = engine->CreateRectangle(posX, posY, difx, 4, false);
	}


}

GOBarrier::~GOBarrier() {
	engine->DestroyObject(this->object);
}

void GOBarrier::Update(){

}

void GOBarrier::Render(){
	graphics->DrawLine(vx[0], vy[0], vx[1], vy[1], color);
}
