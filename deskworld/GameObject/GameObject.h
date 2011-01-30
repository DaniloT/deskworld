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

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../Engine/Engine.h"
#include "../Engine/Box2D/Box2D.h"
#include "../Graphics/Sprite.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <SDL/SDL_rotozoom.h>
#include "../Graphics/Graphics.h"
#include "../Common.h"

#include <vector>

#define DISTANCE(x1,y1,x2,y2) sqrtf(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)))

class GameObject {
public:
	Object object;
	RGBAColor color;
	vector<Sint16> vx, vy;
	bool dynamic;
	Engine* engine;
	Graphics* graphics;

	// Creates an object with the properties passed in the place passed.
	GameObject(){}
	virtual ~GameObject();
	// Return the objects body
	b2Body* GetBody();
	// Updates the objects.
	virtual float32 Update() = 0;
	// Render the object.
	virtual void Render(SDL_Surface* screen) = 0;
};

#endif /* GAMEOBJECT_H_ */
