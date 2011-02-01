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
Audio::Audio(string fileName, int type) {
	this->type = type;
	music = NULL;
	noise = NULL;
	switch(type){
		case 0:
			noise = Mix_LoadWAV(fileName.c_str());
		break;
		case 1:
			music = Mix_LoadMUS(fileName.c_str());
		break;
	}

}

Audio::~Audio() {
	Mix_FreeChunk(noise);
	Mix_FreeMusic(music);
}

void Audio::Play(int n){
	switch(type){
		case 0:
			Mix_PlayChannel(-1, noise, n);
		break;
		case 1:
			if(!Mix_PlayingMusic())
				Mix_PlayMusic(music, n);
		break;
	}
}

void Audio::Stop(){
	switch(type){
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
bool Audio::isPlaying(){
	switch(type){
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
	switch(type){
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
	switch(type){
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
