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
 * Descricao: Desenha graficos complexos do jogo.
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Input/InputManager.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "../Common.h"

#include <vector>

class Graphics {
	Graphics* instance;
	Graphics();
public:
	virtual ~Graphics();
	void DrawPixel(SDL_Surface* screen,Uint16 x, Uint16 y, RGBAColor color);
	void DrawLine(SDL_Surface* screen,Uint16 xOrigin, Uint16 yOrigin, Uint16 x, Uint16 y, RGBAColor color);
	void DrawTriangle(SDL_Surface* screen,Uint16 x1, Uint16 y1, Uint16 x2, Uint16 y2, Uint16 x3, Uint16 y3, RGBAColor color);
	void DrawRectangle(SDL_Surface* screen, vector<Sint16> vx, vector<Sint16> vy, RGBAColor color);
	void DrawCircle(SDL_Surface* screen, Uint16 vx, Uint16 vy, Uint16 r, RGBAColor color);
	void DrawPolygon(SDL_Surface* screen, vector<Sint16> vx, vector<Sint16> vy, int n, RGBAColor color);
	Graphics* getInstace();
};

#endif /* GRAPHICS_H_ */
