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

#include "GameManager.h"

GameManager::GameManager() {
	/* Engine initialization */
	engine = engine->getInstace();
	engine->Initialize();

	/* Audio and video initialization */
	SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_TIMER);
	//TTF_Init();
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,1,4096);

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	if((screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL | SDL_HWSURFACE)) == NULL){
		printf("Couldn't set video mode! Quitting...");
		SDL_Quit();
		return;
	}

	// Graphics initialization
	graphics = graphics->getInstace();

	/* FPSManager initialization */
	manex = (FPSmanager*)malloc(sizeof(FPSmanager));
	SDL_initFramerate(manex);
	SDL_setFramerate(manex, TAXA_FPS);

	currentState = new LevelState();
	currentState->Load();

	inputManager = inputManager->getInstance();
}

GameManager::~GameManager() {
	delete currentState;
	delete inputManager;
	SDL_FreeSurface(screen);
	Mix_CloseAudio();
}

void GameManager::run(){
	while(inputManager->quit == false) {
		/* Pump events to capture input */
		SDL_PumpEvents();
		/* Poll between the inputs */
		inputManager->pollEvents();
		//Update
		currentState->Update();
		/* Render */
		currentState->Render(screen);
		//motion blur
		glAccum(GL_MULT, 0.50);
		glAccum(GL_ACCUM, 1-0.50);
		glAccum(GL_RETURN, 1.0);
		//Blit
		SDL_GL_SwapBuffers();
		SDL_framerateDelay(manex);
	}
}