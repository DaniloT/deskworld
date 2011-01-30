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
 * Descricao: Classe que manuseia o jogo em si, trata da iniciacao e chamada do level.
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_framerate.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_opengl.h>

#include "GameStates/State.h"
#include "GameStates/LevelState.h"
#include "Input/InputManager.h"
#include "Engine/Engine.h"
#include "Graphics/Graphics.h"

#define TAXA_FPS 60

class GameManager {
	SDL_Surface* screen;
	FPSmanager* manex;
	State* currentState;
	int dt, lastTime;
	InputManager* inputManager;
	Graphics* graphics;
	Engine* engine;
public:
	GameManager();
	virtual ~GameManager();
	void run();
};

#endif /* GAMEMANAGER_H_ */
