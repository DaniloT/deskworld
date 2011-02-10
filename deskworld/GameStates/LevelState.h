/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 * Descricao: State in game do jogo.
 */

#ifndef LEVELSTATE_H_
#define LEVELSTATE_H_

#define MENUPROX 20

#include "State.h"
#include "../Input/InputManager.h"
#include "../Engine/Engine.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/GOTriangle.h"
#include "../GameObject/GORectangle.h"
#include "../GameObject/GOCircle.h"
#include "../GameObject/GOPolygon.h"
#include "../GameObject/GOFreeform.h"
#include "../GameObject/GOWorld.h"
#include "../GameObject/GOBarrier.h"
#include "../Graphics/Graphics.h"
#include "../Sound/Audio.h"
#include "../Graphics/ImageLoader.h"

#include <vector>

typedef struct DrawObject{
	int xOrig, yOrig, xMouse, yMouse; // Origin Coordinates of draw.
	bool drawing;	//indicates if user is drawing.
	bool menu; //indicates if the click opens a menu.
} DrawObject;

class LevelState: public State {
	vector<int> ff_vx[10001], ff_vy[10001]; // Coordinates of free form objects.
	DrawObject drawObjects[10001];
	vector<GameObject*> objects;
	vector<GOWorld*> worlds;
	InputManager* inputManager;
	Graphics* graphics;
	ImageLoader* background;
	ImageLoader* fechar;
	vector<Point> menuP;
	vector<ImageLoader*> menu;
	vector<ImageLoader*> menuSelect[3];
//	ImageLoader* menu;
//	ImageLoader* menuSelect[4];
	Audio* bgMusic;
	Engine* engine;
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
	void Render();
};

#endif /* LEVELSTATE_H_ */
