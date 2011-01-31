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
 * Descricao: State in game do jogo.
 */

#ifndef LEVELSTATE_H_
#define LEVELSTATE_H_

#include "State.h"
#include "../Input/InputManager.h"
#include "../Engine/Engine.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/GOTriangle.h"
#include "../GameObject/GORectangle.h"
#include "../GameObject/GOCircle.h"
#include "../GameObject/GOFreeform.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Graphics.h"
#include "../Sound/Audio.h"
#include "../Graphics/ImageLoader.h"

#include <vector>

typedef struct DrawObject{
	Sint16 xOrig, yOrig, xMouse, yMouse; // Origin Coordinates of draw
	vector<Sint16> ff_vx, ff_vy; // Coordinates of free form objects
	bool drawing;	//indicates if user is drawing
} DrawObject;

class LevelState: public State {
	vector<Sint16> ff_vx[10001], ff_vy[10001];
	map<Sint16,TUIOData*>::iterator itTouch;
	map<Sint16,DrawObject*>::iterator it;
	map<Sint16,DrawObject*> drawObjects;
	vector<GameObject*> objects;
	InputManager* inputManager;
	Graphics* graphics;
	ImageLoader* background;
	ImageLoader* dinamico;
	ImageLoader* estatico;
	ImageLoader* circulo;
	ImageLoader* retangulo;
	ImageLoader* triangulo;
	ImageLoader* borracha;
	ImageLoader* formalivre;
	ImageLoader* fechar;
	ImageLoader* musica;
	ImageLoader* vermelho;
	ImageLoader* azul;
	ImageLoader* verde;
	ImageLoader* amarelo;
	ImageLoader* preto;
	ImageLoader* branco;
	Audio* bgMusic;
	Engine* engine;
	uint8 currentTool;
	RGBAColor toolColor;
	bool dynamic;	//indicates if user is creating dynamic object
	float32 thickness;
public:
	//Dummy destructor.
	virtual ~LevelState();
	// Loads the state
	void Load();
	// Unloads the state
	void Unload();
	// Updates the state
	int Update();
	// Renders the state
	void Render(SDL_Surface* screen);
};

#endif /* LEVELSTATE_H_ */
