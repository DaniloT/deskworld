/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 * Descricao: Calcula e cria os objetos do jogo.
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine/Engine.h"
#include "../Graphics/Graphics.h"
#include "../Common.h"

#include <vector>

#define DISTANCE(x1,y1,x2,y2) sqrtf(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)))

class GameObject {
public:
	Object object;
	RGBAColor color;
	vector<int> vx, vy;
	bool dynamic;
	Engine* engine;
	Graphics* graphics;

	// Return the objects body
	b2Body* GetBody(){
		return object.body;
	}
	// Updates the objects.
	virtual float32 Update() = 0;
	// Render the object.
	virtual void Render() = 0;
};

#endif /* GAMEOBJECT_H_ */
