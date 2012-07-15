/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 * Descricao: Produz o audio do jogo.
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <cstdio>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

using namespace std;

class Audio {
	string fileName;
	Mix_Chunk *noise;
	Mix_Music *music;
	int type;
public:
	// Loads the audio file.
	Audio(string fileName, int tipo);
	virtual ~Audio();
	void Play(int n);
	void Stop();
	// Checks if audio is playing.
	bool isPlaying();
	void Pause();
	void Resume();
};

#endif /* AUDIO_H_ */
