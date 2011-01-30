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

#ifndef SPRITE_H_
#define SPRITE_H_

#include <cstdio>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

using namespace std;

class Sprite {
	string fileName;
	SDL_Surface *surfaceRot;
	SDL_Rect rectRot;
	double angle;
	double zoom;
public:
	int x;
	int y;
	SDL_Surface *surface;
	SDL_Rect dstRect;
	// Loads the sprite from the file in the x and y position.
	Sprite(string fileName, int x, int y);
	virtual ~Sprite();
	void Render(SDL_Surface *screen);
	// Moves the sprites position on screen.
	void UpdatePos(int x, int y);
	// Returns the sprites rectangle
	SDL_Rect GetRect();
	// Checks if the sprites box collide with any other sprite.
	bool BoxCollidesWith(Sprite *sprite);
	// Checks if the sprites inner circle collides with another sprite.
	bool InnerCircleCollidesWith(Sprite* sprite);
	// Checks if the sprites outer circle collides with another sprite.
	bool OuterCircleCollidesWith(Sprite* sprite);
	// Checks if the sprites pixels collides with another sprites pixels.
	bool PixelCollidesWith(Sprite* sprite);
	// Rotates and zooms the sprite;
	void SetRotoZoom(double angle, double zoom);
};

#endif /* SPRITE_H_ */
