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
 * Descricao: Produz o audio do jogo.
 */

#include "Audio.h"

// Loads the audio file
Audio::Audio(string fileName, int tipo) {
	this->tipo = tipo;
	musica = NULL;
	som = NULL;
	switch(tipo){
		case 0:
			som = Mix_LoadWAV(fileName.c_str());
		break;
		case 1:
			musica = Mix_LoadMUS(fileName.c_str());
		break;
	}

}

Audio::~Audio() {
	Mix_FreeChunk(som);
	Mix_FreeMusic(musica);
}

void Audio::Play(int n){
	switch(tipo){
		case 0:
			Mix_PlayChannel(-1, som, n);
		break;
		case 1:
			if(!Mix_PlayingMusic())
				Mix_PlayMusic(musica, n);
		break;
	}
}

void Audio::Stop(){
	switch(tipo){
		case 0:
			if(Mix_Playing(-1))
				Mix_HaltChannel(-1);
		break;
		case 1:
			if(Mix_PlayingMusic())
				Mix_HaltMusic();
		break;
	}
}

// Checks if the music is playing.
bool Audio::Tocando(){
	switch(tipo){
		case 0:
			if((Mix_Playing(-1))&&(Mix_Paused(-1)))
				return true;
		break;
		case 1:
			if((Mix_PlayingMusic())&&(!Mix_PausedMusic()))
				return true;
		break;
	}
	return false;
}

void Audio::Pause(){
	switch(tipo){
		case 0:
			Mix_Pause(-1);
		break;
		case 1:
			if(Mix_PlayingMusic())
				Mix_PauseMusic();
		break;
	}
}

void Audio::Resume(){
	switch(tipo){
		case 0:
			if(Mix_Paused(-1))
				Mix_Resume(-1);
		break;
		case 1:
			if(Mix_PausedMusic())
				Mix_ResumeMusic();
		break;
	}
}
