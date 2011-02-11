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
 * Descricao: Descricao de um state do jogo.
 */

#ifndef STATE_H_
#define STATE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class State {
public:
	//State();
	// Loads the state.
	virtual void Load() = 0;
	// Unloads the state.
	virtual void Unload() = 0;
	// Updates the state.
	virtual int Update() = 0;
	// Renders the state.
	virtual void Render() = 0;
};

#endif /* STATE_H_ */
