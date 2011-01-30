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

	graphics = graphics->getInstace();

	/* Audio and video initialization */
	SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_TIMER);
	//TTF_Init();
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,1,4096);

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    //SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0);

	if((screen = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_HWSURFACE)) == NULL){
		printf("Couldn't set video mode! Quitting...");
		SDL_Quit();
		return;
	}

	//Enable Color Transparency
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, 800, 600);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, 800, 600, 0);

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

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

		/*switch(currentState->Update(dt)){
			case 0:
				// Fazer nada
				break;
			case 1:
				currentState->Unload();
				currentState = new LevelState();
				currentState->Load();
				break;
			case 2:
				currentState->Unload();
				currentState = new ControlsState();
				currentState->Load();
				break;
			case 3:
				currentState->Unload();
				currentState = new MainMenuState();
				currentState->Load();
				break;
		}*/
		currentState->Update();
		/* Render */
		currentState->Render(screen);
		//SDL_Flip(screen);
		SDL_GL_SwapBuffers();
		SDL_framerateDelay(manex);
	}
}
