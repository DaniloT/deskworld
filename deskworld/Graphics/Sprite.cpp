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
 * Descricao: Sprites do jogo.
 */

#include "Sprite.h"

// Loads the sprite from the file in the x and y position.
Sprite::Sprite(string fileName, int x, int y) {
	this->x = x;
	this->y = y;
	surface = IMG_Load(fileName.c_str());
	surfaceRot = NULL;
	angle = 0;
	zoom = 1;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = surface->w;
	dstRect.h = surface->h;
}


void Sprite::Render(SDL_Surface *screen){
	if((zoom == 1)&&(angle == 0)){
		dstRect.x = x;
		dstRect.y = y;
		SDL_BlitSurface(surface, NULL, screen, &dstRect);
	}else{
		rectRot.x = x;
		rectRot.y = y;
		SDL_BlitSurface(surfaceRot, NULL, screen, &rectRot);
	}
}

// Moves the sprites position on screen.
void Sprite::UpdatePos(int x, int y){
	this->x = x;
	this->y = y;
}

// Returns the sprites rectangle
SDL_Rect Sprite::GetRect(){
	dstRect.x = x;
	dstRect.y = y;
	return dstRect;
}

Sprite::~Sprite() {
	SDL_FreeSurface(surface);
}

// Checks if the sprites box collide with any other sprite.
bool Sprite::BoxCollidesWith(Sprite* sprite){
	int diffx = dstRect.x - sprite->GetRect().x;
	int diffy = dstRect.y - sprite->GetRect().y;

	/* Collision detection..*/
	if((diffx > sprite->GetRect().w) || (-diffx > dstRect.w)){
		return false;
	}else if((diffy > sprite->GetRect().h)||(-diffy > dstRect.h)){
		return false;
	}else{
		return true;
	}
}

// Rotates and zooms the sprite;
void Sprite::SetRotoZoom(double angle, double zoom){
	SDL_FreeSurface(surfaceRot);
	this->zoom = zoom;
	this->angle = angle;
	/* recebe o zoom e atualiza retangulo para renderizar */
	surfaceRot = rotozoomSurface(surface, angle, zoom, 1);
	rectRot.x = dstRect.x;
	rectRot.y = dstRect.y;
	rectRot.w = surfaceRot->w;
	rectRot.h = surfaceRot->h;
}
